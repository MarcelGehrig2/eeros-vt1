#include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/Sequence.hpp>
#include <eeros/sequencer/BaseSequence.hpp>
// #include <eeros/sequencer/Sequence.hpp>
// #include <eeros/core/EEROSException.hpp>
// #include <cstdio>

using namespace eeros;
using namespace eeros::sequencer;

// int Sequencer::instanceCounter = 0;

void Sequencer::addMainSequence(BaseSequence* mainSeq)
{ 
	if ( mainSeq->isStep() ) log.error() << "MainSequence has to be a Sequence, not a Step";
	mainSequence = mainSeq;
// 	std::this_thread::sleep_for(std::chrono::milliseconds(150));	//
	mainSequence->start();	
}



void Sequencer::addSequence(BaseSequence* seq)
{
	sequenceList.push_back(seq);
}

void Sequencer::run()
{
	
// 	mainSequence->join();
}







state::type Sequencer::getState() const {
	return state;
}

mode::type Sequencer::getMode() const {
	return mode;
}

std::string Sequencer::getName() const {
	std::string name = "Sequencer";		//included for backwards compatibelity. Only 1 Sequencer can be used.
	return std::string(name);
}






























