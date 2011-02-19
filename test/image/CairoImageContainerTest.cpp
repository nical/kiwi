
#include "kiwi/image/cairo/ImageContainer.hpp"
#include "kiwi/generic/ArrayContainer.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Filter.hpp"

using namespace kiwi;
using namespace kiwi::image;
using namespace kiwi::image::cairo;

int CairoImageContainerTest()
{
ScopedBlockMacro(__scp, "kiwi::cairo::ImageContainer Test" );
	//typedef kiwi::generic::Point<kiwi::uint32_t,2> Point2u;
	typedef RGBAImageContainer::CoordinateVector CoordinateVector;
	typedef generic::ArrayContainer<kiwi::uint8_t,2> ChannelBuffer;

	RGBAImageContainer img1( CoordinateVector(80,60) );
	Debug::print() << img1.width() << " "<< img1.spanSize()[0] << endl();
	assert( img1.width() == img1.spanSize()[0] );
	assert( img1.width() == 80 );

	assert( img1.height() == img1.spanSize()[1] );
	assert( img1.height() == 60 );

	Debug::print() << "plop\n";

	ChannelBuffer* B = (ChannelBuffer*)img1.subContainer(0);
	ChannelBuffer* G = (ChannelBuffer*)img1.subContainer(1);
	ChannelBuffer* R = (ChannelBuffer*)img1.subContainer(2);
	ChannelBuffer* A = (ChannelBuffer*)img1.subContainer(3);

	Debug::print() << "plop\n";

	for(int i = 0; i < img1.size(); ++i ){
		img1.setValue(i, RGBA32Fragment(0,0,0,255) );
	}

	Debug::print() << "plop\n";

	for(kiwi::uint32_t i = 0; i < R->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < R->spanSize(1); ++j){
			R->setValue(CoordinateVector(i,j), 2*j );
			assert(R->getValue(CoordinateVector(i,j)) == 2*j );
		}

	for(kiwi::uint32_t i = 0; i < G->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < G->spanSize(1); ++j){
			G->setValue(CoordinateVector(i,j), 0 );
			assert(G->getValue(CoordinateVector(i,j)) == 0 );
		}


	for(kiwi::uint32_t i = 0; i < B->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < B->spanSize(1); ++j){
			B->setValue(CoordinateVector(i,j), 2*i );
			assert(B->getValue(CoordinateVector(i,j)) == 2*i );
		}

	for(kiwi::uint32_t i = 0; i < A->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < A->spanSize(1); ++j){
			A->setValue(CoordinateVector(i,j), 255 );
			assert(A->getValue(CoordinateVector(i,j)) == 255 );
		}

	for(int i = 0; i < img1.size(); ++i ){
		Debug::print() << img1.getValue(i).toStr();
	}

	img1.saveToPng("imgTest1.png");

	
	return 0;
}



#ifdef KIWI_TEST_MAIN

int main()
{
	CairoImageContainerTest();
	return 0;
}

#endif

