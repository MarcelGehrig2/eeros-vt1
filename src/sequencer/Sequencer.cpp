#include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/Sequence.hpp>

using namespace eeros;
using namespace eeros::sequencer;


Sequencer::Sequencer()
: SS(NULL)
{
	static int sequencerCounter;
	sequencerCounter++;
	if ( sequencerCounter > 1 ) log.error() << "Only one sequencer object is allowed";
}

Sequencer::Sequencer(SafetySystem* SS)
: SS(SS) { }

void Sequencer::addSequence(Sequence* seq)
{
	sequenceList.push_back(seq);
}

void Sequencer::addMainSequence(Sequence* mainSeq)
{ 
	if ( mainSeq->isStep() ) log.error() << "MainSequence has to be a Sequence, not a Step";
	mainSequence = mainSeq;
	mainSequence->startMainSequence();
}

Sequence* Sequencer::getMainSequence()
{
	if( mainSequence == NULL ) log.error() << "MainSequence not set in Sequencer";
	return mainSequence;
}

Sequence* Sequencer::getSequenceByID(int ID)
{
	for ( Sequence *seq : getListOfAllSequences() ) {
		if ( ID == seq->getID() ) return seq;
	}
	log.error() << "No sequence with ID '" << ID << "' found.";
	return NULL;
}

Sequence* Sequencer::getSeqenceByName(std::__cxx11::string name)
{
	for ( Sequence *seq : getListOfAllSequences() ) {
		if ( name == seq->getName() ) return seq;
	}
	log.error() << "No sequence with name '" << name << "' found.";
	return NULL;
}

void Sequencer::setSafetySystem(SafetySystem* SS)
{
	this->SS = SS;
}

SafetySystem* Sequencer::getSafetySystem()
{
	if( SS == NULL ) log.error() << "SafetySystem not set in Sequencer";
	return SS;
}

std::vector< Sequence* > Sequencer::getListOfAllSequences()
{
	return sequenceList;
}

std::string Sequencer::getName() const
{
	std::string name = "Sequencer";		//included for backwards compatibelity. Only 1 Sequencer can be used.
	return name;
}

state::type Sequencer::getState() const
{
	return state;
}

mode::type Sequencer::getMode() const
{
	return mode;
}



























