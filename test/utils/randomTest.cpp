

#include "kiwi/utils/random.hpp"
#include "kiwi/generic/Point.hpp"


using namespace kiwi;
using namespace kiwi::utils;

int main()
{
	Debug::init(true, true);
	ScopedBlockMacro( "random::Test");
	float totf = 0;
	int toti = 0;
	for(int i = 0; i < 100; ++i)
	{
		float rf = kiwi::utils::random::generate<float>(1.0);
		int ri = kiwi::utils::random::generate<int>(100);
		totf += rf;
		toti += ri;
		assert(rf >= 0.0);
		assert(rf <= 1.0);
		assert(ri >= 0);
		assert(ri <= 100);
	}
	totf = totf / 100.f;
	toti = toti / 100;

	assert( totf > 0.4 );
	assert( totf < 0.6 );
	assert( toti > 40 );
	assert( toti < 60 );
	
	Debug::print() << "average float rand value: " << totf << endl();


	return 0;
}
