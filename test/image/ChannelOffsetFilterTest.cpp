
#include "kiwi/image/ChannelOffsetFilter.hpp"
#include "kiwi/image/cairo/ImageContainer.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/generic/RectangleContainer.hpp"
#include <assert.h>



using namespace kiwi;
using namespace kiwi::image;

void ChannelOffsetTest()
{
	typedef cairo::RGBAImageContainer::CoordinateVector CoordinateVector; 

	cairo::RGBAImageContainer inputData("inputImageTransp.png");
	kiwi::core::Node inputDataNode(&inputData);

	kiwi::generic::PointVectorContainer<kiwi::uint32_t, 2> displacement1(CoordinateVector(10,10));
	kiwi::core::Node displacement1Node(&displacement1);

	kiwi::generic::RectangleContainer<kiwi::int32_t,2> region(
		CoordinateVector(0,100),CoordinateVector(600,400) );
	kiwi::core::Node regionNode(&region);
		
	cairo::RGBAImageContainer result("inputImageTransp.png" );	
	kiwi::core::Node resultNode(&result);

	kiwi::image::ChannelOffsetFilter f1;


	assert( inputDataNode.dataPort(0).isComposite() );
	assert( inputDataNode.dataPort(0).nbSubPorts() == 4 );
	
	inputDataNode.dataPort(0).subPort(0) 	>> f1.readerPort(0);
	displacement1Node.dataPort(0) 			>> f1.readerPort(1);
	regionNode.dataPort(0) 			>> f1.readerPort(2);
	resultNode.dataPort(0).subPort(0)		>> f1.writerPort(0);

	//typedef kiwi::core::Container TestType;
	typedef kiwi::generic::PointAccessContainerInterface<kiwi::uint8_t,2> TestType;
	TestType* ptr =	resultNode.dataPort(0).subPort(0).getContainer<TestType>() ;
	assert( ptr );

	assert( f1.readerPort(0).isConnected() );
	assert( f1.readerPort(1).isConnected() );
	assert( f1.writerPort(0).isConnected() );

	f1.process();

	result.saveToPng("OffsetFilterOutputImage.png");
}


int main()
{
	ScopedBlockMacro(scop, "ChannelOffsetFilter::Test")
	ChannelOffsetTest();
}
