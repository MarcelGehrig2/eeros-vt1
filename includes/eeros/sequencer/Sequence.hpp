#ifndef ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
#define ORG_EEROS_SEQUENCER_SEQUENCE_HPP_


#include <condition_variable>
// #include <string>
// #include <map>
// #include <functional>
// #include <vector>
// #include <mutex>
// #include <condition_variable>
// #include <atomic>
// 
// #include <eeros/logger/Logger.hpp>
// #include <eeros/logger/LogWriter.hpp>
// #include <eeros/sequencer/Sequencer.hpp>
// #include <eeros/sequencer/SequenceResult.hpp>
#include "eeros/core/Thread.hpp"
// #include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/BaseSequence.hpp>
// #include <eeros/sequencer/Monitor.hpp>

namespace eeros {
	namespace sequencer {

		
		class BaseSequence;		//forward declaration
		
		class Sequence : public Thread, public BaseSequence {
// 		class Sequence : public BaseSequence {
// 		class Sequence : public Thread {
		public:
	// 		Sequence();
			Sequence(Sequencer& S, Sequence* caller, std::string name);
			~Sequence();
			
			int operator() ();
			int runBlocking();
			int runNonBlocking();
			
			virtual int start();
			virtual int action() = 0;
			
			std::string getName() const;
			void setName(std::string name);
			
			bool isStep();
		
// // // 			void addMonitor(Monitor* monitor);	//TODO implementm
		// 	void addSequence
			
			
	// 	private:
			std::string name;
			int sequenceID = 0;
// 			static int sequenceCount;	//TODO works like intended? counts all created sequences
			
// 			eeros::logger::Logger<eeros::logger::LogWriter> log; is in BaseSequence
// 			Sequencer& S; is in BaseSequence
			
			std::mutex m;
			std::condition_variable cv;
// 			Sequence* caller; is in BaseSequence
			bool blocking = false;
			
		private:
			virtual void run();
		};
	
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
