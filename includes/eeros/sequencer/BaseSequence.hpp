#ifndef ORG_EEROS_SEQUENCER_BASESEQUENCE_HPP_
#define ORG_EEROS_SEQUENCER_BASESEQUENCE_HPP_

#include <vector>
#include <atomic>

#include <eeros/logger/Logger.hpp>
#include <eeros/logger/LogWriter.hpp>
#include <eeros/sequencer/EnumeratorsSequencer.hpp>
#include <eeros/sequencer/MonitorTimeout.hpp>
#include <eeros/sequencer/ConditionTimeout.hpp>


namespace eeros {
	namespace sequencer {
		
		class Sequencer;		//forward declaration
		class BaseSequence;
		
		class BaseSequence {			
		public:
			BaseSequence(Sequencer& S, BaseSequence* caller);
			
		// 	virtual int operator()(std::string args) = 0;	//has to be implemented in derived class			
			
			void restartSequence();
			void pauseSequence();
			
			
// // // 		// 	void addStopCondition(std::function<bool ()> f);
// // // 			virtual bool stopCondition();
// // // 			virtual bool checkExitCondition() = 0;
			
			virtual int start() = 0;
			virtual bool checkExitCondition();
			
		// 	virtual void set(std::string instruction, type value);	//TODO ??? polymorph or string
			
			
			virtual bool isStep() const;
			void setID(int ID);
			int getID() const;		//steps allways have ID=-99
			BaseSequence* getCallerSequence();
			std::vector< BaseSequence* > getCallerStack() const;
			std::vector< BaseSequence* > getCallerStackBlocking();	//creates callerStackBlocking if it is not already created
		// 	SequencerException& getSequencerException() const;
			bool getIsMainSequence() const;
			void setIsMainSequence();
			

			
			//TODO  moinitor exception timeout?....
			void setPollingTime(int timeInMilliseconds);
// // // 			void addMonitor(Monitor* monitor);
			
			std::string getState() const;
			void setState(std::string state);
			runningStateEnum getRunningState() const;
			void setRunningState(runningStateEnum runningState);
			
			std::string getName() const;
			void setName(std::string name);
		// 	void setCallerRunningState(runningStateEnum runningState);

			
			//TODO Timeout
		// 	bool checkTimeout();
		// 	bool checkTimeout(int sequenceID);
		// 	bool checkTimeout(BaseSequence* seqvuence);
		// 	bool checkTimeoutOfAllBlockedCallers();		//excluding "this" sequence, goes up to (but without) latest caller of a non blocking sequence
		// 	bool checkTimeoutOfThisSequence();
		// --> replaced with timeoutMonitor
			
		
			// Monitors
			// ////////////////////////////////////////////////////////////////////////
			std::vector< Monitor* > monitors;
			void addMonitor( Monitor* monitor);
			std::vector< Monitor* > getMonitors() const;
			
			// Timeout
			// ////////////////////////////////////////////////////////////////////////
			void setTimeoutTime(double timeoutInSec);		//in seconds. For this sequence
			void resetTimeout();
			void setTimeoutBehavior(behaviorEnum behavior);	//default is
			void setTimeoutExceptionSequence(BaseSequence* sequence);
			

		// 	
		// protected:
		// 	virtual void yield();
		// 	
		// 	virtual void init();
		// 	virtual void exit();
		// 	
// 			eeros::logger::Logger<eeros::logger::LogWriter> log;
			

			bool getIsBlocking() const;
			
		protected:
			Sequencer& S;			//reference to singleton Sequencer
			eeros::logger::Logger<eeros::logger::LogWriter> log;

			
			int actionFramework();			//handels different checks like preconditions
// 			int runBlocking();
// 			int runNonBlocking();
			// run mode:
			void setIsBlocking();		//standard run mode
			void setIsNonBlocking();
			
			void setActiveException( Monitor* activeMonitor );
			void clearActiveException();
			void checkActiveException();
			
			int pollingTime;					//in milliseconds for checkPostconditions (including monitors)
// 			int nrOfSequenceRepetitions = 1;	//number of repetitions of this sequence; 0==infinite; 1==run only once; 2==run once and repete once
													//sequence restarts are not counted
// 			int repetitionCounter = 0;		//how many times the sequence got repeted within a single run
// 			int runCounter = 0;	
// 			int timeoutsInARowCounter = 0;	//TODO when to reset??
			int restartCounter = 0;
			
			std::string state;				//TODO use enum,	userdefined
			
// 			std::atomic<runningStateEnum> runningState;	
// 			std::atomic<bool> isBlocking;			//standard run mode
			runningStateEnum runningState;	
			bool isBlocking;			//standard run mode
			
			
			
			
			std::vector< BaseSequence* > callerStack;	//vector with all caller sequences. Top element is latest caller
			std::vector< BaseSequence* > callerStackBlocking;	//TODO vector with all sequences, which are blocked with this sequence. Bottom element is the oldest blocked caller
			void createCallerStackBlocking();
			bool callerStackBlockingCreated = false;
			BaseSequence* callerSequence;
			
		// 	SequencerException& sequencerException;
			
// // // 			std::vector< Condition* > preconditions;
// // // 			std::vector< Condition* > postconditions;

			
			std::string name = "no Name";
			
		private:
// 			auto& cs;	Has to be added by the control engineer for derived sequences
// 			auto& ss;
			virtual int action() = 0;		//pure virtual function
			int sequenceID;
			bool isMainSequence = false;
			bool sequenceIsRestarting = false;
			
			bool exceptionIsActive = false;
			Monitor* activeException;
// // // 			void checkAllMonitors();
// // // 			void checkMonitorsOfThisSequence();
// // // 			void checkMonitorsOfAllCallers();
			
// // // 			auto startTime;
			
			ConditionTimeout conditionTimeout;
			MonitorTimeout monitorTimeout;
			
			void checkTimeoutMonitor();
			void checkMonitorsOfBlockedCallers();
			void checkMonitor(Monitor* monitor);
// 			double timeout;				//0 = not set or infinite
// // // 			Behavior::enumerator behaviorTimeout;
// // // 			TimeoutCondition timeoutCondition;
// // // 			Monitor timeoutMonitor;
// // // 			
// // // 			std::vector< *Monitor > monitors;
// // /*			
// // 			bool checkPreconditions();
// // 			bool checkPostconditions();
// // 			bool checkExceptionMonitors();*/
		};
		
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_BASESEQUENCE_HPP_