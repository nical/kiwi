#pragma once

#ifndef KIWI_ARRAYCONTAINER_TEST
#define KIWI_ARRAYCONTAINER_TEST

#include "core/Commons.hpp"

#include "core/CanonicalFilter.hpp"

#include "generic/ArrayContainer.hpp"
#include "generic/ArrayReader.hpp"
#include "generic/ArrayWriter.hpp"
#include "generic/ArrayIterator.hpp"

#include "generic/Point.hpp"

#include "utils/types.hpp"

#include <vector>


using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::generic;


// ---------------------------------------------------------------------
// --------------------- A simple Filter -------------------------------
// ---------------------------------------------------------------------



// compute the sum of two Value<> resources and place it in an other Value<>
template<typename TValueType, unsigned int TDimension>
class AddArraysFilter : public CanonicalFilter
{
public:
	enum{ A = 0, B = 1};
	enum{ WRITE = 0};
	enum{ RESULT = 0};
	
	typedef generic::ArrayReader<TValueType, TDimension> myReader;
	typedef generic::ArrayWriter<TValueType, TDimension> myWriter;
// ---------------------------------------------------------------------
	AddArraysFilter() : CanonicalFilter(1)
	{
	ScopedBlockMacro(scp_block, "AddArraysFilter::constructor");
		setLayoutEventEnabled(false);
		kiwi::string sType( kiwi::string("array")
			+ boost::lexical_cast<kiwi::string>(TDimension)
			+"d_"+ types::str<TValueType>() );
		addReaderInputPort();
		addReaderInputPort();
		
//+		addWriterInputPort();	
		
		//add a reader output that will be available only when the writer
		//port is connected
//+		addReaderOutputPort();
//+		setPortEnabled(readerOutputPort(0),false);
		setLayoutEventEnabled(true);
	}
	~AddArraysFilter() {}

	

// ---------------------------------------------------------------------
	void process()
	{
	ScopedBlockMacro(proc_block, "AddArraysFilter::process()");

DEBUG_ONLY(		if(!isReady() )
		{
			Debug::error() << "AddArraysFilter::Process error : not ready" 
				<< endl();
			return;
		}
)
		Debug::print() << "Allocate Reader #0" << endl();
		myReader A( readerInputPort(0) );
		
		Debug::print() << "Allocate Reader #1" << endl();
		myReader B( readerInputPort(1) );
		
		Debug::print() << "Allocate Writer #0" << endl();
		myWriter result( writerInputPort(0) );
		
		Debug::beginBlock( "compute..");
			ArrayConstIterator<TValueType> itA = A.getIterator();
			ArrayConstIterator<TValueType> itB = B.getIterator();
			ArrayIterator<TValueType> itResult = result.getIterator();
			
			Point<int, TDimension> pos(0);
			result.set( pos , A.get( pos ) + B.get( pos ) );
			unsigned count = 0;
			do
			{
				if( itA.isDone() ) break;
				if( itB.isDone() ) break;
				
				++count;
				//Debug::print() << " on iteration " << count << endl();
				
				*itResult = *itA + *itB;
				// this is unsafe crap: you don't iterate through image 
				// that might not have the same size that way but right
				// now i'm interested on testing iterators
				++itA ;
				++itB ;
			} while(itResult.onIteration() );
			
			Debug::print() << count << " iterations " << endl();

		Debug::endBlock( "compute..");
		
		Debug::print() << "end of the method" << endl();
		return;
	}
	
	
// ---------------------------------------------------------------------
	bool readyCondition()
	{
		return (readerInputPort(0).isConnected()
			&& readerInputPort(1).isConnected()
			&& writerInputPort(0).isConnected() );
	}
	
};






// ---------------------------------------------------------------------
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------

template<typename T, unsigned Dim, unsigned Comp>
void ArrayContainerTest()
{

	Debug::beginBlock("Allocate the resources");
		//audio::AudioBuffer<float> audioTest( 128, 1 );
		
		bool interleave = false;
		
		generic::Point<unsigned,Dim> size;
		for(unsigned i = 0; i < Dim; ++i) size[i] = 10;
		
		Debug::print() << "resource1" << endl();
		// here the container allocates its data
		generic::ArrayContainer<T,Dim> resource1(size, Comp, interleave);
		
		Debug::print() << "resource2" << endl();
		// here the container uses some preallocated memory 
		unsigned allocSize = Comp; for(unsigned i = 0; i < Dim; ++i) 
			allocSize*=10;
		T* preAllocData = new T[allocSize];
		generic::ArrayContainer<T,Dim> resource2(preAllocData, size, Comp, interleave);
		// remember to delete the allocated memory !
		
		Debug::print() << "resourceResult" << endl();
		generic::ArrayContainer<T,Dim> resourceResult(size, Comp, interleave);
		
		AddArraysFilter<T,Dim> myTest;
		AddArraysFilter<T,Dim> myTest2;
		
		T count = 0;
		ArrayIterator<T> it = resource1.getBasicIterator();
		do { *it = ++count; } while ( it.onIteration() );
		
		it = resource2.getBasicIterator();
		do { *it = 100; } while ( it.onIteration() );
		
		it = resourceResult.getBasicIterator();
		do { *it = 0; } while ( it.onIteration() );
		
		assert( myTest.indexOf( myTest.readerInputPort(0) ) == 0 );
		assert( myTest.indexOf( myTest.readerInputPort(1) ) == 1 );
		assert( resource1.indexOf( resource1.writerOutputPort(0) ) == 0 );
		assert( resource1.indexOf( resource1.writerOutputPort(1) ) == 1 );
		
		//resource1.printState();
		//resource2.printState();
		
	Debug::endBlock();

	Debug::endl();

	Debug::beginBlock("connect the ports");
		// tests that Canonical Form is working
		assert( !myTest.readerOutputPort(0).isEnabled() );
		resource1.readerOutputPort(1) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
		
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
		// now the reader output port should be enabled
		assert( myTest.readerOutputPort(0).isEnabled() );

		resource1.readerOutputPort(0) >> myTest2.readerInputPort(0);
		myTest.readerOutputPort(0) >> myTest2.readerInputPort(1);
		resourceResult.writerOutputPort(1) >> myTest2.writerInputPort(0);
	Debug::endBlock("connect the ports");

	Debug::print() << endl();

	myTest.process();
	myTest2.process();

	Debug::print() << "processed" << endl();

	//resourceResult.printState();
	delete[] preAllocData;
}


#endif
