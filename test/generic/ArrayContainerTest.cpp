
#include "core/Commons.hpp"

#include "core/Filter.hpp"

#include "generic/ArrayContainer.hpp"
#include "generic/ArrayReader.hpp"
#include "generic/ArrayWriter.hpp"

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
		addReaderInputPort(sType, "A");
		addReaderInputPort(sType, "B");
		
		addWriterInputPort(sType, "Write Result");	
		
		//add a reader output that will be available only when the writer
		//port is connected
		addReaderOutputPort(sType, "Result");
		setReaderOutputPortEnabled(0,false);
		setLayoutEventEnabled(true);
	}
	~AddArraysFilter() {}

	

// ---------------------------------------------------------------------
	void process()
	{
		ScopedBlockMacro(proc_block, "AddArraysFilter::process()");
		if(!isReady() )
		{
			debug.error() << "AddArraysFilter::Process error : not ready" 
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
			Point<int, TDimension> pos(0);
			result.set( pos , A.get( pos ) + B.get( pos ) );
			//debug.print() << "result :" << result.get() << endl();
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
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------

template<typename T, unsigned Dim, unsigned Comp>
bool ArrayTest()
{

	debug.beginBlock("Allocate the resources");
		generic::Point<unsigned,Dim> size;
		for(unsigned i = 0; i < Dim; ++i) size[i] = 255;
	
		generic::ArrayContainer<T,Dim> resource1(size, Comp, 1);
		generic::ArrayContainer<T,Dim> resource2(size, Comp, 2);
		generic::ArrayContainer<T,Dim> resourceResult(size, Comp, 3);
		
		AddArraysFilter<T,Dim> myTest;
	debug.endBlock();

	debug.endl();

	debug.beginBlock("connect the ports");
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
	debug.endBlock("connect the ports");

	debug.print() << endl();

	myTest.process();

	return true;
}

// ---------------------------------------------------------------------
// ---------------------------- Main -----------------------------------
// ---------------------------------------------------------------------




int main()
{

ScopedBlockMacro(s2, "kiwi::TestArrayContainer");

debug.beginBlock("int main() ");

	ArrayTest<int, 2, 1>();

	
debug.endBlock();
	return 0;
}


