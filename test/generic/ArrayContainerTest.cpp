#ifndef KIWI__ARRAYCONTAINER_TEST
#define KIWI__ARRAYCONTAINER_TEST

#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Filter.hpp"

#include "kiwi/generic/ArrayContainerInterface.hpp"
#include "kiwi/generic/ArrayContainer.hpp"
#include "kiwi/generic/ArrayReader.hpp"
#include "kiwi/generic/ArrayWriter.hpp"
#include "kiwi/generic/ArrayIterator.hpp"


//#include "kiwi/core/Ports.hpp"

#include "kiwi/generic/Point.hpp"

#include "kiwi/utils/types.hpp"

#include <vector>


using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::generic;




// ---------------------------------------------------------------------
// ---------------------------- Test -----------------------------------
// ---------------------------------------------------------------------

template<class ArrayType>
void ArrayContainerTest()
{
	typedef typename ArrayType::CoordinateVector CoordinateVector;
	typedef typename ArrayType::ValueType ValueType;
	
	CoordinateVector size = CoordinateVector::cube(100);
	ArrayType array(size);

	for(int i = 0; i < 1000; ++i){
		CoordinateVector pos = CoordinateVector::random() % size;
		array.setValue(pos, static_cast<ValueType>(i) );
		assert( array.getValue(pos) == static_cast<ValueType>(i) );
	}

	for(int i = 0; i < array.size(); ++i ){
		array.setValue(i, static_cast<ValueType>(i) );
	}
	for(int i = 0; i < array.size(); ++i ){
		assert( array.getValue(i) == static_cast<ValueType>(i) );
	}
}


#ifdef KIWI_TEST_MAIN

int main()
{
	Debug::init(true,true);
	ScopedBlockMacro(_scop, "ArrayContainer::Test")
	
	ArrayContainerTest< ArrayContainer<kiwi::int8_t, 1> >();
	ArrayContainerTest< ArrayContainer<kiwi::int32_t, 2> >();
	ArrayContainerTest< ArrayContainer<double, 3> >();
	
	return 0;
	
}

#endif


#endif
