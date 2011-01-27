
#include "kiwi/utils/UnorderedArray.hpp"
#include <assert.h>

using namespace kiwi::utils;

int main()
{
ScopedBlockMacro(__scop, "UnorderedArray::Test" )	
	UnorderedArray<int> a;

	assert( a.size() == 0 );
	a.add(42);
	assert( a.size() == 1 );
	assert( a[0] == 42 );
	assert( a.has(42) );
	
	a.add(12);
	assert( a.size() == 2 );
	assert( a[0]+a[1] == 12+42  );
	assert( a.has(42) );
	assert( a.has(12) );

	a.add(5);
	assert( a.size() == 3 );
	assert( a[0]+a[1]+a[2] == 12+42+5 );
	assert( a.has(42) );
	assert( a.has(12) );
	assert( a.has(5) );

	assert( a.remove( 12 ) );
	assert( a.size() == 2 );
	assert( a[0]+a[1] == 42+5 );
	assert( !a.has( 12 ) );
	assert( a.has(42) );
	assert( a.has(5) );

}
