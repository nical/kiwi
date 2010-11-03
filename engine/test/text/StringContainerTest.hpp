#include "TestSuite.hpp"

#include "core/Commons.hpp"

#include "core/Filter.hpp"

#include "generic/Point.hpp"

#include "utils/types.hpp"

#include "text/StringContainer.hpp"

#include <vector>


using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::generic;


// ---------------------------------------------------------------------
// --------------------- A simple Filter -------------------------------
// ---------------------------------------------------------------------



// compute the sum of two Value<> resources and place it in an other Value<>
template<typename TValueType, unsigned int TDimension>
class TestStringFilter : public Filter
{
public:
	enum{ A = 0, B = 1 };
	enum{ WRITE = 0 };
	enum{ RESULT = 0 };
	
	typedef generic::ArrayReader<TValueType, TDimension> myReader;
	typedef generic::ArrayWriter<TValueType, TDimension> myWriter;
// ---------------------------------------------------------------------
	TestStringFilter() : Filter()
	{
	ScopedBlockMacro(scp_block, "TestStringFilter::constructor");
		setLayoutEventEnabled(false);
		kiwi::string sType( "string" );
		addReaderInputPort(sType, "A");
		addReaderInputPort(sType, "B");
		
		addWriterInputPort(sType, "Write Result");	
		
		//add a reader output that will be available only when the writer
		//port is connected
		addReaderOutputPort(sType, "Result");
		setReaderOutputPortEnabled(0,false);
		setLayoutEventEnabled(true);
	}
	~TestStringFilter() {}

	

// ---------------------------------------------------------------------
	void process()
	{
	//ScopedBlockMacro(proc_block, "TestStringFilter::process()");
		
		if(!isReady() )
		{
			debug.error() << "TestStringFilter::Process error : not ready" 
				<< endl();
			return;
		}

		debug.print() << "Allocate Reader #0" << endl;
		myReader A( readerInputPort(0) );
		
		debug.print() << "Allocate Reader #1" << endl;
		myReader B( readerInputPort(1) );
		
		debug.print() << "Allocate Writer #0" << endl;
		myWriter result( writerInputPort(0) );
		
		debug.beginBlock( "compute..");
		
		
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
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------

bool StringTest()
{

	debug.beginBlock("Allocate the resources");
		//audio::AudioBuffer<float> audioTest( 128, 1 );
		
		debug.print() << "resource1" << endl();
		
		text::StringContainer resource1("foo");
		
		debug.print() << "resource2" << endl();
		text::StringContainer resource2();
		// remember to delete the allocated memory !
		
		debug.print() << "resourceResult" << endl();
		text::StringContainer resourceResult();
		
		TestStringFilter myTest;
		
			
		resource1.printState();
		resource2.printState();
		
	debug.endBlock();

	debug.endl();

	debug.beginBlock("connect the ports");
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
	debug.endBlock("connect the ports");

	debug.print() << endl();

	myTest.process();

	debug.print() << "processed" << endl();

	resourceResult.printState();
		delete[] preAllocData;
	return true;
}

// ---------------------------------------------------------------------
// ---------------------------- Main -----------------------------------
// ---------------------------------------------------------------------


int main()
{

ScopedBlockMacro(s2, "kiwi::StringContainerTest");

debug.beginBlock("int main() ");

	StringTest();

debug.endBlock();
	return 0;
}



