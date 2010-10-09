
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
		
		assert(this->getWriterInputCount() == 0 );
		
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
			debug.error() << "TestFilter::Process error : not ready" << endl();
			return;
		}

		debug.print() << "Allocate Reader #0" << endl;
		FloatReader A( readerInputPort(0) );
		
		debug.print() << "Allocate Reader #1" << endl;
		FloatReader B( readerInputPort(1) );
		
		debug.print() << "Allocate Writer #0" << endl;
		FloatWriter result( writerInputPort(0) );
		
		debug.beginBlock( "compute..");
			result.set( A.get() + B.get() );
			debug.print() << "result :" << result.get() << endl();
		debug.endBlock( "compute..");
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




int main()
{

ScopedBlockMacro(s2, "kiwi::Test");

debug.beginBlock("int main() ");

	debug.beginBlock("Allocate the resources");
		generic::Value<float> resource1(10);
		generic::Value<float> resource2(10);
		generic::Value<float> resourceResult(42);

		TestFilter<float> myTest;
		TestFilter<float> myTest2;
	debug.endBlock();

	debug.print() << endl();

	debug.beginBlock("Test: this should not work");
		myTest.readerOutputPort(0) >> myTest2.readerInputPort(0);		
		assert( !myTest.readerOutputPort(0).isConnected() );
		assert( !myTest2.readerInputPort(0).isConnected() );
	debug.endBlock("Test: it didn't work right ?");
	
	debug.endl();

	debug.beginBlock("connect the ports");
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);	
			assert( resource1.readerOutputPort(0).isConnected() );
			assert( myTest.readerInputPort(0).isConnected() );
		
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
			assert( resource2.readerOutputPort(0).isConnected() );
			assert( myTest.readerInputPort(1).isConnected() );

		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
			assert( resourceResult.writerOutputPort(0).isConnected() );
			assert( myTest.writerInputPort(0).isConnected() );

	debug.endBlock("connect the ports");
	
	debug.endl();
	
	debug.beginBlock("Test: now this should work");
		if(! myTest.isLayoutEventEnabled() )
			debug.error() << "error : layoutEvent not enabled" << endl();
		assert(myTest.isLayoutEventEnabled());
		
		if(myTest.readerOutputPort(0).resource() 
			== myTest.readerOutputPort(0).metaResource() )
			debug.error() << "error : binding badly done" << endl();
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

	debug.endBlock("Test: did it work ?");

	debug.endl();
	
	assert(myTest.isReady() );
	myTest.process();
	assert(myTest2.isReady() );
	myTest2.process();
	
	
debug.endBlock();
	return 0;
}


