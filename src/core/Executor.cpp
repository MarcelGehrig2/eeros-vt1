#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <memory>
#include <cmath>
#include <thread>
#include <signal.h>
#include <sched.h>
#include <sys/mman.h>

#include <eeros/core/Executor.hpp>
#include <eeros/task/Async.hpp>
#include <eeros/task/Lambda.hpp>
#include <eeros/task/HarmonicTaskList.hpp>
#include <eeros/control/TimeDomain.hpp>
#include <eeros/safety/SafetySystem.hpp>


volatile bool running = true;

using namespace eeros;

namespace {

	using Logger = logger::Logger<logger::LogWriter>;

	struct TaskThread {
		TaskThread(double period, task::Periodic &task, task::HarmonicTaskList tasks) :
			taskList(tasks), async(taskList, task.getRealtime(), task.getNice())
		{
			async.counter.setPeriod(period);
			async.counter.monitors = task.monitors;
		}
		task::HarmonicTaskList taskList;
		task::Async async;
	};

	template < typename F >
	void traverse(std::vector<task::Periodic> &tasks, F func) {
		for (auto &t: tasks) {
			func(&t);
			traverse(t.before, func);
			traverse(t.after, func);
		}
	}

 	void createThread(Logger &log, task::Periodic &task, task::Periodic &baseTask, std::vector<std::shared_ptr<TaskThread>> &threads, std::vector<task::Harmonic> &output);

	void createThreads(Logger &log, std::vector<task::Periodic> &tasks, task::Periodic &baseTask, std::vector<std::shared_ptr<TaskThread>> &threads, task::HarmonicTaskList &output) {
		for (task::Periodic &t: tasks) {
			createThread(log, t, baseTask, threads, output.tasks);
			log.info() << t.getName() << "________task created";
		}
	}

	void createThread(Logger &log, task::Periodic &task, task::Periodic &baseTask, std::vector<std::shared_ptr<TaskThread>> &threads, std::vector<task::Harmonic> &output) {
		int k = static_cast<int>(task.getPeriod() / baseTask.getPeriod());
		double actualPeriod = k * baseTask.getPeriod();
		double deviation = std::abs(task.getPeriod() - actualPeriod) / task.getPeriod();
		task::HarmonicTaskList taskList;

		if (task.before.size() > 0) {
			createThreads(log, task.before, task, threads, taskList);
		}
		taskList.add(task.getTask());
		if (task.after.size() > 0) {
			createThreads(log, task.after, task, threads, taskList);
		}

		if (task.getRealtime())
			log.trace() << "creating harmonic realtime task '" << task.getName()
						<< "' with period " << actualPeriod << " sec (k = "
						<< k << ") and priority " << (Executor::basePriority - task.getNice())
						<< " based on '" << baseTask.getName() << "'";
		else
			log.trace() << "creating harmonic task '" << task.getName() << "' with period "
						<< actualPeriod << " sec (k = " << k << ")"
						<< " based on '" << baseTask.getName() << "'";

		if (deviation > 0.01) throw std::runtime_error("period deviation too high");

		if (task.getRealtime() && task.getNice() <= 0)
			throw std::runtime_error("priority not set");

		if (taskList.tasks.size() == 0)
			throw std::runtime_error("no task to execute");

		threads.push_back(std::make_shared<TaskThread>(actualPeriod, task, taskList));
		output.emplace_back(threads.back()->async, k);
	}
}

Executor::Executor() :
	log('E'), period(0), mainTask(nullptr) { }

Executor::~Executor() {

}

Executor& Executor::instance() {
	static Executor executor;
	return executor;
}

void Executor::setMainTask(task::Periodic &mainTask) {
	if (this->mainTask != nullptr)
		throw std::runtime_error("you can only define one main task per executor");
	period = mainTask.getPeriod();
	counter.setPeriod(period);
	this->mainTask = &mainTask;
}

void Executor::setMainTask(safety::SafetySystem &ss) {
	task::Periodic *task = new task::Periodic("safety system", ss.getPeriod(), ss, true);
	setMainTask(*task);
}

void Executor::add(task::Periodic &task) {
	tasks.push_back(task);
}

void Executor::add(control::TimeDomain &timedomain) {
	task::Periodic task(timedomain.getName().c_str(), timedomain.getPeriod(), timedomain, timedomain.getRealtime());
	tasks.push_back(task);
}

void Executor::prefault_stack() {
	unsigned char dummy[8*1024] = {};
}

bool Executor::lock_memory() {
	return (mlockall(MCL_CURRENT | MCL_FUTURE) != -1);
}

bool Executor::set_priority(int nice) {
	struct sched_param schedulingParam;
	schedulingParam.sched_priority = (Executor::basePriority - nice);
	return (sched_setscheduler(0, SCHED_FIFO, &schedulingParam) != -1);
}

void Executor::stop() {
	running = false;
}

void Executor::assignPriorities() {
	std::vector<task::Periodic*> priorityAssignments;

	// add task to list of priority assignments
	traverse(tasks, [&priorityAssignments] (task::Periodic *task) {
		priorityAssignments.push_back(task);
	});

	// sort list of priority assignments
	std::sort(priorityAssignments.begin(), priorityAssignments.end(), [] (task::Periodic *a, task::Periodic *b) -> bool {
		if (a->getRealtime() == b->getRealtime())
			return (a->getPeriod() < b->getPeriod());
		else
			return a->getRealtime();
	});

	// assign priorities
	int nice = 1;
	for (auto t: priorityAssignments) {
		if (t->getRealtime()) {
			t->setNice(nice++);
		}
	}
}

void Executor::run() {
	log.trace() << "starting executor with base period " << period << " sec and priority " << basePriority;

	if (period == 0.0)
		throw std::runtime_error("period of executor not set");

	log.trace() << "assigning priorities";
	assignPriorities();

	Runnable *mainTask = nullptr;

	if (this->mainTask != nullptr) {
		mainTask = &this->mainTask->getTask();
		log.trace() << "setting '" << this->mainTask->getName() << "' as main task";
	}

	std::vector<std::shared_ptr<TaskThread>> threads; // smart pointer used because async objects must not be copied
	task::HarmonicTaskList taskList;
	task::Periodic executorTask("executor", period, this, true);

	counter.monitors = this->mainTask->monitors;

	createThreads(log, tasks, executorTask, threads, taskList);

	using seconds = std::chrono::duration<double, std::chrono::seconds::period>;

	// TODO: implement this with ready-flag (wait for all threads to be ready instead of blind sleep)
	std::this_thread::sleep_for(seconds(1)); // wait 1 sec to allow threads to be created

	if (!set_priority(0))
		log.error() << "could not set realtime priority";

	prefault_stack();

	if (!lock_memory())
		log.error() << "could not lock memory in RAM";

	log.trace() << "starting periodic execution";

	auto next_cycle = std::chrono::steady_clock::now() + seconds(period);
// 	log.info() << taskList.tasks.
	while (running) {
		std::this_thread::sleep_until(next_cycle);

		counter.tick();
		taskList.run();
		if (mainTask != nullptr)
			mainTask->run();
		counter.tock();
		next_cycle += seconds(period);
	}

	log.trace() << "stopping all threads";

	for (auto &t: threads)
		t->async.stop();

	log.trace() << "joining all threads";

	for (auto &t: threads)
		t->async.join();

	log.trace() << "exiting executor";
}
