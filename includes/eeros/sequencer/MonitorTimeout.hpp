#ifndef ORG_EEROS_SEQUENCER_MONITORTIMEOUT_HPP_
#define ORG_EEROS_SEQUENCER_MONITORTIMEOUT_HPP_

#include <eeros/sequencer/Monitor.hpp>

namespace eeros {
	namespace sequencer {
		
		class MonitorTimeout : public Monitor {
		public:
			MonitorTimeout(BaseSequence* owner, Condition* condition, behaviorEnum behavior);
			
			
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_MONITORTIMEOUT_HPP_