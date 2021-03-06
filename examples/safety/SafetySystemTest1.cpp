//#include <initializer_list>
#include <eeros/safety/SafetySystem.hpp>
#include <eeros/hal/HAL.hpp>
#include <eeros/core/EEROSException.hpp>
#include <eeros/core/Executor.hpp>
#include <eeros/logger/StreamLogWriter.hpp>
#include <eeros/logger/Logger.hpp>
#include <eeros/task/Lambda.hpp>
#include <eeros/hal/DummyLogicInput.hpp>
#include <eeros/hal/DummyLogicOutput.hpp>
#include <unistd.h>
#include <iostream>
#include <signal.h>

#include "SafetyPropertiesTest1.hpp"

using namespace eeros;
using namespace eeros::hal;
using namespace eeros::safety;
using namespace eeros::logger;

void signalHandler(int signum) {
	SafetySystem::exitHandler();
}

int main() {
	signal(SIGHUP, signalHandler);
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	signal(SIGKILL, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGPWR, signalHandler);
	
	StreamLogWriter w(std::cout);
	w.show();
	Logger<LogWriter>::setDefaultWriter(&w);
	Logger<LogWriter> log;
	
	log.info() << "Safety System Example started...";
	
	// Get HAL instance and initialize
	HAL& hal = HAL::instance();
	hal.addPeripheralInput(new DummyLogicInput("in1"));
	hal.addPeripheralOutput(new DummyLogicOutput("out1"));
	
	// Create and initialize safety system
	double period = 1;
	SafetyPropertiesTest1 ssProperties;
	SafetySystem safetySys(ssProperties, period);

	safetySys.triggerEvent(ssProperties.seStartInitializing);

	// Create and run executor
	auto executor = eeros::Executor::instance();
	executor.setMainTask(safetySys);
	
	eeros::task::Lambda l1 ([&] () {
		static int count = 0;
		if (count++ == 5) safetySys.triggerEvent(ssProperties.seInitializingDone);
	});
	eeros::task::Periodic t1("t1", period, l1);
	executor.add(t1);

	executor.run();

	log.info() << "Test finished...";
}
