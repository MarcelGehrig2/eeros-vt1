#include <eeros/sequencer/Step.hpp>

using namespace eeros;
using namespace eeros::sequencer;

Step::Step(Sequencer& S, BaseSequence* caller): BaseSequence(S, caller)
{

}

bool Step::isStep() const
{
	return true;
}

int Step::start()
{
	resetTimeout();
	actionFramework();
	return 0;
}


