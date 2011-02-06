#ifndef KIWI__ARRAYCONTAINER_TEST
#define KIWI__ARRAYCONTAINER_TEST

#include "kiwi/core/Commons.hpp"

#include "kiwi/core/Filter.hpp"

#include "kiwi/generic/ArrayContainerInterface.hpp"
#include "kiwi/generic/ArrayContainer.hpp"
#include "kiwi/generic/ArrayReader.hpp"
#include "kiwi/generic/ArrayWriter.hpp"
#include "kiwi/generic/ArrayIterator.hpp"


#include "kiwi/core/Ports.hpp"

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
	typename ArrayType::CoordinateVector size = ArrayType::CoordinateVector::cube(100);
	ArrayType array(size);
}


#ifdef KIWI_TEST_MAIN

int main()
{
	ArrayContainerTest< ArrayContainer<int, 2> >();

	
	return 0;
	
}

#endif


#endif
