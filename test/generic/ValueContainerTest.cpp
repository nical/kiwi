#ifndef KIWI_NUMBERCONTAINER_TEST
#define KIWI_NUMBERCONTAINER_TEST

#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Filter.hpp"

#include "kiwi/generic/NumberContainer.hpp"
#include "kiwi/arithmetic/AddFilter.hpp"

#include "kiwi/generic/Point.hpp"

#include "kiwi/utils/types.hpp"

#include <vector>


using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::generic;



// ---------------------------------------------------------------------
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------

template<typename T>
void NumberContainerTest()
{
	ScopedBlockMacro(__scop, "NumberContainer::Test<>")

	// allocate two container nodes with one container each
	Node* n1 = new Node( new NumberContainer<T>(10) );
	Node* n2 = new Node( new NumberContainer<T>(5) );

	Debug::print() << "assert: number of ports in the container\n";
		// check that the number of ports is correct
		assert( n1->nbReaderOutputs() == 1 );
		assert( n1->nbWriterOutputs() == 1 );
		assert( n1->nbReaderInputs() == 0 );
		assert( n1->nbWriterInputs() == 0 );

	Debug::print() << "check the within the containers\n";
		assert( n1->readerOutputPort(0).getContainer<NumberContainerInterface<T> >()->getValue() == 10 );
		assert( n2->readerOutputPort(0).getContainer<NumberContainerInterface<T> >()->getValue() == 5 );
	
	// create a filter
	arithmetic::AddFilter addition;

	Debug::print() << "assert: number of ports in the filter\n";
		assert( addition.nbReaderInputs() == 2 );	
		assert( n1->nbReaderOutputs() == 1 );
		assert( n2->nbReaderOutputs() == 1 );


	Debug::print() << "connections\n";
	n1->readerOutputPort(0) >> addition.readerInputPort(0);
	n2->readerOutputPort(0) >> addition.readerInputPort(1);

		
		assert( addition.nbReaderInputs() == 2 );
		assert( n1->nbReaderOutputs() == 1 );
		assert( n2->nbReaderOutputs() == 1 );

		assert( n1->readerOutputPort(0).isConnected() );
		assert( n2->readerOutputPort(0).isConnected() );
		assert( addition.readerInputPort(0).isConnected() );
		assert( addition.readerInputPort(1).isConnected() );

	Debug::print() << "filter will process...\n";

	addition.process();

	Debug::print() << "after filter processing\n";

		assert( addition.readerOutputPort(0).getContainer<NumberContainerInterface<T> >()->getValue() == 15 );

	Debug::print() << "Test passed successfuly!\n";

}


#ifdef KIWI_TEST_MAIN

int main()
{
	Debug::init();
	ScopedBlockMacro(__scop, "NumberContainer::Test")
	//NumberContainerTest<char>();
	NumberContainerTest<float>(); // Right now only works with floats

	return 0;
}



#endif


#endif
