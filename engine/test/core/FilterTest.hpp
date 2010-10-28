
#include "core/Commons.hpp"

#include "core/Filter.hpp"

#include "generic/SimpleValue.hpp"

#include "utils/types.hpp"


#include <assert.h>

using namespace kiwi;
using namespace kiwi::core;

typedef kiwi::generic::ValueReader<float> FloatReader; 
typedef kiwi::generic::ValueWriter<float> FloatWriter;


// ---------------------------------------------------------------------
// --------------------- A simple Filter -------------------------------
// ---------------------------------------------------------------------



// compute the sum of two Value<> resources and place it in an other Value<>
template<typename TValueType>
class TestFilter : public Filter
{
public:
	enum{ A = 0, B = 1};
	enum{ WRITE = 0};
	enum{ RESULT = 0};
// ---------------------------------------------------------------------
	TestFilter() : Filter()
	{
	ScopedBlockMacro(scp_block, "TestFilter::constructor");
		setLayoutEventEnabled(false);
		
		kiwi::string sType( kiwi::string("value_")+ types::str<TValueType>() );
		
		assert(this->getReaderInputCount() == 0 );
		assert(this->getWriterInputCount() == 0 );
		
		addReaderInputPort(sType, "A");
		
		assert(this->getReaderInputCount() == 1 );
		
		addReaderInputPort(sType, "B");
		
		assert(this->getReaderInputCount() == 2 );
		
		addWriterInputPort(sType, "Write Result");
		
		Debug::print() << "writer input count: " 
		<< this->getWriterInputCount() << endl();
		
		assert(this->getWriterInputCount() == 1 );
		
		//add a reader output that will be available only when the writer
		//port is connected
		addReaderOutputPort(sType, "Result");
		setReaderOutputPortEnabled(0,false);
		setLayoutEventEnabled(true);
	}
	~TestFilter() {}

	

// ---------------------------------------------------------------------------------------
	void process()
	{
		ScopedBlockMacro(proc_block, "TestFilter::process()");
		if(!isReady() )
		{
			Debug::error() << "TestFilter::Process error : not ready" << endl();
			return;
		}

		Debug::print() << "Allocate Reader #0" << endl;
		FloatReader A( readerInputPort(0) );
		
		Debug::print() << "Allocate Reader #1" << endl;
		FloatReader B( readerInputPort(1) );
		
		Debug::print() << "Allocate Writer #0" << endl;
		FloatWriter result( writerInputPort(0) );
		
		Debug::beginBlock( "compute..");
			result.set( A.get() + B.get() );
			Debug::print() << "result :" << result.get() << endl();
		Debug::endBlock( "compute..");
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
				= writerInputPort(0).connectedOutput()->resource()->readerOutputPort(0);
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
// ---------------------------- Main -----------------------------------
// ---------------------------------------------------------------------

template<typename T> void FilterTest()
{
ScopedBlockMacro(__scop, "Filter Test");	
	Debug::beginBlock("Allocate the resources");
		generic::Value<T> resource1(10);
		generic::Value<T> resource2(10);
		generic::Value<T> resourceResult(42);

		TestFilter<T> myTest;
		TestFilter<T> myTest2;
	Debug::endBlock();

	Debug::print() << endl();

	Debug::beginBlock("Test: this should not work");
		myTest.readerOutputPort(0) >> myTest2.readerInputPort(0);		
		assert( !myTest.readerOutputPort(0).isConnected() );
		assert( !myTest2.readerInputPort(0).isConnected() );
	Debug::endBlock("Test: it didn't work right ?");
	
	Debug::endl();

	Debug::beginBlock("connect the ports");
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);	
			assert( resource1.readerOutputPort(0).isConnected() );
			assert( myTest.readerInputPort(0).isConnected() );
		
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
			assert( resource2.readerOutputPort(0).isConnected() );
			assert( myTest.readerInputPort(1).isConnected() );

		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
			assert( resourceResult.writerOutputPort(0).isConnected() );
			assert( myTest.writerInputPort(0).isConnected() );

	Debug::endBlock("connect the ports");
	
	Debug::endl();
	
	Debug::beginBlock("Test: now this should work");
		if(! myTest.isLayoutEventEnabled() )
			Debug::error() << "error : layoutEvent not enabled" << endl();
		assert(myTest.isLayoutEventEnabled());
		
		if(myTest.readerOutputPort(0).resource() 
			== myTest.readerOutputPort(0).metaResource() )
			Debug::error() << "error : binding badly done" << endl();
		assert( myTest.readerOutputPort(0).resource() != myTest.readerOutputPort(0).metaResource() );	
			
		myTest.readerOutputPort(0) >> myTest2.readerInputPort(0);
			assert( myTest.readerOutputPort(0).isConnected() );
			assert( myTest2.readerInputPort(0).isConnected() );

		resource1.readerOutputPort(0) >> myTest2.readerInputPort(1);
			assert( resource1.readerOutputPort(0).isConnected() );
			assert( myTest2.readerInputPort(1).isConnected() );

		resourceResult.writerOutputPort(0) >> myTest2.writerInputPort(0);
			assert( resourceResult.writerOutputPort(0).isConnected() );
			assert( myTest.writerInputPort(0).isConnected() );

	Debug::endBlock("Test: did it work ?");

	Debug::endl();
	
	assert(myTest.isReady() );
	myTest.process();
	assert(myTest2.isReady() );
	myTest2.process();
	
	
}

/*
int main()
{

ScopedBlockMacro(s2, "kiwi::FilterTest");
	FilterTest<float>();
	FilterTest<int>();

	return 0;
}

*/
