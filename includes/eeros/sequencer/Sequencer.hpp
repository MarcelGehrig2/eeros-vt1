#ifndef ORG_EEROS_SEQUENCER_SEQUENCER_HPP_
#define ORG_EEROS_SEQUENCER_SEQUENCER_HPP_

#include <vector>
// #include <string>
#include <atomic>
// #include <vector>
// #include <mutex>
// #include <condition_variable>
// #include <eeros/core/Thread.hpp>
#include <eeros/sequencer/Sequence.hpp>

namespace eeros {
	namespace sequencer {
		
		
		namespace state {
			enum type { executing, waiting, terminating, terminated, idle };
		}
		
		namespace mode {
			enum type { automatic, stepping };
		}
	
		class Sequence;		//forward declaration
		
		class Sequencer : public Thread {
		public:
			Sequencer();
		// 	Sequencer(Sequence* mainSequence);
			
			void run();
			
			void addSequence(Sequence* seq);
			void addMainSequence(Sequence* mainSeq);
			
			
			
			virtual std::string getName() const;
			virtual state::type getState() const;
			virtual mode::type getMode() const;
			
			
		private:
			Sequence* mainSequence;
			std::vector< Sequence* > sequenceList;
			
			
			unsigned int id;
			std::atomic<state::type> state;
			std::atomic<mode::type> mode;
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
