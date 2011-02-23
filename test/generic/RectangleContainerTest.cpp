
#include "kiwi/generic/RectangleContainer.hpp"


using namespace kiwi;
using namespace kiwi::generic;

void RectangleContainerTest()
{
	typedef RectangleContainer<2>::PointType Point;
	RectangleContainer<2> rect(Point(0,0),Point(800,600));

	assert( rect.getPosition() == Point(0,0) );
	assert( rect.getSize() == Point(800,600) );

	rect.setPosition( Point(42,12) );
	assert( rect.getPosition() == Point(42,12) );

}


int main()
{
	ScopedBlockMacro(scop,"RectangleContainer::Test");
	RectangleContainerTest();
}
