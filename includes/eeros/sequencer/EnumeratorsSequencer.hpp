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
			nothing,					//do nothing. (only exception sequence is called, if available)
// 			notSet,
			abortOwner,
			restartOwner,				//restart the owner sequence or step of this monitor
			abortCallerofOwner,
			restartCallerOfOwner,		//restart the caller of the owner of this monitor
// 			restartStep,				//restart step, which detects the exception
// 			abortStep,
// 			pause,						//pause, till condition==false
// 			goTo,
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif	// ORG_EEROS_SEQUENCER_ENUMERATORSSEQUENCER_HPP_