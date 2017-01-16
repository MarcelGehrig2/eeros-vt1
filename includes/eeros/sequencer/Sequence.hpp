#ifndef ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
#define ORG_EEROS_SEQUENCER_SEQUENCE_HPP_


#include <condition_variable>
// #include <string>
// #include <map>
// #include <functional>
// #include <vector>
// #include <mutex>
// #include <condition_variable>
// #include <atomic>
// 
// #include <eeros/logger/Logger.hpp>
// #include <eeros/logger/LogWriter.hpp>
// #include <eeros/sequencer/Sequencer.hpp>
// #include <eeros/sequencer/SequenceResult.hpp>
#include "eeros/core/Thread.hpp"
#include <eeros/sequencer/Sequencer.hpp>

namespace eeros {
	namespace sequencer {
	
	class Sequencer;		//forward declaration
	
	class Sequence : public Thread {
	public:
// 		Sequence();
		Sequence(Sequencer& S, Sequence* caller, std::string name);
	// 	~Sequence();
		
		virtual void run() = 0;
	// 	virtual void action();
		std::string getName();
		
	// 	void addSequence
		
		std::string name;
		Sequencer& S;
		
		std::mutex m;
		std::condition_variable cv;
		Sequence* caller;
		bool blocking = false;
	};
	
	};	//namespace sequencer
}; // namespace eeros

#endif // ORG_EEROS_SEQUENCER_SEQUENCE_HPP_
