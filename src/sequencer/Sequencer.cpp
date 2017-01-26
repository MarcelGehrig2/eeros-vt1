#include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/Sequence.hpp>

using namespace eeros;
using namespace eeros::sequencer;

void Sequencer::addSequence(Sequence* seq)
{
	log.trace() << "Sequence '" << seq->getName() << "' added";
	sequenceList.push_back(seq);
}

void Sequencer::addMainSequence(Sequence* mainSeq)
{ 
	if ( mainSeq->isStep() ) log.error() << "MainSequence has to be a Sequence, not a Step";
	mainSequence = mainSeq;
	mainSequence->startMainSequence();
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

std::vector< Sequence* > Sequencer::getListOfAllSequences()
{
	return sequenceList;
}



























