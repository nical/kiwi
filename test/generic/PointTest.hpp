#include "generic/Point.hpp"
#include "core/Commons.hpp"
#include <assert.h>

#include "utils/types.hpp"

using namespace kiwi;


template<typename T, unsigned D>
void PointTest()
{
	typedef kiwi::generic::Point<T,D> pointnd;

	ScopedBlockMacro(__scop, "kiwi::TestPoint");
		debug.print() << "init -----------------" << endl();
	pointnd p1(1,5);
	pointnd p2(42,4);
	pointnd p3(43,9);
	pointnd pzero(0.0);
	pointnd pzero2 = pointnd::zero();
	pointnd copy(p3);
	pointnd eq = p1;
		debug.print() << "assert ---------------" << endl();
	assert(p1 != p2);
	assert(p1+p2 == p3);
	assert(p1-p1 == pzero);
	assert(pzero == pzero2);
	assert(p1 == p1);
	assert(p2 == p2);
	assert(eq == p1);
	assert(copy == p3);

	for(unsigned i = 0; i < D; ++i) assert( p2[i]==p2(i) );
	
	debug.print() << " Point tests : success !" << endl();

}
