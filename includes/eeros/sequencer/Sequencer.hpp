#ifndef ORG_EEROS_SEQUENCER_SEQUENCER_HPP_
#define ORG_EEROS_SEQUENCER_SEQUENCER_HPP_

#include <vector>
#include <atomic>

#include <eeros/core/Thread.hpp>
#include <eeros/sequencer/Sequence.hpp>

namespace eeros {
	namespace sequencer {
		
		
		namespace state {
			enum type { executing, waiting, terminating, terminated, idle };
		}
		
		namespace mode {
			enum type { automatic, stepping };
		}
	
		class BaseSequence;		//forward declaration
		class Sequence;
		
		
		class Sequencer : public Thread {
		public:
// 			Sequencer();
// 			~Sequencer();	//TODO clean everything
			
			void addSequence(Sequence* seq);
			void addMainSequence(Sequence* mainSeq);
			
			Sequence* getSequenceByID(int ID);
			Sequence* getSeqenceByName(std::string name);
			
			// Name, State and Mode are included for backwards compatibelity
			virtual std::string getName() const;
			virtual state::type getState() const;
			virtual mode::type getMode() const;
			std::vector< Sequence* > getListOfAllSequences();			
			
		private:
			Sequence* mainSequence;
			std::vector< Sequence* > sequenceList;	//list of all sequences
			
			
			unsigned int id;
			std::atomic<state::type> state;
			std::atomic<mode::type> mode;
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_SEQUENCER_HPP_
