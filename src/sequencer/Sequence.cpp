#include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/Sequence.hpp>
#include <eeros/sequencer/BaseSequence.hpp>

using namespace eeros;
using namespace eeros::sequencer;

Sequence::Sequence(Sequencer& S, std::__cxx11::string name)
: Sequence(S, NULL, name)
{log.info() << "tralala"; }


Sequence::Sequence(Sequencer& S, BaseSequence* caller, std::__cxx11::string name)
: BaseSequence(S, caller)
{
	
	static int sequenceCount;
	setID(sequenceCount++);	//TODO check how many Sequence-Objects of this type are allowed. Maybe singleton.
	if (name == "") {
		log.error() << "All sequences must have a name";
	} else {
		for ( Sequence *seq : S.getListOfAllSequences() ) {
			if ( this->name == seq->getName() ) log.error() << "All sequences must have different names"; 
		}
		this->name = name;
	}
	
	S.addSequence(this);	//register this new Sequence-Object in Sequencer
	if ( this->getIsBlocking() )
		log.trace() << "Sequence '" << name << "' created and is blocking";
	else
		log.trace() << "Sequence '" << name << "' created and is not blocking";
	
}

Sequence::~Sequence()
{
	//TODO remove this sequence from list in Sequencer
}

void Sequence::run()	//runs in thread
{
	log.trace() << "Sequence '" << name << "' run() started";	
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk);							//sends Sequence to sleep. Waiting for start()
	lk.unlock();
	log.trace() << "Sequence '" << name << "' action";
	actionFramework();
	log.trace() << "Sequence '" << name << "' run() ended";
}

int Sequence::start()
{
	resetTimeout();
	
	if ( getIsBlocking() ) {	//starts action() blocking
		log.trace() << "Sequence '" << name << "' blocking action(). CallerSequence: " << callerSequence->getName();
		actionFramework();				//action gets overwritten by child class
		log.trace() << "Sequence '" << name << "' blocking action() ended. CallerSequence: " << callerSequence->getName();
	}
	else {
		log.trace() << "Sequence '" << name << "' nonblocking action()";
		cv.notify_one();		//starts actionFramework() in thread
	}
	
	return 0;
}

int Sequence::startMainSequence()
{
// 	log.trace() << "Sequence::startMainSequence()      1";
	cv.notify_one();		//starts actionFramework() in thread
}

// bool Sequence::sleepMSec(int msec)
// {
// 	std::this_thread::sleep_for(std::chrono::milliseconds(msec));	//TODO Check Monitors (of callers) while sleeping!
// }

bool Sequence::isStep()
{
	return false;
}

// BaseSequence* Sequence::getLatestCalledSequence()
// {
// 	return latestCalledSequence;
// }


