#include <eeros/sequencer/ConditionTimeout.hpp>

using namespace eeros;
using namespace eeros::sequencer;

ConditionTimeout::ConditionTimeout(Sequencer& seq)
: Condition(seq), timeout(0)
{ }

bool ConditionTimeout::validate()
{
	if ( timeout == 0 ) return false;		//timeout is not activated
	
	if ( started == false ) {				//first call
		resetTimeout();
		return false;
	}
	
	auto now = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
	if (duration.count() > timeout*1000) return true;
	else return false;
}

void ConditionTimeout::setTimeoutTime(double timeInSec)
{
	timeout = timeInSec;
}

void ConditionTimeout::resetTimeout()
{
	started = true;
	startTime = std::chrono::steady_clock::now();
}
