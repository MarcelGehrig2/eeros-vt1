#include <eeros/sequencer/BaseSequence.hpp>
#include <eeros/sequencer/EnumeratorsSequencer.hpp>
#include <unistd.h>

using namespace eeros;
using namespace eeros::sequencer;

BaseSequence::BaseSequence(Sequencer& S, BaseSequence* caller)
: S(S), callerSequence(caller), conditionTimeout(S), monitorTimeout(this, &conditionTimeout, behaviorEnum::abortOwner),
runningState(runningStateEnum::idle), isBlocking(true), pollingTime(100)
{
	if ( callerSequence == NULL ) {
		static int numberOfMainSequence;
		numberOfMainSequence++;
		if ( numberOfMainSequence > 1 ) 
			log.error() << "Only one MainSequence is possible. Use 'Sequence(S, caller, name)' to construct a normal sequence";
		else 
			setIsMainSequence();
	}
	
	//get and update callerStack
	if ( !getIsMainSequence() ) {
		callerStack = callerSequence->getCallerStack();
		callerStack.push_back(callerSequence);	//add latest caller
	}
	
	//callerStackBlocking gets created, when getCallerStackBlocking() is called
	
	addMonitor( &monitorTimeout );
}

int BaseSequence::actionFramework() {
	setRunningState( running );
	checkActiveException();		//sets RunningState according to activeException
	
	if ( callerSequence != NULL )
		if ( (runningState == running) && (callerSequence->getRunningState() == restarting) ) setRunningState( aborting );
	
	do {	//for reastarting
		if ( getRunningState() == restarting ) {	//sequence got restarted
			setRunningState( running );
			sequenceIsRestarting = false;
			resetTimeout();
			restartCounter++;
		}
		else restartCounter = 0;
		
// 		if( runningState == paused ) {	//has to be alerted by an other sequence
// 			usleep(pollingTime*1000);
// 		}
		
		double firstCheck = true;
		
		if ( checkPreCondition() ) {
		
			action();
			
			while ( runningState == running ) {
				if ( !firstCheck ) {
					if ( checkExitCondition() ) setRunningState(terminated);	//check exitCondition
					if ( runningState != terminated ) {
						checkMonitorsOfThisSequence();		//sets activeException if needed
						checkMonitorsOfBlockedCallers();	//sets activeException if needed
					}
				}
				else firstCheck = false;
				
				checkActiveException();					//sets RunningState according to activeException
				if ( runningState == running ) usleep(pollingTime*1000);
			}
		}
		else {	//checkPreCondition() failed
			setRunningState( terminated );
		}
	
	} while ( runningState == restarting );
	
	if ( runningState == aborting ) setRunningState(aborted);
	else setRunningState( terminated );
}

// Monitors
// ////////////////////////////////////////////////////////////////////////
void BaseSequence::addMonitor(Monitor* monitor)
{
	monitors.push_back( monitor );
}

std::vector< Monitor* > BaseSequence::getMonitors() const 
{
	return monitors;
}

void BaseSequence::checkMonitorsOfThisSequence()
{
	for ( Monitor* monitor : getMonitors() ) {
		checkMonitor(monitor);
	}
}

void BaseSequence::checkMonitorsOfBlockedCallers()
{
	for ( BaseSequence* seq : getCallerStackBlocking() ) {
		for ( Monitor* monitor : seq->getMonitors() ) {
			checkMonitor( monitor );
		}
	}
}

void BaseSequence::checkMonitor(Monitor* monitor)
{
	if ( monitor->checkCondition() == true ) {
		monitor->startExceptionSequence();
		switch( monitor->getBehavior() ) {
			case nothing :				break;
			case abortOwner : 			monitor->getOwner()->setActiveException( monitor );
										break;
			case restartOwner :			monitor->getOwner()->setActiveException( monitor );
										break;
			case abortCallerofOwner :	monitor->getOwner()->getCallerSequence()->setActiveException( monitor );
										break;
			case restartCallerOfOwner :	monitor->getOwner()->getCallerSequence()->setActiveException( monitor );
										break;
			default :					break;
		}
	}
	else return;
}

// Exceptions
// ////////////////////////////////////////////////////////////////////////

void BaseSequence::setActiveException(Monitor* activeMonitor)
{
	switch ( activeMonitor->getBehavior() ) {
		case abortOwner :
		case restartOwner :
			activeMonitor->getOwner()->exceptionIsActive = true;
			activeMonitor->getOwner()->activeException = activeMonitor;
			break;
		case abortCallerofOwner :
		case restartCallerOfOwner :	
			activeMonitor->getOwner()->getCallerSequence()->exceptionIsActive = true;
			activeMonitor->getOwner()->getCallerSequence()->activeException = activeMonitor;
			break;
		default : break;
	}
}

void BaseSequence::clearActiveException()
{
	exceptionIsActive = false;
	activeException = NULL;
}

void BaseSequence::checkActiveException()
{
	if ( exceptionIsActive == true ) {	// this sequence got the order to abort, restart ...
		switch( activeException->getBehavior() ) {
			case nothing :				break;
			case abortOwner : 			setRunningState(aborting);
										break;
			case restartOwner :			setRunningState(restarting);
										break;
			case abortCallerofOwner :	setRunningState(aborting);
										break;
			case restartCallerOfOwner : setRunningState(restarting);
										break;
			default : 					break;
		}
		clearActiveException();
	}
	else {								// a blocked caller got the order to abort, restart ...
		for ( BaseSequence* seq : getCallerStack() ) {
			if ( seq->exceptionIsActive == true ) {
				switch( seq->activeException->getBehavior() ) {
					case abortOwner :
					case restartOwner :
					case abortCallerofOwner :
					case restartCallerOfOwner :
												setRunningState(aborting);
												break;
					default : 					break;
				}
			}
		}
	}
}

// Sequence / Step
// ////////////////////////////////////////////////////////////////////////

bool BaseSequence::isStep() const
{
	return false;
}

bool BaseSequence::checkExitCondition()
{
	return true;
}

bool BaseSequence::checkPreCondition()
{
	return true;
}

void BaseSequence::setName(std::__cxx11::string name)
{
	this->name = name;
}

std::string BaseSequence::getName() const
{
	return name;
}

void BaseSequence::setID(int ID)
{
	sequenceID = ID;
}

int BaseSequence::getID() const
{
	return sequenceID;
}

void BaseSequence::setIsMainSequence()
{
	isMainSequence = true;
}
bool BaseSequence::getIsMainSequence() const
{
	return isMainSequence;
}

void BaseSequence::setIsBlocking()
{
	isBlocking = true;
}

void BaseSequence::setIsNonBlocking()
{
	isBlocking = false;
}

bool BaseSequence::getIsBlocking() const
{
	return isBlocking;
}

BaseSequence* BaseSequence::getCallerSequence()
{
	if( callerSequence == NULL ) {
		log.error() << "This sequence does not have a caller";
		return NULL;
	}
	else return callerSequence;
}

std::vector< BaseSequence* > BaseSequence::getCallerStack() const
{
	return callerStack;
}

std::vector< BaseSequence* > BaseSequence::getCallerStackBlocking()
{
	if ( !callerStackBlockingCreated ) createCallerStackBlocking();
	return callerStackBlocking;
}

void BaseSequence::createCallerStackBlocking()
{
	std::vector< BaseSequence* > tempStack;
	
	for ( int i = callerStack.size(); i--; ) {	//reverse iteration
		if ( callerStack[i]->getIsBlocking() ) tempStack.push_back(callerStack[i]);
		else break;
	}
	
	for ( int i = tempStack.size(); i--; ) {	//reverse vector
		callerStackBlocking.push_back(tempStack[i]);
		log.info() << "___callerStrackBlocking: " << tempStack[i]->getName();
	}
	callerStackBlockingCreated = true;
}

void BaseSequence::setRunningState(runningStateEnum runningState)
{
	this->runningState=runningState;
}

runningStateEnum BaseSequence::getRunningState() const
{
	return runningState;
}

void BaseSequence::restartSequence()
{
	setRunningState(restarting);
	sequenceIsRestarting = true;
}

void BaseSequence::setPollingTime(int timeInMilliseconds)
{
	pollingTime = timeInMilliseconds;
}

// Timeout	
// ////////////////////////////////////////////////////////////////////////////
void BaseSequence::setTimeoutTime(double timeoutInSec)
{
	conditionTimeout.setTimeoutTime(timeoutInSec);
}

void BaseSequence::resetTimeout()
{
	conditionTimeout.resetTimeout();
}

void BaseSequence::setTimeoutBehavior(behaviorEnum behavior)
{
	monitorTimeout.setBehavior(behavior);
}

void BaseSequence::setTimeoutExceptionSequence(BaseSequence* sequence)
{
	monitorTimeout.setExceptionSequence(sequence);
}


