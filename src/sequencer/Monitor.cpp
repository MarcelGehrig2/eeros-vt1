#include <eeros/sequencer/Monitor.hpp>
#include <eeros/sequencer/BaseSequence.hpp>

using namespace eeros;
using namespace eeros::sequencer;


Monitor::Monitor(BaseSequence* owner, Condition* condition, behaviorEnum behavior)
: Monitor(owner, condition, behavior, NULL)
{ }

Monitor::Monitor(BaseSequence* owner, Condition* condition, behaviorEnum behavior, BaseSequence* exceptionSequence)
: owner(owner), condition(condition), behavior(behavior), exceptionSequence(exceptionSequence)
{ }

void Monitor::startExceptionSequence()
{
	if ( exceptionSequence != NULL )
		exceptionSequence->start();
}

void Monitor::setBehavior(behaviorEnum behavior)
{
	this->behavior = behavior;
}

behaviorEnum Monitor::getBehavior() const
{
	return behavior;
}

BaseSequence* Monitor::getOwner() const
{
	return owner;
}

void Monitor::setExceptionSequence(BaseSequence* exceptionSequence)
{
	this->exceptionSequence = exceptionSequence;
}

bool Monitor::checkCondition()
{
	return condition->isTrue();
}
