#ifndef ORG_EEROS_SEQUENCER_CONDITION_HPP_
#define ORG_EEROS_SEQUENCER_CONDITION_HPP_

namespace eeros {
	namespace sequencer {

		class Sequencer;
		
		class Condition {	
		public:
			Condition(Sequencer& seq);
			
			bool isTrue();					//return true, if safed conditionState is true. Validates if validateStyle==polling
			virtual bool validate() = 0;	// has to be overwritten (pure virtual function)

		protected:
			bool conditionState = false;
			
			Sequencer& S;			//reference to singleton Sequencer
		};
	};	//namespace sequencer
}; // namespace eeros

#endif //ORG_EEROS_SEQUENCER_CONDITION_HPP_