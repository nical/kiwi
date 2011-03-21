
#include "kiwi/image/LinearGradientContainer.hpp"
#include "kiwi/image/cairo/ImageContainer.hpp"
#include "kiwi/image/CopyImageFilter.hpp"

using namespace kiwi;
using namespace kiwi::image;

void LinearGradientContainerTest(){

	typedef LinearGradientContainer<kiwi::uint8_t,2,kiwi::uint32_t> GradientContainer;
	typedef GradientContainer::PointType Point;
	
	image::LinearGradientContainer<kiwi::uint8_t,2,kiwi::uint32_t>
		gradient1( Point(0,0), 0,  Point(600,10), 255 );

	//kiwi::core::Container* test = dynamic_cast<kiwi::core::Container>(gradient)

	kiwi::core::DynamicNode gradient1Node( &gradient1 );

	cairo::RGBAImageContainer inputData("inputImageTransp.png");
	kiwi::core::DynamicNode inputDataNode(&inputData);
		
	cairo::RGBAImageContainer result("inputImageTransp.png" );	
	kiwi::core::DynamicNode resultNode(&result);

	CopyImageFilter filter;

	gradient1Node.dataPort(0)			 >> filter.readerPort(0);
	gradient1Node.dataPort(0) 			 >> filter.readerPort(1);
	gradient1Node.dataPort(0)			 >> filter.readerPort(2);
	inputDataNode.dataPort(0).subPort(3) >> filter.readerPort(3);

	resultNode.dataPort(0) >> filter.writerPort(0);


	assert( gradient1Node.dataPort(0).isConnected() );

	filter.process();

	result.saveToPng("GradientOutputImage.png");
}



int main()
{
	ScopedBlockMacro("LinearGradientContainer::Test")
	LinearGradientContainerTest();
	return 0;
}
