// #include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/Sequence.hpp>

using namespace eeros;
using namespace eeros::sequencer;

Sequence::Sequence(Sequencer& S, Sequence* caller, std::__cxx11::string name)
: created(false), S(S), name(name), caller(caller)
{
	
}


void Sequence::run()
{
	log.trace() << "Sequence '" << name << "' run() started";
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk);
	action();
	log.trace() << "Sequence '" << name << "' run() ended";
}

void Sequence::start()
{
	cv.notify_one();
}


std::string Sequence::getName()
{
	return name;
}
