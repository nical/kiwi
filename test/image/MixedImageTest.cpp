
#include "kiwi/image/RGBAImageContainer.hpp"
#include "kiwi/image/cairo/ImageContainer.hpp"
#include "kiwi/image/GaussianBlur.hpp"

using namespace kiwi;
using namespace kiwi::image;

int main()
{
	ScopedBlockMacro(____, "MixedImageTests")
	/*
	typedef cairo::RGBAImageContainer::CoordinateVector CoordinateVector;
	typedef cairo::RGBAImageContainer::ValueType ValueType;
	typedef generic::ArrayContainer<kiwi::uint32_t,2> ChannelBuffer;

	cairo::RGBAImageContainer cairoImg("inputImage.png");
	Debug::print() << "Loaded a png\n";
	
	cairoImg.saveToPng("inputImageCopy.png");

	Debug::print() << "Saved a copy of the png\n";

	ChannelBuffer* R = (ChannelBuffer*)cairoImg.subContainer(0);

	for(kiwi::uint32_t i = 0; i < R->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < R->spanSize(1); ++j){
			R->setValue(CoordinateVector(i,j), 0 );
		}
		
	Debug::print() << "tweaking the image\n";	

	cairoImg.saveToPng("outputImage1.png");
	
	Debug::print() << "Saved outputImage1.png\n";	
	*/

}
