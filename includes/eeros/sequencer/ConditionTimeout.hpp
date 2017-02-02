#ifndef ORG_EEROS_SEQUENCER_CONDITIONTIMEOUT_HPP_
#define ORG_EEROS_SEQUENCER_CONDITIONTIMEOUT_HPP_

#include <chrono>

#include <eeros/sequencer/Condition.hpp>

namespace eeros {
	namespace sequencer {
		
		class ConditionTimeout : public Condition {
		public:
			ConditionTimeout(Sequencer& seq);
			
			bool validate();
			
			void setTimeoutTime(double timeInSec);	//0 = not set or infinite
			void resetTimeout();
			
			
		private:
			bool started = false;			
			std::chrono::steady_clock::time_point startTime;
			double timeout;				//0 = not set or infinite; in Seconds
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_CONDITIONTIMEOUT_HPP_