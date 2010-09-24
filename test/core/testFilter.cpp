
#include "core/Commons.hpp"

#include "core/Filter.hpp"

#include "generic/SimpleValue.hpp"

#include <vector>

using namespace kiwi;
using namespace kiwi::core;

class TestFilter : public Filter
{
public:
	

	TestFilter() : Filter()
	{
		addReaderInputPort("A");
		addReaderInputPort("B");
		
		addWriterInputPort("< Result");
	}
	~TestFilter() {}

	void process()
	{
		typedef generic::ValueReader<float> FloatResource; 
		ScopedBlockMacro(proc_block, "TestFilter::process()");

		debug.print() << "Allocate Reader #0" << endl;
		FloatResource A(dynamic_cast<generic::ValueHolder<float>*>(readerInputPort(0).connectedOutput()->resource()), readerInputPort(0).connectedOutput()->index() );
		
		debug.print() << "Allocate Reader #1" << endl;
		FloatResource B(dynamic_cast<generic::ValueHolder<float>*>(readerInputPort(1).connectedOutput()->resource()), readerInputPort(1).connectedOutput()->index() );
		
		debug.print() << "Allocate Writer #0" << endl;		
		FloatResource result(dynamic_cast<generic::ValueHolder<float>*>(writerInputPort(0).connectedOutput()->resource()), readerInputPort(0).connectedOutput()->index() );

		
		
	}
	
	// Resource implementation -----------------------------------------
	// This Resource has no input port so nothing to be compatible with
	virtual bool isCompatible(portIndex_t, const OutputPort<Reader>&) const 
	{ return true; }
	virtual bool isCompatible(portIndex_t, const OutputPort<Writer>&) const 
	{ return true; }
	
	bool isReady()
	{
		return (readerInputPort(0).isConnected()
			&& readerInputPort(1).isConnected()
			&& writerInputPort(0).isConnected() );
	}
};


int main()
{

ScopedBlockMacro(s2, "kiwi::Test");

debug.beginBlock("int main() ");

	debug.beginBlock("Allocate the resources");
		generic::Value<float> resource1(10);
		generic::Value<float> resource2(10);
		generic::Value<float> resourceResult(10);

		TestFilter myTest;
	debug.endBlock();

	debug.beginBlock("connect the ports");
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);	
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
	debug.endBlock();

	myTest.process();
	
	
	
debug.endBlock();
	return 0;
}


