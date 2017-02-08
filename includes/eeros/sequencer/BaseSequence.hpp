#ifndef ORG_EEROS_SEQUENCER_BASESEQUENCE_HPP_
#define ORG_EEROS_SEQUENCER_BASESEQUENCE_HPP_

#include <vector>

#include <eeros/logger/Logger.hpp>
#include <eeros/logger/LogWriter.hpp>
#include <eeros/sequencer/EnumeratorsSequencer.hpp>
#include <eeros/sequencer/ConditionTimeout.hpp>
#include <eeros/sequencer/Monitor.hpp>


namespace eeros {
	namespace sequencer {
		
		class Sequencer;		//forward declaration
		class BaseSequence;
		
		class BaseSequence {			
		public:
			BaseSequence(Sequencer& S, BaseSequence* caller);
			
		// 	virtual int operator()(std::string args) = 0;	//has to be implemented in derived class
			
// 			void pauseSequence();	not yet implemented
// 			void resumeSequence();	not yet implemented
			
			// This functions can be overwritten by a userdefinde, derived class
			// ////////////////////////////////////////////////////////////////////////
			virtual int start() = 0;
			virtual bool checkPreCondition();
			virtual bool checkExitCondition();
			
			
			virtual bool isStep() const;
			
			void setName(std::string name);
			std::string getName() const;
			
			void setID(int ID);
			int getID() const;		//steps allways have ID=-99
			
			void setIsMainSequence();
			bool getIsMainSequence() const;
			
			void setIsBlocking();		//standard run mode
			void setIsNonBlocking();
			bool getIsBlocking() const;
			
			BaseSequence* getCallerSequence();
			std::vector< BaseSequence* > getCallerStack() const;
			std::vector< BaseSequence* > getCallerStackBlocking();	//creates callerStackBlocking if it is not already created
			
			void setRunningState(runningStateEnum runningState);
			runningStateEnum getRunningState() const;
			void restartSequence();
			
			void setPollingTime(int timeInMilliseconds);
			
			// Monitors
			// ////////////////////////////////////////////////////////////////////////
			std::vector< Monitor* > monitors;
			void addMonitor( Monitor* monitor);
			std::vector< Monitor* > getMonitors() const;
			
			// Timeout
			// ////////////////////////////////////////////////////////////////////////
			void setTimeoutTime(double timeoutInSec);		//in seconds. For this sequence
			void resetTimeout();
			void setTimeoutBehavior(behaviorEnum behavior);	
			void setTimeoutExceptionSequence(BaseSequence* sequence);
			
			
		protected:
			int actionFramework();		//handels different checks like preconditions
			
			Sequencer& S;				//reference to singleton Sequencer
			
			eeros::logger::Logger<eeros::logger::LogWriter> log;
			
			std::string name = "Steps do not have a name";	//constructor of "Sequence" overwrites name
			
			runningStateEnum runningState;	
			bool isBlocking;			//standard run mode
			
			BaseSequence* callerSequence;
			
		private:
			virtual int action() = 0;	//overwritten by "Sequence" and "Step"
			
			void createCallerStackBlocking();
			
			void checkMonitorsOfBlockedCallers();
			void checkMonitorsOfThisSequence();
			void checkMonitor(Monitor* monitor);
			
			void setActiveException( Monitor* activeMonitor );
			void clearActiveException();
			void checkActiveException();
			
			
			int sequenceID;
			bool isMainSequence = false;
			bool sequenceIsRestarting = false;
			
			std::vector< BaseSequence* > callerStack;			//vector with all caller sequences. Top element is latest caller
			std::vector< BaseSequence* > callerStackBlocking;	//vector with all sequences, which are blocked by this sequence. Element[0] is the oldest blocked caller
			bool callerStackBlockingCreated = false;
			
			Monitor monitorTimeout;
			ConditionTimeout conditionTimeout;
			
			int restartCounter = 0;
			int pollingTime;		//in milliseconds for checkExitCondition monitors)
			
			bool exceptionIsActive = false;
			Monitor* activeException;
			
			
		};
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_BASESEQUENCE_HPP_