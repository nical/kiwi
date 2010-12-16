#ifndef KIWI_NODE_TEST_HPP
#define KIWI_NODE_TEST_HPP

#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Node.hpp"

#include "kiwi/utils/types.hpp"



using namespace kiwi;



class MyNodeTest : public kiwi::core::Node
{
public:
	
	MyNodeTest() : Node()
	{
	ScopedBlockMacro(scp_block, "MyNodeTest::constructor");
	
	addReaderInputPort();
	addReaderInputPort();
		
	addWriterInputPort();	
	
	addWriterOutputPort();
		
	addReaderOutputPort();

	}
	~MyNodeTest() {}
	
	kiwi::string readerInputName(kiwi::portIndex_t i) const
	{
		switch(i)
		{
			case 0: return kiwi::string("foo");
			case 1: return kiwi::string("bar");
			default: return kiwi::string("");
		}
	}
	kiwi::string readerOutputName(kiwi::portIndex_t i) const
	{
		return kiwi::string("plop");
	}
	kiwi::string WriterInputName(kiwi::portIndex_t i) const
	{
		return kiwi::string("haha");
	}
	kiwi::string WriterOutputName(kiwi::portIndex_t i) const
	{
		return kiwi::string("orly?");
	}
	
	int nodeType() {return 42;}

};






// ---------------------------------------------------------------------
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------


void NodeTest()
{
	MyNodeTest n;
	
	Debug::print() << n.readerInputPort(kiwi::string("foo"))->name() << endl();
	Debug::print() << n.readerInputPort(kiwi::string("bar"))->name() << endl();
	
	assert(n.readerInputPort("foo")->index() == 0 );
	assert(n.readerInputPort("bar")->index() == 1 );
	assert(n.readerOutputPort("plop")->index() == 0 );
	assert(n.readerInputPort("mouahaha") == 0 );
}



#ifdef KIWI_TEST_MAIN

int main()
{
	NodeTest();
	return 0;
}

#endif


#endif
