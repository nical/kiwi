
#include "kiwi/image/cairo/ImageContainer.hpp"

#include "kiwi/generic/ArrayWriter.hpp"
#include "kiwi/generic/ArrayIterator.hpp"


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
	typedef generic::ArrayContainer<kiwi::uint32_t,2> ChannelBuffer;

	RGBAImageContainer img1( CoordinateVector(80,60) );
	Debug::print() << img1.width() << " "<< img1.spanSize()[0] << endl();
	assert( img1.width()*4 == img1.spanSize()[0] );
	assert( img1.width() == 80 );

	assert( img1.height() == img1.spanSize()[1] );
	assert( img1.height() == 60 );

	ChannelBuffer* B = (ChannelBuffer*)img1.subContainer(0);
	ChannelBuffer* G = (ChannelBuffer*)img1.subContainer(1);
	ChannelBuffer* R = (ChannelBuffer*)img1.subContainer(2);
	ChannelBuffer* A = (ChannelBuffer*)img1.subContainer(3);

	for(int i = 0; i < img1.size(); ++i ){
		img1.setValue(i, 0);
	}

	for(kiwi::uint32_t i = 0; i < R->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < R->spanSize(1); ++j){
			R->setValue(CoordinateVector(i,j), 0 );
		}

	for(kiwi::uint32_t i = 0; i < G->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < G->spanSize(1); ++j){
			G->setValue(CoordinateVector(i,j), 0 );
		}


	for(kiwi::uint32_t i = 0; i < B->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < B->spanSize(1); ++j){
			B->setValue(CoordinateVector(i,j), i );
		}

	for(kiwi::uint32_t i = 0; i < A->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < A->spanSize(1); ++j){
			A->setValue(CoordinateVector(i,j), i );
		}

	for(int i = 0; i < img1.size(); ++i ){
		Debug::print() << (int)img1.getValue(i);
	}

	img1.saveToPng("imgTest1.png");
/*
	typedef kiwi::generic::Point<kiwi::uint32_t,2> Point2u;
	typedef kiwi::generic::ArrayWriter<kiwi::uint8_t, 2> myWriter;
	
	
	kiwi::image::cairo::RGBAImageContainer img1( Point2u(80,60) );
	assert( img1.width() == img1.spanSize()[0] );
	assert( img1.width() == 80 );

	assert( img1.height() == img1.spanSize()[1] );
	assert( img1.height() == 60 );
	
	Debug::print() << "increment(0): " << img1.increments(0)[0]; 
	
	kiwi::image::cairo::RGBAImageContainer img2( Point2u(80,60) );
	
	
	myWriter img1Writer0( img1, 0 );
	generic::ArrayIterator<kiwi::uint8_t> it = img1Writer0.getIterator();
	do { *it = 0; } while ( it.onIteration() );
	
	myWriter img1Writer1( img1, 1 );
	it = img1Writer1.getIterator();
	do { *it = 100; } while ( it.onIteration() );
	
	myWriter img1Writer2( img1, 2 );
	it = img1Writer2.getSpanIterator(Point2u::zero(), 1 );
	kiwi::uint8_t val = 0;
	for(generic::Point<kiwi::uint32_t, 2> pos(0,0); pos(1) < 60; pos(1)+=2 )
	{
		//Debug::print() << "y = " << pos(1) << endl();
		generic::ArrayIterator<kiwi::uint8_t> itLine 
			= img1Writer2.getSpanIterator( pos, 0 );
		// for each line ...	
		do 
		{ 
			//*itLine = val; count++; 
			*itLine = 200; 
		} while ( itLine.onIteration() );
	}
	
		myWriter img1Writer3( img1, 3 );
	it = img1Writer3.getIterator();
	do { *it = 255; } while ( it.onIteration() );
	
	// ------ 2 nested span iterators
	Debug::endl(5);
	
	val = 0;
	myWriter img2Writer0( img2, 0 );
	it = img2Writer0.getIterator();
	do { *it = 0; } while ( it.onIteration() );
	
	myWriter img2Writer1( img2, 1 );
	it = img2Writer1.getSpanIterator( 
		generic::Point<kiwi::uint32_t, 2>::zero(), 0 );
	do { 
		generic::ArrayIterator<kiwi::uint8_t> itLine 
			= img2Writer1.getSpanIterator( it, 1 );
		// for each line ...	
		do {*itLine = val*255/80; } while ( itLine.onIteration() );
		
		val++;
	} while ( it.onIteration() );
	
	generic::Point<kiwi::uint32_t,2> pos = generic::Point<kiwi::uint32_t,2>::zero();
	
	val = 0;
	myWriter img2Writer2( img2, 2 );
	it = img2Writer2.getSpanIterator( 
		generic::Point<kiwi::uint32_t, 2>::zero(), 1 );
	do { 
		Debug::beginBlock("spanIterator >");
		int count = 0;
		generic::ArrayIterator<kiwi::uint8_t> itLine 
			= img2Writer2.getSpanIterator( it, 0 );
		// for each line ...	
		do 
		{ 
			*itLine = val*255/60; 
			count++; 
		} while ( itLine.onIteration() );
		val++;
		Debug::print() << "count: " << count << " val: " << (int)val << endl();
		Debug::endBlock();
		pos(1) += 1;
	} while ( it.onIteration() );

	
	myWriter img2Writer3( img2, 3 );
	it = img2Writer3.getIterator();
	int count = 0;
	do { *it = 255;
		//Point<kiwi::uint32_t,2> p = img2Writer3.positionOf(it);
		count++;
	 } while ( it.onIteration() );
	assert(count == 80*60);
	Debug::error() << count << endl();
		
	img1.saveToPng("testCairoContainer1.png");
	img2.saveToPng("testCairoContainer2.png");

	
	
	
*/
	
	return 0;
}



#ifdef KIWI_TEST_MAIN

int main()
{
	CairoImageContainerTest();
	return 0;
}

#endif

