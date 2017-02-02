#ifndef ORG_EEROS_SEQUENCER_MONITOR_HPP_
#define ORG_EEROS_SEQUENCER_MONITOR_HPP_

#include <string>

#include <eeros/sequencer/EnumeratorsSequencer.hpp>

namespace eeros {
	namespace sequencer {
		
		
		class BaseSequence;
		class Condition;
		
		class Monitor {
		public:
			Monitor(BaseSequence* owner, Condition* condition, behaviorEnum behavior);
			Monitor(BaseSequence* owner, Condition* condition, behaviorEnum behavior, BaseSequence* exceptionSequence);

			void setExceptionSequence(BaseSequence* exceptionSequence);	
			void setBehavior(behaviorEnum behavior);
			behaviorEnum getBehavior() const;
			BaseSequence* getOwner() const;
		// 	void setGotToTarget(std::string goToTarget);
			
			bool checkCondition();
			void startExceptionSequence();
			
// 			bool check(BaseSequence* caller);	//returns true if runningState of caller is changed
			

			

			
		protected:
			BaseSequence* owner;
			Condition* condition;
			BaseSequence* exceptionSequence;
			behaviorEnum behavior;
// 			std::string goToTarget;			//
			std::string exceptionDescription;
			
		private:
			
		};

	};	//namespace sequencer
}; // namespace eeros

#endif	// ORG_EEROS_SEQUENCER_MONITOR_HPP_