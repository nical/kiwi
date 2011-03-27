#ifndef KIWI_NUMBERCONTAINER_TEST
#define KIWI_NUMBERCONTAINER_TEST

#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Filter.hpp"
#include "kiwi/core/DynamicNode.hpp"

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
	ScopedBlockMacro("NumberContainer::Test<>")

	// allocate two container nodes with one container each
	Node* n1 = new DynamicNode( new NumberContainer<T>(10) );
	Node* n2 = new DynamicNode( new NumberContainer<T>(5) );

	Debug::print() << "assert: number of ports in the container\n";
		// check that the number of ports is correct
		assert( n1->nbDataPorts() == 1 );
		assert( n1->nbReaderPorts() == 0 );
		assert( n1->nbWriterPorts() == 0 );

	Debug::print() << "check the within the containers\n";
		assert( n1->dataPort(0).safeDownCastContainer<NumberContainerInterface<T> >()->getValue() == 10 );
		assert( n2->dataPort(0).safeDownCastContainer<NumberContainerInterface<T> >()->getValue() == 5 );
	
	// create a filter
	arithmetic::AddFilter addition;

	Debug::print() << "assert: number of ports in the filter\n";
		assert( addition.nbReaderPorts() == 2 );	
		assert( n1->nbDataPorts() == 1 );
		assert( n2->nbDataPorts() == 1 );


	Debug::print() << "connections\n";
	assert( n1->dataPort(0) >> addition.readerPort(0) );
	n2->dataPort(0) >> addition.readerPort(1);

		
		assert( addition.nbReaderPorts() == 2 );
		assert( n1->nbDataPorts() == 1 );
		assert( n2->nbDataPorts() == 1 );

		assert( n1->dataPort(0).isConnected() );
		assert( n2->dataPort(0).isConnected() );
		assert( addition.readerPort(0).isConnected() );
		assert( addition.readerPort(1).isConnected() );

	Debug::print() << "filter will process...\n";

	addition.process();

	Debug::print() << "after filter processing\n";
    Debug::print() << addition.dataPort(0).safeDownCastContainer<NumberContainerInterface<T> >()->getValue() << endl();
		assert( addition.dataPort(0).safeDownCastContainer<NumberContainerInterface<T> >()->getValue() == 15 );

	Debug::print() << "Test passed successfuly!\n";

}


#ifdef KIWI_TEST_MAIN

int main()
{
	Debug::init();
	ScopedBlockMacro("NumberContainer::Test")
	//NumberContainerTest<char>();
	NumberContainerTest<float>(); // Right now only works with floats

	return 0;
}



#endif


#endif
