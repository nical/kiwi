
#include "kiwi/image/CopyImageFilter.hpp"
#include "kiwi/image/cairo/ImageContainer.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Filter.hpp"




using namespace kiwi;
using namespace kiwi::image;

void CopyImageTest()
{
	typedef cairo::RGBAImageContainer::CoordinateVector CoordinateVector; 

	cairo::RGBAImageContainer inputData("inputImageTransp.png");
	kiwi::core::DynamicNode inputDataNode(&inputData);

	assert(inputDataNode.dataPort(0).isComposite());
	assert(inputDataNode.dataPort(0).nbSubPorts() == 4);

	Debug::print() << inputDataNode.dataPort(0).subPort(0).tags().str();

	CopyImageFilter filter;

	Debug::print() << inputDataNode.dataPort(0).subPort(0).isComposite() << endl();

	assert( inputDataNode.dataPort(0).subPort(0).safeDownCastContainer<kiwi::core::Container>() == inputData.subContainer(0) );

	Debug::print() << inputDataNode.dataPort(0).subPort(0).nbSubPorts();
	
	inputDataNode.dataPort(0).subPort(0) >> filter.readerPort(0);
	inputDataNode.dataPort(0).subPort(1) >> filter.readerPort(1);
	inputDataNode.dataPort(0).subPort(2) >> filter.readerPort(2);
	inputDataNode.dataPort(0).subPort(3) >> filter.readerPort(3);

	/*
	inputDataNode.dataPort(0) >> filter.inputPort(0);
	inputDataNode.dataPort(1) >> filter.inputPort(1);
	result.dataPort(0) 		  >> filter.destinationPort(0);
	//
	inputDataNode.dataPort(0) >> filter.readerPort(0);
	inputDataNode.dataPort(1) >> filter.writerPort(1);
	result.dataPort(0) 		  >> filter.destinationPort(0);
	//
	inputDataNode.data(0) >> filter.source(0);
	inputDataNode.data(1) >> filter.source(1);
	result.dataPort(0) 	  >> filter.destination(0);
	*/
	cairo::RGBAImageContainer result(
		CoordinateVector( inputData.width(), inputData.height() ) );
		
	kiwi::core::DynamicNode resultNode(&result);

	resultNode.dataPort(0) >> filter.writerPort(0);

	assert( filter.writerPort(0).isConnected() );

	filter.process();

	result.saveToPng("CopiedOutputImage.png");
}


int main()
{
	ScopedBlockMacro("CopyImageFilter::Test")
	CopyImageTest();
}
