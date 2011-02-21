
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
/*
	assert(cairo_image_surface_get_format( inputData.getSurface() )
		== CAIRO_FORMAT_ARGB32);
*/
	assert(inputDataNode.readerOutputPort(0).isComposite());
	assert(inputDataNode.readerOutputPort(0).nbSubPorts() == 4);

	Debug::print() << "\n\nloutriplop\n" << endl();
	
	Debug::print() << inputDataNode.readerOutputPort(0).subPort(0).tags().str();

	Debug::print() << "\nloutriplop\n\n" << endl();
	

	CopyImageFilter filter;

	Debug::print() << inputDataNode.readerOutputPort(0).subPort(0).isComposite() << endl();

	assert( inputDataNode.readerOutputPort(0).subPort(0).getContainer<kiwi::core::Container>() == inputData.subContainer(0) );

	Debug::print() << inputDataNode.readerOutputPort(0).subPort(0).nbSubPorts();

	Debug::print() << "plop\n" << endl();
	
	inputDataNode.readerOutputPort(0).subPort(0) >> filter.readerInputPort(0);
	inputDataNode.readerOutputPort(0).subPort(1) >> filter.readerInputPort(1);
	inputDataNode.readerOutputPort(0).subPort(2) >> filter.readerInputPort(2);
	inputDataNode.readerOutputPort(0).subPort(3) >> filter.readerInputPort(3);

	//inputData.subContainer(0)->readerInputPort(0);
	

	cairo::RGBAImageContainer result(
		CoordinateVector( inputData.width(), inputData.height() ) );
		
	kiwi::core::Node resultNode(&result);

	resultNode.writerOutputPort(0) >> filter.writerInputPort(0);

	filter.process();

	result.saveToPng("CopiedOutputImage.png");
}


int main()
{
	ScopedBlockMacro(scop, "CopyImageFilter::Test")
	CopyImageTest();
}
