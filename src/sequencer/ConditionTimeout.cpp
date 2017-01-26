#include <eeros/sequencer/ConditionTimeout.hpp>

using namespace eeros;
using namespace eeros::sequencer;

ConditionTimeout::ConditionTimeout(Sequencer& seq)
: Condition(seq)
{ }

bool ConditionTimeout::validate()
{
	if ( timeout == 0 ) return false;		//timeout is not activated
	
	if ( started == false ) {				//first call
		restartTimer();
		return false;
	}
	
	auto now = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
	if (duration.count() > timeout*1000) return true;
	else return false;
}

void ConditionTimeout::setTime(double timeInSec)
{
	this->timeout = timeInSec;
}

void ConditionTimeout::restartTimer()
{
	started = true;
	startTime = std::chrono::steady_clock::now();
}
