
#include "kiwi/image/RGBAImageContainer.hpp"

using namespace kiwi;
using namespace kiwi::image;


int ImageContainerTest()
{
ScopedBlockMacro(__scp, "kiwi::ImageContainer Test" );

	typedef RGBAImageContainer<>::CoordinateVector CoordinateVector;
	typedef RGBAImageContainer<>::ColorChannel ColorChannel;
	typedef RGBAImageContainer<>::ValueType Pixel;

	unsigned WIDTH = 12;
	unsigned HEIGHT = 8;

	RGBAImageContainer<> img1( WIDTH, HEIGHT );
	Debug::print() << img1.width() << " "<< img1.spanSize()[0] << endl();
	assert( img1.width() == img1.spanSize()[0] );
	assert( img1.width() == WIDTH );

	assert( img1.height() == img1.spanSize()[1] );
	assert( img1.height() == HEIGHT );

	ColorChannel* B = (ColorChannel*)img1.subContainer(0);
	ColorChannel* G = (ColorChannel*)img1.subContainer(1);
	ColorChannel* R = (ColorChannel*)img1.subContainer(2);
	ColorChannel* A = (ColorChannel*)img1.subContainer(3);

	assert(R);
	assert(G);
	assert(B);
	assert(A);

	assert( img1.size() == img1.width() * img1.height() );

	for(int i = 0; i < img1.size(); ++i ){
		img1.setValue(i, Pixel(0,0,0,255) );
	}

	int count = 0;
	for(kiwi::uint32_t i = 0; i < R->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < R->spanSize(1); ++j){
			R->setValue(CoordinateVector(i,j), 42 );
		}

	for(kiwi::uint32_t i = 0; i < G->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < G->spanSize(1); ++j){
			G->setValue(CoordinateVector(i,j), 222 );
		}


	for(kiwi::uint32_t i = 0; i < B->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < B->spanSize(1); ++j){
			B->setValue(CoordinateVector(i,j), 111 );
		}

	for(kiwi::uint32_t i = 0; i < A->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < A->spanSize(1); ++j){
			A->setValue(CoordinateVector(i,j), 255 );
		}

	Pixel expected(42,222,111,255);
	for(kiwi::uint32_t i = 0; i < img1.width(); ++i)
		for(kiwi::uint32_t j = 0; j < img1.height(); ++j){
			Debug::print() << img1.getValue( CoordinateVector(i,j) ).toStr();
			Pixel pix = img1.getValue( CoordinateVector(i,j) );
			assert(pix.r == expected.r);
			assert(pix.g == expected.g);
			assert(pix.b == expected.b);
			assert(pix.a == expected.a);
	}

	
	return 0;
}



int main()
{
	ImageContainerTest();
	return 0;
}


