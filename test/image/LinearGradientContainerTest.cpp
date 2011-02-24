
#include "kiwi/image/LinearGradientContainer.hpp"

using namespace kiwi;
using namespace kiwi::image;

void LinearGradientContainerTest(){

	typedef LinearGradientContainer<kiwi::uint8_t,2,float> GradientContainer;
	typedef GradientContainer::PointType Point;
	
	GradientContainer gradient1( Point(50,0), 0,  Point(400,200), 250 );

	

}



int main()
{
	ScopedBlockMacro(scop,"LinearGradientContainer::Test")
	LinearGradientContainerTest();
	return 0;
}
