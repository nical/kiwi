#ifndef KIWI_VALUECONTAINER_TEST
#define KIWI_VALUECONTAINER_TEST

#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Filter.hpp"

#include "kiwi/generic/ValueContainer.hpp"


#include "kiwi/generic/Point.hpp"

#include "kiwi/utils/types.hpp"

#include <vector>


using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::generic;


// ---------------------------------------------------------------------
// --------------------- A simple Filter -------------------------------
// ---------------------------------------------------------------------



// compute the sum of two Value<> resources and place it in an other Value<>
template<typename TValueType>
class ValueTestFilter : public Filter
{
public:
	enum{ A = 0, B = 1};
	enum{ WRITE = 0};
	enum{ RESULT = 0};
	
	typedef kiwi::generic::ValueReader<TValueType> myReader;
	typedef kiwi::generic::ValueWriter<TValueType> myWriter;
// ---------------------------------------------------------------------
	ValueTestFilter() : Filter()
	{
	ScopedBlockMacro(scp_block, "ValueTestFilter::constructor");
		setLayoutEventEnabled(false);
		kiwi::string sType( string("value_")+types::str<TValueType>() );
		addReaderInputPort();
		addReaderInputPort();
		
		addWriterInputPort();	
		
		//add a reader output that will be available only when the writer
		//port is connected
		addReaderOutputPort();
		setPortEnabled(readerOutputPort(0),false);
		setLayoutEventEnabled(true);
	}
	~ValueTestFilter() {}

	

// ---------------------------------------------------------------------
	void process()
	{
	ScopedBlockMacro(proc_block, "ValueTestFilter::process()");

		DEBUG_ONLY(		
			if(!isReady() )
			{
				Debug::error() << "ValueTestFilter::Process error : not ready" 
					<< endl();
				return;
			}
		)//DEBUG_ONLY
		
		Debug::print() << "Allocate Reader #0" << endl();
		myReader A( readerInputPort(0) );
		
		Debug::print() << "Allocate Reader #1" << endl();
		myReader B( readerInputPort(1) );
		
		Debug::print() << "Allocate Writer #0" << endl();
		myWriter result( writerInputPort(0) );
		
		Debug::beginBlock( "compute..");
		
		result.set( A.get() + B.get() );
		
		Debug::endBlock( "compute..");
		
		
		return;
	}
	
	
// ---------------------------------------------------------------------
	bool isReady() const
	{
		return (readerInputPort(0).isConnected()
			&& readerInputPort(1).isConnected()
			&& writerInputPort(0).isConnected() );
	}
	
	void layoutChanged()
	{
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
};






// ---------------------------------------------------------------------
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------

template<typename T>
void ValueContainerTest()
{
ScopedBlockMacro(__scop, "ValueContainerTest")
	Debug::beginBlock("Allocate the resources");
		
		generic::ValueContainer<T> resource1(42);
		
		generic::ValueContainer<T> resource2(12);
		
		generic::ValueContainer<T> resourceResult(0);
		
		ValueTestFilter<T> myTest;
		ValueTestFilter<T> myTest2;
		
	
		
		assert( myTest.indexOf( myTest.readerInputPort(0) ) == 0 );
		assert( resource1.indexOf( resource1.writerOutputPort(0) ) == 0 );

		
	
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

	
}


#ifdef KIWI_TEST_MAIN

int main()
{
	ValueContainerTest<float>();
	ValueContainerTest<char>();
	ValueContainerTest<int>();
	
	return 0;
}

#endif




#endif
