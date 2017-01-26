#include <eeros/sequencer/MonitorTimeout.hpp>

using namespace eeros;
using namespace eeros::sequencer;

MonitorTimeout::MonitorTimeout(BaseSequence* owner, Condition* condition, behaviorEnum behavior)
: Monitor(owner, condition, behavior)
{ }
