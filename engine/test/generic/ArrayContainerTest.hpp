#pragma once

#ifndef KIWI_ARRAYCONTAINER_TEST
#define KIWI_ARRAYCONTAINER_TEST

#include "core/Commons.hpp"

#include "core/Filter.hpp"

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
class AddArraysFilter : public Filter
{
public:
	enum{ A = 0, B = 1};
	enum{ WRITE = 0};
	enum{ RESULT = 0};
	
	typedef generic::ArrayReader<TValueType, TDimension> myReader;
	typedef generic::ArrayWriter<TValueType, TDimension> myWriter;
// ---------------------------------------------------------------------
	AddArraysFilter() : Filter()
	{
	ScopedBlockMacro(scp_block, "AddArraysFilter::constructor");
		setLayoutEventEnabled(false);
		kiwi::string sType( kiwi::string("array")
			+ boost::lexical_cast<kiwi::string>(TDimension)
			+"d_"+ types::str<TValueType>() );
		addReaderInputPort(sType);
		addReaderInputPort(sType);
		
		addWriterInputPort(sType);	
		
		//add a reader output that will be available only when the writer
		//port is connected
		addReaderOutputPort(sType);
		setReaderOutputPortEnabled(0,false);
		setLayoutEventEnabled(true);
	}
	~AddArraysFilter() {}

	

// ---------------------------------------------------------------------
	void process()
	{
	ScopedBlockMacro(proc_block, "AddArraysFilter::process()");

DEBUG_ONLY(		if(!isReady() )
		{
			debug.error() << "AddArraysFilter::Process error : not ready" 
				<< endl();
			return;
		}
)
		debug.print() << "Allocate Reader #0" << endl;
		myReader A( readerInputPort(0) );
		
		debug.print() << "Allocate Reader #1" << endl;
		myReader B( readerInputPort(1) );
		
		debug.print() << "Allocate Writer #0" << endl;
		myWriter result( writerInputPort(0) );
		
		debug.beginBlock( "compute..");
			ArrayConstIterator<TValueType> itA = A.getIterator();
			ArrayConstIterator<TValueType> itB = B.getIterator();
			ArrayIterator<TValueType> itResult = result.getIterator();
			
			Point<int, TDimension> pos(0);
			result.set( pos , A.get( pos ) + B.get( pos ) );
			unsigned count = 0;
			debug.print() << "avant la boucle" << endl();
			do
			{
				if( itA.isDone() ) break;
				if( itB.isDone() ) break;
				
				++count;
				//debug.print() << " on iteration " << count << endl();
				
				*itResult = *itA + *itB;
				// this is unsafe crap: you don't iterate through image 
				// that might not have the same size that way but right
				// now i'm testing iterators so... 
				++itA ;
				++itB ;
			} while(itResult.onIteration() );
			
			debug.print() << count << " iterations " << endl();

		debug.endBlock( "compute..");
		
		debug.print() << "end of the method" << endl();
		return;
	}
	
	
// ---------------------------------------------------------------------
	bool readyCondition()
	{
		return (readerInputPort(0).isConnected()
			&& readerInputPort(1).isConnected()
			&& writerInputPort(0).isConnected() );
	}
	
	void layoutChanged()
	{
	ScopedBlockMacro(__scop, "TestFiler::layoutChanged")
		if(writerInputPort(0).isConnected() )
		{
			if( !readerOutputPort(0).isEnabled() )
			{
				setReaderOutputPortEnabled(0,true);
				ReaderOutputPort& op
				= writerInputPort(0).connectedOutput()->node()->readerOutputPort(0);
				bindPort( readerOutputPort(0), op );
			}
		}
		else
		{
			readerOutputPort(0).disconnect();
			setReaderOutputPortEnabled(0,false);	
		}

	}
};






// ---------------------------------------------------------------------
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------

template<typename T, unsigned Dim, unsigned Comp>
void ArrayContainerTest()
{

	debug.beginBlock("Allocate the resources");
		//audio::AudioBuffer<float> audioTest( 128, 1 );
		
		bool interleave = false;
		
		generic::Point<unsigned,Dim> size;
		for(unsigned i = 0; i < Dim; ++i) size[i] = 10;
		
		debug.print() << "resource1" << endl();
		// here the container allocates its data
		generic::ArrayContainer<T,Dim> resource1(size, Comp, interleave);
		
		debug.print() << "resource2" << endl();
		// here the container uses some preallocated memory 
		unsigned allocSize = Comp; for(unsigned i = 0; i < Dim; ++i) 
			allocSize*=10;
		T* preAllocData = new T[allocSize];
		generic::ArrayContainer<T,Dim> resource2(preAllocData, size, Comp, interleave);
		// remember to delete the allocated memory !
		
		debug.print() << "resourceResult" << endl();
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
		
	debug.endBlock();

	debug.endl();

	debug.beginBlock("connect the ports");
		resource1.readerOutputPort(1) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
		
		resource1.readerOutputPort(0) >> myTest2.readerInputPort(0);
		myTest.readerOutputPort(0) >> myTest2.readerInputPort(1);
		resourceResult.writerOutputPort(1) >> myTest2.writerInputPort(0);
	debug.endBlock("connect the ports");

	debug.print() << endl();

	myTest.process();
	myTest2.process();

	debug.print() << "processed" << endl();

	//resourceResult.printState();
	delete[] preAllocData;
}

/*
int main()
{

ScopedBlockMacro(s2, "kiwi::TestArrayContainer");

debug.beginBlock("int main() ");

	ArrayTest<int, 2, 2>();

	DEBUG_ONLY( debug.print() << "woooooat !" << endl; )
	
debug.endBlock();
	return 0;
}
*/

#endif
