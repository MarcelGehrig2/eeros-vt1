#ifndef ORG_EEROS_SEQUENCER_CONDITION_HPP_
#define ORG_EEROS_SEQUENCER_CONDITION_HPP_

namespace eeros {
	namespace sequencer {



		class Sequencer;
		
		class Condition {	
		public:
			Condition(Sequencer& seq);
		// 	Condition(Sequencer& seq, validateStyleEnum validateStyle, float cycleTime);
			
		// 	bool operator()();		// checks condition	
			bool isTrue();			//return true, if safed conditionState is true. Validates if validateStyle==polling
			virtual bool validate() = 0;	// has to be overwritten (pure virtual function)
			
			
			
		// 	enum validateStyleEnum {
		// 		polling,	//validates each time, the condition is checked (isTrue())
		// 		periodic,	//validates the sequence periodic
		// 	};
			
		// 	void addExceptionSequence(Sequence* exceptionSequence);
			
		protected:
			bool conditionState = false;
// 			validateStyleEnum validateStyle;
		// 	behaviorEnum behavior = notSet;
			
// 			float cycleTime;	//1sec
			
			
			Sequencer& S;			//reference to singleton Sequencer
		// 	
		// 	Sequence* exceptionSequence;
		// 	int retries = 0;
		// 	int maxRetries = 1;
		// 	
		// 	int counter = 0;
		// 	bool heritable = false;
			
		};
		
		
		
		
	};	//namespace sequencer
}; // namespace eeros

#endif //ORG_EEROS_SEQUENCER_CONDITION_HPP_