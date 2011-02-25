
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
	kiwi::core::Node inputDataNode(&inputData);

	assert(inputDataNode.readerOutputPort(0).isComposite());
	assert(inputDataNode.readerOutputPort(0).nbSubPorts() == 4);

	Debug::print() << inputDataNode.readerOutputPort(0).subPort(0).tags().str();

	CopyImageFilter filter;

	Debug::print() << inputDataNode.readerOutputPort(0).subPort(0).isComposite() << endl();

	assert( inputDataNode.readerOutputPort(0).subPort(0).getContainer<kiwi::core::Container>() == inputData.subContainer(0) );

	Debug::print() << inputDataNode.readerOutputPort(0).subPort(0).nbSubPorts();
	
	inputDataNode.readerOutputPort(0).subPort(0) >> filter.readerInputPort(0);
	inputDataNode.readerOutputPort(0).subPort(1) >> filter.readerInputPort(1);
	inputDataNode.readerOutputPort(0).subPort(2) >> filter.readerInputPort(2);
	inputDataNode.readerOutputPort(0).subPort(3) >> filter.readerInputPort(3);

	cairo::RGBAImageContainer result(
		CoordinateVector( inputData.width(), inputData.height() ) );
		
	kiwi::core::Node resultNode(&result);

	resultNode.writerOutputPort(0) >> filter.writerInputPort(0);

	assert( filter.writerInputPort(0).isConnected() );

	filter.process();

	result.saveToPng("CopiedOutputImage.png");
}


int main()
{
	ScopedBlockMacro(scop, "CopyImageFilter::Test")
	CopyImageTest();
}
