#pragma once

#ifndef KIWI_METAFILTER_TEST
#define KIWI_METAFILTER_TEST


#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Filter.hpp"

#include "generic/ArrayContainerTest.hpp"

#include "kiwi/utils/types.hpp"

#include <vector>


using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::generic;


// ---------------------------------------------------------------------
// --------------------- A simple Filter -------------------------------
// ---------------------------------------------------------------------



// compute the sum of two Value<> resources and place it in an other Value<>
template<typename TValueType, unsigned int TDimension>
class MetaAddArraysFilter : public Filter
{
public:
	
	typedef generic::ArrayReader<TValueType, TDimension> myReader;
	typedef generic::ArrayWriter<TValueType, TDimension> myWriter;
// ---------------------------------------------------------------------
	MetaAddArraysFilter() : Filter()
	{
//	ScopedBlockMacro(scp_block, "MetaAddArraysFilter::constructor");
		setLayoutEventEnabled(false);
		kiwi::string sType( kiwi::string("array")
			+ boost::lexical_cast<kiwi::string>(TDimension)
			+"d_"+ types::str<TValueType>() );
		addReaderInputPort();
		addReaderInputPort();
		
		addWriterInputPort();	
		
		//add a reader output that will be available only when the writer
		//port is connected
		addReaderOutputPort();
		setPortEnabled(readerOutputPort(0),false);
		
		bindPort(readerInputPort(0), _subFilter.readerInputPort(0) );
		bindPort(readerInputPort(1), _subFilter.readerInputPort(1) );
		bindPort(writerInputPort(0),_subFilter.writerInputPort(0) );
		bindPort(readerOutputPort(0), _subFilter.readerOutputPort(0) );
		
		
		setLayoutEventEnabled(true);
	}
	~MetaAddArraysFilter() {}

	

// ---------------------------------------------------------------------
	void process()
	{
	ScopedBlockMacro(proc_block, "MetaAddArraysFilter::process()");

		DEBUG_ONLY(		
			if( !isReady() )
			{
				Debug::error() << "MetaAddArraysFilter::Process error : not ready" 
					<< endl();
				return;
			}
		)//DEBUG_ONLY
			
		_subFilter.process();
			
		return;
	}
	
	
// ---------------------------------------------------------------------
	bool readyCondition()
	{
		return _subFilter.isReady();
	}
	
	void layoutChanged()
	{
	//ScopedBlockMacro(__scop, "TestFiler::layoutChanged")
		if(writerInputPort(0).isConnected() )
		{
			if( !readerOutputPort(0).isEnabled() )
			{
				setPortEnabled(readerOutputPort(0),true);
				ReaderOutputPort& op
				= writerInputPort(0).connectedOutput()->node()->readerOutputPort(0);
				bindPort( readerOutputPort(0), op );
			}
		}
		else
		{
			readerOutputPort(0).disconnect();
			setPortEnabled(readerOutputPort(0),false);	
		}

	}
	
protected:
	AddArraysFilter<TValueType,TDimension> _subFilter;
};






// ---------------------------------------------------------------------
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------

template<typename T, unsigned Dim, unsigned Comp>
void MetaFilterTest()
{
// Here we run the same test that ArrayContainerTest but using a 
// "meta-filter" that encapsulates AddArraysFilter to test the 
// functionning of port bindings


 	Debug::beginBlock("Allocate the resources");
		
		bool interleave = false;
		
		generic::Point<unsigned,Dim> size;
		for(unsigned i = 0; i < Dim; ++i) size[i] = 10;
		
		Debug::print() << "resource1" << endl();
		// here the container allocates its data
		generic::ArrayContainer<T,Dim> resource1(size, Comp, interleave);
		
		Debug::print() << "resource2" << endl();
		// here the container uses some preallocated memory 
		unsigned allocSize = Comp; for(unsigned i = 0; i < Dim; ++i) allocSize*=10;
		T* preAllocData = new T[allocSize];
		generic::ArrayContainer<T,Dim> resource2(preAllocData, size, Comp, interleave);
		// remember to delete the allocated memory !
		
		Debug::print() << "resourceResult" << endl();
		generic::ArrayContainer<T,Dim> resourceResult(size, Comp, interleave);
		
		MetaAddArraysFilter<T,Dim> myTest;
		MetaAddArraysFilter<T,Dim> myTest2;
		
		T count = 0;
		ArrayIterator<T> it = resource1.getBasicIterator();
		do { *it = ++count; } while ( it.onIteration() );
		
		it = resource2.getBasicIterator();
		do { *it = 100; } while ( it.onIteration() );
		
		it = resourceResult.getBasicIterator();
		do { *it = 0; } while ( it.onIteration() );
		
		//resource1.printState();
		//resource2.printState();
		
	Debug::endBlock();

	Debug::endl();

	Debug::beginBlock("connect the ports");
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
		
		resource1.readerOutputPort(0) >> myTest2.readerInputPort(0);
		myTest.readerOutputPort(0) >> myTest2.readerInputPort(1);
		resourceResult.writerOutputPort(0) >> myTest2.writerInputPort(0);
	Debug::endBlock("connect the ports");

	Debug::print() << endl();

	myTest.process();
	myTest2.process();

	Debug::print() << "processed" << endl();

	resourceResult.printState();
	delete[] preAllocData;
}


#endif
