#ifndef ORG_EEROS_CORE_THREAD_SEQUENCE_HPP_
#define ORG_EEROS_CORE_THREAD_SEQUENCE_HPP_

#include <eeros/logger/Logger.hpp>
#include <eeros/logger/LogWriter.hpp>

#include <thread>
#include <functional>
#include <string>

// Copy of Thread.hpp, but without logger. This allows multiple inheritance for Sequence.cpp


namespace eeros {
	
	class ThreadSequence {
	
	public:
		ThreadSequence();
		virtual ~ThreadSequence();
		
		virtual std::string getId() const;
		virtual void join();
		
	protected:
		ThreadSequence(std::function<void ()> t);
		
		virtual void run();
		
		std::thread t;
// 		eeros::logger::Logger<eeros::logger::LogWriter> log;
	};
};

#endif // ORG_EEROS_CORE_THREAD_SEQUENCE_HPP_
