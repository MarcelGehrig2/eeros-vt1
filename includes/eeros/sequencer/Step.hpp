#ifndef ORG_EEROS_SEQUENCER_STEP_HPP_
#define ORG_EEROS_SEQUENCER_STEP_HPP_


#include <condition_variable>
#include <eeros/sequencer/BaseSequence.hpp>

namespace eeros {
	namespace sequencer {

		class Sequencer;	//forward declaration
		class Sequence;

		class Step : public BaseSequence {
		public:
			Step(Sequencer& S, BaseSequence* caller);
			
			// 			virtual int operator() () = 0;  This function has to be implemented in the derived Step
			virtual int action() = 0;
			int start();
			
			bool isStep() const;
			
		protected:
			
		private:
		};
	
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_STEP_HPP_
