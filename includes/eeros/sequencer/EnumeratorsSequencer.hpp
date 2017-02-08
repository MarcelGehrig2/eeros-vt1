#ifndef ORG_EEROS_SEQUENCER_ENUMERATORSSEQUENCER_HPP_
#define ORG_EEROS_SEQUENCER_ENUMERATORSSEQUENCER_HPP_


namespace eeros {
	namespace sequencer {

		enum runningStateEnum {
			idle,
			running,
			paused,
			aborting,
			aborted,
			terminated,
			restarting,
		};
		
		enum behaviorEnum {		//For Monitors
			nothing,					//do nothing. (only exception sequence is called, if available)
			abortOwner,					//abort the owner sequence or step of this monitor
			restartOwner,				//restart the owner sequence or step of this monitor
			abortCallerofOwner,			//abort the caller of the owner of this monitor
			restartCallerOfOwner,		//restart the caller of the owner of this monitor
// 			paused,						//pause, till condition==false
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif	// ORG_EEROS_SEQUENCER_ENUMERATORSSEQUENCER_HPP_