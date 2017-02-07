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
// 			bool sleepMSec(int msec);	//TODO Check Monitors (of callers) while sleeping!
			
			bool isStep();
		
// 			BaseSequence* getLatestCalledSequence();
			
			
			
	// 	private:
			int sequenceID;
			
			std::mutex m;
			std::condition_variable cv;
			
		protected:
			
		private:
			void run();
// 			BaseSequence* latestCalledSequence;
			
		};
		

	
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
