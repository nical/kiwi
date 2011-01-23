#ifndef KIWI_MULTIARRAYCONTAINER_TEST
#define KIWI_MULTIARRAYCONTAINER_TEST

#include "kiwi/core/Commons.hpp"


#include "kiwi/generic/MultiArrayContainer.hpp"
#include "kiwi/generic/ArrayReader.hpp"
#include "kiwi/generic/ArrayWriter.hpp"
#include "kiwi/generic/ArrayIterator.hpp"

#include "kiwi/generic/Point.hpp"
#include "kiwi/core.hpp"

#include "kiwi/utils/types.hpp"

#include <vector>


using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::generic;





// compute the sum of two Value<> resources and place it in an other Value<>
template<typename TValueType, unsigned int TDimension>
class AddArraysFilter : public kiwi::core::CanonicalFilter
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
	bool isReady() const
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
void MultiArrayContainerTest()
{
	typedef generic::ArrayReader<T, Dim> myReader;
	typedef generic::ArrayWriter<T, Dim> myWriter;

	Debug::beginBlock("Allocate the resources");
		
		generic::Point<unsigned,Dim> size;
		for(unsigned i = 0; i < Dim; ++i) size[i] = 10;
		
		Debug::print() << "resource1" << endl();
		// here the container allocates its data
		generic::MultiArrayContainer<T,Dim> resource1(size, Comp);
		
		Debug::print() << "resource2" << endl();
		// here the container uses some preallocated memory 
		unsigned allocSize = 1; for(unsigned i = 0; i < Dim; ++i) 
			allocSize*=10;
		T** preAllocData = new T*[Comp];
		for(unsigned i = 0; i< Comp; ++i)
			preAllocData[i] = new T[allocSize];
		
		generic::MultiArrayContainer<T,Dim> resource2(preAllocData, size, Comp);
		// remember to delete the allocated memory !
		
		Debug::print() << "resourceResult" << endl();
		generic::MultiArrayContainer<T,Dim> resourceResult(size, Comp);
		
		AddArraysFilter<T,Dim> myTest;
		AddArraysFilter<T,Dim> myTest2;
		
		T count = 0;
		
		myWriter rd10( resource1, 0 );
		ArrayIterator<T> it = rd10.getIterator();
		do { *it = ++count; } while ( it.onIteration() );
		
		myWriter rd11( resource1, 1 );
		it = rd11.getIterator();
		do { *it = ++count; } while ( it.onIteration() );
		
		myWriter rd20( resource2, 0 );
		it = rd20.getIterator();
		do { *it = 100; } while ( it.onIteration() );
		
		myWriter rd21( resource1, 1 );
		it = rd21.getIterator();
		do { *it = 500; } while ( it.onIteration() );
		
		myWriter wr10( resource2, 0 );
		it = rd11.getIterator();
		do { *it = 0; } while ( it.onIteration() );
		
		myWriter wr11( resource1, 1 );
		it = wr10.getIterator();
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
		resource1.readerOutputPort(1) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
		
		resource1.readerOutputPort(0) >> myTest2.readerInputPort(0);
		myTest.readerOutputPort(0) >> myTest2.readerInputPort(1);
		resourceResult.writerOutputPort(1) >> myTest2.writerInputPort(0);
	Debug::endBlock("connect the ports");

	Debug::print() << endl();

	myTest.process();
	myTest2.process();

	Debug::print() << "processed" << endl();

	for(unsigned i = 0; i< Comp; ++i)
			delete[] preAllocData[i];
	delete[] preAllocData;
}


#ifdef KIWI_TEST_MAIN

int main()
{
	MultiArrayContainerTest<double, 3, 4>();
	return 0;
}

#endif




#endif
