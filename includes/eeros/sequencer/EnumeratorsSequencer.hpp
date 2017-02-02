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
			restartOwner,					//restart the owner sequence or step of this monitor
			nothing,						//do nothing. (only exception sequence is called, if available)
// 			restartCallerOfOwnerSequence,	//restart the caller of the owner of this monitor
// 			restartStep,						//restart step, which detects the exception
			abortOwner,
// 			abortCallerofOwnerSequence,
// 			abortStep,
// 			pause,							//pause, till condition==false
// 			goTo,
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif	// ORG_EEROS_SEQUENCER_ENUMERATORSSEQUENCER_HPP_