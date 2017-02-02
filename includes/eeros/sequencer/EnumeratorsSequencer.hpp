#ifndef ORG_EEROS_SEQUENCER_ENUMERATORSSEQUENCER_HPP_
#define ORG_EEROS_SEQUENCER_ENUMERATORSSEQUENCER_HPP_


namespace eeros {
	namespace sequencer {

		enum runningStateEnum {
			notSet,
			idle,
			running,
			paused,
			aborting,
			aborted,
			terminated,
			restartingStep,
			restarting,
		};	// terminatedWithWarning, terminatedBecauseCallerMonitor
		
		enum behaviorEnum {		//For Monitors
// 			notSet,
			repeteOwnerSequence,			//repete the owner sequence of this monitor
			repeteCallerOfOwnerSequence,	//repete the caller of the owner of this monitor
			repeteStep,						//repete step, which detects the exception
			abortOwnerSequence,
			abortCallerofOwnerSequence,
			abortStep,
			pause,							//pause, till condition==false
			goTo,
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif	// ORG_EEROS_SEQUENCER_ENUMERATORSSEQUENCER_HPP_