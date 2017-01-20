#include <eeros/core/ThreadSequence.hpp>
#include <sstream>

// Copy of Thread.hpp, but without logger. This allows multiple inheritance for Sequence.cpp

using namespace eeros;

ThreadSequence::ThreadSequence() : t([&]() {
	std::string id = getId();
// 	log.trace() << "Thread '" << id << "' started.";
	
	this->run();
	
// 	log.trace() << "Thread '" << id << "' finished.";
}) { }

ThreadSequence::ThreadSequence(std::function<void ()> t) : t(t) { }

ThreadSequence::~ThreadSequence() {
	join();
}

std::string ThreadSequence::getId() const {
	std::ostringstream s;
	s << t.get_id();
	return s.str();
}

void ThreadSequence::join() {
	if(t.joinable()) t.join();
}

void ThreadSequence::run() { }
