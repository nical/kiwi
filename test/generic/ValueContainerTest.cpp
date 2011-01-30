#ifndef KIWI_VALUECONTAINER_TEST
#define KIWI_VALUECONTAINER_TEST

#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Filter.hpp"

#include "kiwi/generic/ValueContainer.hpp"
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
void ValueContainerTest()
{
	ScopedBlockMacro(__scop, "ValueContainer::Test<>")

	NodeInitializer init1;
	init1.addContainer( new ValueContainer<T>(10), true, true );
	core::Node* n1 = new core::Node( init1 );

	NodeInitializer init2;
	init2.addContainer( new ValueContainer<T>(5), true, true );
	core::Node* n2 = new core::Node( init2 );	
	
	assert( n1->nbReaderOutputs() == 1 );
	assert( n1->nbWriterOutputs() == 1 );
	assert( n1->nbReaderInputs() == 0 );
	assert( n1->nbWriterInputs() == 0 );

	assert( dynamic_cast<ValueContainer<T>* >(n1->readerOutputPort(0).data())->value() == 10 );
	assert( dynamic_cast<ValueContainer<T>* >(n2->readerOutputPort(0).data())->value() == 5 );

	arithmetic::AddFilter addition;

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

	assert( dynamic_cast<ValueContainer<T>* >(addition.readerOutputPort(0).data())->value() == 15 );

	Debug::print() << "Test passed successfuly!\n";
	
}


#ifdef KIWI_TEST_MAIN

int main()
{
	Debug::init();	
	ScopedBlockMacro(__scop, "ValueContainer::Test")
	//ValueContainerTest<float>();
	//ValueContainerTest<char>();
	ValueContainerTest<int>();
	
	return 0;
}

#endif




#endif
