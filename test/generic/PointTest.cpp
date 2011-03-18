#ifndef KIWI_POINT_TEST
#define KIWI_POINT_TEST

#include "kiwi/generic/Point.hpp"
#include "kiwi/core/Commons.hpp"
#include <assert.h>

#include "kiwi/utils/types.hpp"

using namespace kiwi;


template<typename T, unsigned D>
void PointTest()
{
	typedef kiwi::generic::Point<T,D> pointnd;

	ScopedBlockMacro("kiwi::TestPoint");
		Debug::print() << "init -----------------" << endl();
	pointnd p1(1,5);
	pointnd p2(42,4);
	pointnd p3(43,9);
	pointnd pzero(0.0);
	pointnd pzero2 = pointnd::zero();
	pointnd copy(p3);
	pointnd eq = p1;
		Debug::print() << "assert ---------------" << endl();
	assert(p1 != p2);
	assert(p1+p2 == p3);
	assert(p1-p1 == pzero);
	assert(pzero == pzero2);
	assert(p1 == p1);
	assert(p2 == p2);
	assert(eq == p1);
	assert(copy == p3);

	for(unsigned i = 0; i < D; ++i) assert( p2[i]==p2(i) );
	
	Debug::print() << " Point tests : success !" << endl();

}


#ifdef KIWI_TEST_MAIN

int main()
{
	PointTest<char,2>();
	PointTest<float,3>();
	PointTest<double,4>();
	PointTest<unsigned int,3>();
	return 0;
}

#endif


#endif
