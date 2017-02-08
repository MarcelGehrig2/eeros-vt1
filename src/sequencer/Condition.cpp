#include <eeros/sequencer/Condition.hpp>

using namespace eeros;
using namespace eeros::sequencer;


Condition::Condition(Sequencer& seq)
: S(seq)
{ }


bool Condition::isTrue()
{
	conditionState = validate();
	return conditionState;
}
