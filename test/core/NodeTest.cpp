#ifndef KIWI_NODE_TEST_HPP
#define KIWI_NODE_TEST_HPP

#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Node.hpp"

#include "kiwi/utils/types.hpp"

#include "kiwi/core/ReaderPort.hpp"
#include "kiwi/core/WriterPort.hpp"
#include "kiwi/core/DataPort.hpp"


using namespace kiwi;



class MyNodeTest : public kiwi::core::Node
{
public:
	
	MyNodeTest() : Node()
	{
	ScopedBlockMacro(scp_block, "MyNodeTest::constructor");
	
	addReaderPort();
	addReaderPort();
	addReaderPort();
	addReaderPort();
		
	addWriterPort();	
	
	addDataPort();
	addDataPort();
		
	
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

	kiwi::Tags readerInputTags(kiwi::portIndex_t i) const
	{
		switch(i)
		{
			case 0 : return kiwi::Tags("#foo");
			case 1 : return kiwi::Tags("#bar");
			case 2 : return kiwi::Tags("#kiwi#bar");
			case 3 : return kiwi::Tags("#open#bar");
			default : return kiwi::Tags("#plop");
		}
	}
	kiwi::Tags readerOutputTags(kiwi::portIndex_t i) const
	{
		switch(i)
		{
			case 0 : return kiwi::Tags("#foo");
			case 1 : return kiwi::Tags("#bar");
			case 2 : return kiwi::Tags("#kiwi#bar");
			case 3 : return kiwi::Tags("#open#bar");
			default : return kiwi::Tags("#plop");
		}
	}
	
	int nodeType() {return 42;}

};






// ---------------------------------------------------------------------
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------


void NodeTest()
{
	Debug::init();
	ScopedBlockMacro(__scop, "Node::Test");
	
	MyNodeTest n;
	
	Debug::print() << n.readerPort(kiwi::string("foo"))->name() << endl();
	Debug::print() << n.readerPort(kiwi::string("bar"))->name() << endl();

	Debug::print() << "Node::Test#1" << endl();
	
	assert(n.readerPort("foo")->index() == 0 );
	assert(n.readerPort("bar")->index() == 1 );
	assert(n.dataPort("plop")->index() == 0 );
	assert(n.readerPort("mouahaha") == 0 );

	MyNodeTest n2;

	Debug::print() << "Node::Test#2" << endl();

	n.dataPort(0) >> n2.readerPort(0);
	assert( n.dataPort(0).isConnected() );
	assert( n2.readerPort(0).isConnected() );

	Debug::print() << "Node::Test#3" << endl();
	
	n2.readerPort(0).disconnect();

	assert( ! n.dataPort(0).isConnected() );
	assert( ! n2.readerPort(0).isConnected() );

	Debug::print() << "Node::Test#4" << endl();

	n.dataPort(0) >> n2.readerPort(0);
	assert( n.dataPort(0).nbConnections() == 1 );

	n.dataPort(0).disconnect();

	assert( ! n.dataPort(0).isConnected() );
	assert( ! n2.readerPort(0).isConnected() );

	Debug::print() << "Node::Test#5" << endl();
	
	// should not connect
	Debug::print()
		<< "the next test will provoque an expected error message"
		<< endl();
	n.dataPort(0) >> n2.readerPort(1);
	Debug::error() << "n.nbConnections = "
		<< n.dataPort(0).nbConnections() << endl();
	assert( ! n.dataPort(0).isConnected() );
	assert( ! n2.readerPort(1).isConnected() );

	Debug::print() << "Node::Test#6" << endl();

	n.dataPort(2) >> n2.readerPort(3);
	assert( n.dataPort(2).isConnected() );
	assert( n2.readerPort(3).isConnected() );
	
}



#ifdef KIWI_TEST_MAIN

int main()
{
	//NodeTest(); specs have changed, so the tes mus be redone
	return 0;
}

#endif


#endif
