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
#include <eeros/core/ThreadSequence.hpp>
// #include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/BaseSequence.hpp>
// #include <eeros/sequencer/Monitor.hpp>

namespace eeros {
	namespace sequencer {

		class BaseSequence;		//forward declaration
		
		class Sequence : public ThreadSequence, public BaseSequence {
// 		class Sequence : public BaseSequence {
// 		class Sequence : public Thread {	
		public:
	// 		Sequence();
			Sequence(Sequencer& S, Sequence* caller, std::string name);
			~Sequence();
			
			int operator() ();

			
			virtual int start();
			virtual int action() = 0;
			
			std::string getName() const;
			void setName(std::string name);
			
			bool isStep();
		
			BaseSequence* getLatestCalledSequence();	
// // // 			void addMonitor(Monitor* monitor);	//TODO implement
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
// 			bool blocking = false;
			
		private:
			virtual void run();
			BaseSequence* latestCalledSequence;
			
		};
		
		
		
		
		
		class Step : public BaseSequence {
		public:
			Step(Sequencer& S, Sequence* caller);
			
			virtual int start();
			virtual int action() = 0;
			
			bool isStep() const;
		};
	
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
