#ifndef ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
#define ORG_EEROS_SEQUENCER_SEQUENCE_HPP_


#include <condition_variable>
#include <eeros/core/ThreadSequence.hpp>
#include <eeros/sequencer/BaseSequence.hpp>

namespace eeros {
	namespace sequencer {
		
		class Sequencer;		//forward declaration
		
		class Sequence : public ThreadSequence, public BaseSequence {
		public:
			Sequence(Sequencer& S, BaseSequence* caller, std::string name);
			Sequence(Sequencer& S, std::string name);		//only for mainSequence
			~Sequence();
			
			
// 			virtual int operator() () = 0;  This function has to be implemented in the derived Sequence

			virtual int action() = 0;
			int start();
			int startMainSequence();
			
			bool isStep();
		
			BaseSequence* getLatestCalledSequence();	
// // // 			void addMonitor(Monitor* monitor);	//TODO implement
			void addSequence(Sequence* Seq);
			
			
			
	// 	private:
// 			std::string name;
			int sequenceID = 0;
// 			static int sequenceCount;	//TODO works like intended? counts all created sequences
			
// 			eeros::logger::Logger<eeros::logger::LogWriter> log; is in BaseSequence
// 			Sequencer& S; is in BaseSequence
			
			std::mutex m;
			std::condition_variable cv;
// 			Sequence* caller; is in BaseSequence
// 			bool blocking = false;
			
		protected:
			
		private:
			void run();
			BaseSequence* latestCalledSequence;
			
		};
		

	
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
