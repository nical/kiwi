

#include "kiwi/utils/random.hpp"
#include "kiwi/generic/Point.hpp"


using namespace kiwi;
using namespace kiwi::utils;

int main()
{
	Debug::init(true, true);
	ScopedBlockMacro(__scop_, "random::Test");
	float totf = 0;
	for(int i = 0; i < 100; ++i)
	{
		float rf = random::generate<float>();
		totf += rf;
		Debug::print() << rf << endl();
		Debug::print() << random::generate<int>() << endl();
		//Debug::print() << random::generate<generic::Point<2,int>()[0] << endl();
	}
	totf = totf / 100.f;

	Debug::print() << "average float rand value: " << totf << endl();


	return 0;
}
