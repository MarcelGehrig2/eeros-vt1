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

// Monitor::Monitor(BaseSequence* owner, Condition* condition, Behavior::enumerator behavior, BaseSequence* exceptionSequence, std::__cxx11::string goToTarget)
// : owner(owner), condition((condition), behavior), exceptionSequence(exceptionSequence), goToTarget(goToTarget)
// {
// 
// }

// bool Monitor::check(BaseSequence* caller)	//caller is the sequence, which
// {
// 	if( condition->isTrue() ) {
// 		
// 		//TODO n-times repetition watch
// 		BaseSequence::runningStateEnum currentRunningState = caller->getRunningState();
// 		
// 		caller->getSequencerException()->throwException(caller, owner, behavior, exceptionDescription);		
// 		startExceptionSequence();
// 		
// 		if ( currentRunningState != caller->getRunningState() ) return true;
// 		else return false;
// 	}
// 	else return false;
// }

void Monitor::startExceptionSequence()
{
	if ( exceptionSequence != NULL )
		exceptionSequence->start();
	//TODO start sequence
	//TODO function parameter of sequence?
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

// void Monitor::setGotToTarget(std::__cxx11::string goToTarget)
// {
// 	this->goToTarget = goToTarget;
// }
