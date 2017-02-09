#include <eeros/sequencer/Sequence.hpp>
#include <eeros/sequencer/Sequencer.hpp>

using namespace eeros;
using namespace eeros::sequencer;


Sequence::Sequence(Sequencer& S, std::__cxx11::string name)
: Sequence(S, NULL, name) { }


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
	
	log.trace() << "Sequence '" << name << "' created";
}

void Sequence::run()	//runs in thread
{
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk);							//sends Sequence to sleep. Waiting for start()
	lk.unlock();
	if ( getIsMainSequence()) log.trace() << "Sequence '" << name << "' started non-blocking.";
	else log.trace() << "Sequence '" << name << "' started non-blocking. CallerSequence: " << callerSequence->getName();
	actionFramework();
	log.trace() << "Sequence '" << name << "' terminated";
}

int Sequence::start()
{
	resetTimeout();
	
	if ( getIsBlocking() ) {	//starts action() blocking
		if ( getIsMainSequence()) log.trace() << "Sequence '" << name << "' started blocking.";
		else log.trace() << "Sequence '" << name << "' started blocking. CallerSequence: " << callerSequence->getName();
		actionFramework();				//action gets overwritten by child class
		log.trace() << "Sequence '" << name << "' terminated";
	}
	else {
		cv.notify_one();		//starts actionFramework() in thread
	}
	
	return 0;
}

int Sequence::startMainSequence()
{
	cv.notify_one();		//starts actionFramework() in thread
}

bool Sequence::isStep()
{
	return false;
}

