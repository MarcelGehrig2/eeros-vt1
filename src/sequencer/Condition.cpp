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





// Condition::Condition(Sequencer& seq, Condition::validateStyleEnum)
// : S(seq),
// {
// 
// }

// Condition::Condition(Sequencer& seq) : S(seq)
// {
// 	S.addCondition(this);
// }


// bool getConditionState() {
// 	checkCondition();
// 	return conditionState;
// };

// bool Condition::operator()()
// {
// 	return check();
// }


// bool Condition::check()
// {
// 	validate();
// 	
// 	return conditionState;
// }
// 

