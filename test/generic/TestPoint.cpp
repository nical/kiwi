#include "generic/Point.hpp"
#include "core/Commons.hpp"
#include <assert.h>
int main()
{

typedef kiwi::generic::Point<int,2> point2D;

//ScopedBlockMacro(s1, "kiwi::TestPoint");
	
	point2D p1(1,5);
	point2D p2(42,-4);
	point2D p3(43,1);
	point2D zero(0);
	point2D copy(p3);

	assert(p1+p2 == p3);
	assert(p1-p1 == zero);
	assert(p1 == p1);
	assert(p2 == p2);
	assert(copy == p3);
//	debug.print() << p.coordinate(0)<<endl;




return 0;
}
