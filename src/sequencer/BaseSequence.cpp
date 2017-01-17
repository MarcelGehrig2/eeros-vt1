




// ////////////////////////////////////////////////////////////////////////////
//
//	BaseSequence.cpp is included in Sequence.cpp. Prevents "invalid use of incomplete type" Error
//
// ////////////////////////////////////////////////////////////////////////////











// #include <eeros/sequencer/BaseSequence.hpp>
// // #include <eeros/sequencer/Sequencer.hpp>
// // #include "SequencerException.hpp"
// // #include "Sequencer.hpp"
// #include <thread>
// #include <chrono>
// 
// using namespace eeros;
// using namespace eeros::sequencer;
// 
// BaseSequence::BaseSequence(Sequencer& S, BaseSequence* caller)
// // : S(S), startTime(std::chrono::steady_clock::now()), callerSequence(caller)
// : S(S), callerSequence(caller)
// { 
// 
// 	
// 	setState("idle");
// 	
// 
// 	
// 	
// 	//get and update callerStack
// 	callerStack = callerSequence->getCallerStack();
// 	callerStack.push_back(callerSequence);	//add latest caller
// 	
// 	//get and update callerStackBlocking
// 	//TODO
// 	
// 	
// // // // 	//inherit SequencerException from caller
// // // // 	//TODO if mainSequence no caller exists
// // // // 	sequencerException = callerSequence->getSequencerException();
// 	
// 	
// 	setPollingTime(10);
// 	
// 	//timeout
// // // // 	timeout = 0;	//0 == not set == no timeout
// // // // 	behaviorTimeout = Behavior::abortOwnerSequence;
// // // // 	timeoutCondition( S, timeout );
// // // // 	timeoutMonitor( this, &timeoutCondition, behaviorTimeout );
// // // // 	addMonitor( &timeoutMonitor ) ;
// }
// 
// // // // int BaseSequence::runBlocking()
// // // // {
// // // // 	setIsBlocking();
// // // // 	
// // // // 	// 1 Check precondition
// // // // 	// ////////////////////
// // // // 	bool preconditionsPass = checkPreconditions();	//including monitors of all caller
// // // // 	
// // // // 	
// // // // 	if( preconditionsPass ) {		//checkPreconditions did not change the runningState
// // // // 	
// // // // 		// 2 Action
// // // // 		// ////////
// // // // 		action();		//Send action to Controlsystem and or Safetysystem.
// // // // 						//Send signal to other sequence
// // // // 						//Star a Sequence
// // // // 		
// // // // 		
// // // // 		
// // // // 		
// // // // 		// 3 Check postcondition
// // // // 		// /////////////////////
// // // // 		while(runningState == "running") {
// // // // 			if(runningState == "running") checkExitCondition();	//used for normal stop of this step/sequence 
// // // // 			
// // // // 			if(runningState == "running") checkTimeoutOfAllBlockedCallers();	//if caller timeout -> error thrown
// // // // 			if(runningState == "running") checkTimeoutOfThisSequence(); //if true -> timeoutAction()
// // // // 			
// // // // 			if(runningState == "running") checkMonitorsOfAllCallers();		//of all callers
// // // // 			if(runningState == "running") checkMonitorsOfThisSequence();	//of all callers
// // // // 		// 	checkPause();			//TODO or us a global Condition instead?
// // // // 		// 	checkStop();			//TODO a condition as well?
// // // // 			std::this_thread::sleep_for (std::chrono::milliseconds(pollingTime));
// // // // 		}
// // // // 	}
// // // // 
// // // // }
// 
// // // // int BaseSequence::runNonBlocking()
// // // // {
// // // // 	setIsNonBlocking();
// // // // 	
// // // // }
// 
// // // // int BaseSequence::run()
// // // // {
// // 	bool execute = true;
// // 	if (	   ( callerSequence->getRunningState() == terminated )
// // 			&& ( true ) );
// 	
// // // // 	// if sequencerException is active: abort or repete sequence, depending on exception behavior:
// // // // 	sequencerException->setRunningStateOfThisSequence(this);
// // // // 
// // // // 	
// // // // 	if ( runningState != aborting ) {
// // // // 		runCounter++;
// // // // 		
// // // // 		if ( callerSequence->runningState == running ) {
// // // // 			repetitionCounter=0;
// // // // 			
// // // // 			// while loop, if multiple repetition OR this sequence is RESTARTED
// // // // 			while ( ( nrOfSequenceRepetitions==0 ) || (repetitionCounter <= nrOfSequenceRepetitions) ) {
// // // // 				repetitionCounter ++;
// // // // 				
// // // // 				
// // // // 				//RUN
// // // // 				if (getIsBlocking()) { runBlocking(); }
// // // // 				else { runNonBlocking(); }
// // // // 				
// // // // 				
// // // // 				// if sequencerException is active: abort or repete sequence, depending on exception behavior:
// // // // 				sequencerException->setRunningStateOfThisSequence(this);
// // // // 				if ( runningState == restarting ) {
// // // // 					runningState = running;
// // // // 				}
// // // // 				if ( runningState == aborting )	break;
// // // // 			}
// // // // 		}
// // // // 		
// // // // 		if ( runningState == aborting ) runningState = aborted;
// // // // 		else runningState = terminated;	//TODO terminated with warning/error?
// // // // 	}
// // // /*	
// // // }*/
// 
// // int BaseSequence::start()
// // {
// // 	run();
// // }
// 
// 
// 
// void BaseSequence::setPollingTime(int timeInMilliseconds)
// {
// 	pollingTime = timeInMilliseconds;
// }
// 
// // void BaseSequence::addMonitor(Monitor* monitor)
// // {
// // 	monitors.push_back(monitor);
// // }
// 
// 
// bool BaseSequence::isStep() const
// {
// 	return false;
// }
// 
// 
// // bool BaseSequence::checkPreconditions()
// // {
// // 	bool fail;		//TODO
// // 	
// // 	checkAllMonitors();		// can change runningState
// // 	
// // 	if ( runningState != running ) fail = true; 
// // 	
// // 	//TODO what happens, if this sequence could resolve??
// // 
// // 	return !fail;
// // }
// 
// 
// BaseSequence* BaseSequence::getCallerSequence() const
// {
// 	return callerSequence;
// }
// 
// // // // bool BaseSequence::stopCondition()
// // // // {
// // // // 	return true;	// Sequence is immediately stopped after action is performed.
// // // // }
// 
// void BaseSequence::setIsBlocking()
// {
// 	isBlocking = true;
// }
// 
// void BaseSequence::setIsNonBlocking()
// {
// 	isBlocking = false;
// }
// 
// bool BaseSequence::getIsBlocking() const
// {
// 	return isBlocking;
// }
// 
// std::string BaseSequence::getState() const
// {
// 	return state;
// }
// 
// void BaseSequence::setState(std::string state)
// {
// 	this->state = state;
// }
// 
// runningStateEnum BaseSequence::getRunningState() const
// {
// 	return runningState;
// }
// 
// void BaseSequence::setRunningState(runningStateEnum runningState)
// {
// 	this->runningState=runningState;
// }
// 
// std::vector< BaseSequence* > BaseSequence::getCallerStack() const
// {
// 	return callerStack;
// }
// 
// std::vector< BaseSequence* > BaseSequence::getCallerStackBlocking() const
// {
// 	return callerStackBlocking;
// }
// 
// 
// // SequencerException& BaseSequence::getSequencerException() const
// // {
// // 	return sequencerException;
// // }
// 
// void BaseSequence::setID(int ID)
// {
// 	sequenceID = ID;
// }
// 
// 
// int BaseSequence::getID() const
// {
// 	return sequenceID;
// }
// 
// void BaseSequence::restartSequence()
// {
// 	state="restarting";
// }
// 
// 
// 
// // // // //Timeout handling
// // // // bool BaseSequence::checkTimeoutOfThisSequence()
// // // // {
// // // // 	//TODO this sequences timout, detected by a sub sequence. now clear exception and do timeout action. 
// // // // 	//clear error, if it is caused by a called seqeuence, beacause of the timeout of this seqeuence
// // // // 	if ( S.getSeqencerException()->isSet() ) {
// // // // 		if ( ( S.getSeqencerException()->getRootSequence() == this ) && ( S.getSeqencerException()->getExceptionDescription() == "timeout" ) ) {
// // // // 			S.getSeqencerException()->clearException();
// // // // 		}
// // // // 	}
// // // // 	
// // // // // 	return checkTimeout(this);	//TODO
// // // // }
// // // // 
// // // // bool BaseSequence::checkTimeout(int sequenceID)
// // // // {
// // // // 	BaseSequence* sequence = S.getSequenceByID(sequenceID);
// // // // 	return checkTimeout(&sequence);
// // // // }
// // // // 
// // // // bool BaseSequence::checkTimeout(BaseSequence* sequence)
// // // // {
// // // // 	//TODO implement Timeout check
// // // // 	if (sequence->timeout > 0) {
// // // // 		auto now = std::chrono::steady_clock::now();
// // // // 		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - sequence->startTime) > sequence->timeout) return true;
// // // // 		else return false;
// // // // 	}
// // // // 	// 	sequence->getStartOfTimeout;
// // // // // 	sequence->getTotalTimeoutTime;
// // // // }
// // // // 
// // // // 	
// // // // bool BaseSequence::checkTimeoutOfAllBlockedCallers()	//does not check timeout of "this"
// // // // {
// // // // 	//TODO if callerTimeout happens, throw sequencer exception. the caller sequence handles than the timeout action.
// // // // 	//TODO non blocking seqeuences should not inherit timeouts --> outer iterator
// // // // 	//TODO how do the list iterator exactly work?
// // // // 	//lates (newest) caller of a non blocking call. Timeouts of this caller and older callers are ignored
// // // // 	
// // // // 	bool isTimeout = false;
// // // // // 	for (std::list<int>::const_iterator iterator = callerStack.end(), end = callerStack.begin(); iterator != end; --iterator) {
// // // // // // 		int a = iterator.operator*();
// // // // // 		if ( (!(S.getSequenceByID(iterator.operator*())->getIsBlocking)) | (iterator == callerStack.begin()) {	//latest caller of a non blocking sequence, or first sequence
// // // // // 			for (iterator, end = callerStack.end(); iterator != end; ++iterator) {
// // // // // 				isTimeout = isTimeout | checkTimeout(*iterator);
// // // // // 			}
// // // // // 		}
// // // // // 	}
// // // // 	return isTimeout;		//if true, at least on1 timeout occoured
// // // // }
// // // // 
// // // // bool BaseSequence::timeoutAction()
// // // // {
// // // // 	S.sequencerError.throwError();
// // // // }
// 
// 
// // // // // Timeout	(is a monitor)
// // // // // ////////////////////////////////////////////////////////////////////////////
// // // // 
// // // // void BaseSequence::setTimeoutTime(double timeoutInSec)
// // // // {
// // // // 	timeoutCondition.setTime(timeoutInSec);
// // // // }
// // // // 
// // // // void BaseSequence::setTimeoutBehavior(Behavior::enumerator behavior)
// // // // {
// // // // 	timeoutMonitor.setBehavior(behavior);
// // // // }
// // // // 
// // // // void BaseSequence::setTimeoutExceptionSequence(Sequence* sequence)
// // // // {
// // // // 	timeoutMonitor.setExceptionSequence(sequence);
// // // // }
// // // // 
// // // // void BaseSequence::resetTimeout()
// // // // {
// // // // 	timeoutCondition.resetTimeout();
// // // // }
// 
// 
// 
// void BaseSequence::pauseSequence()
// {
// 
// }
// 
// 
// 
// 
// 
