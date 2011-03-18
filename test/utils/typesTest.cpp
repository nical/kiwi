

#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/types.hpp"
#include <assert.h>


using namespace kiwi;

template<typename T>
kiwi::string testCall(){
	return kiwi::string( types::str<T>() );
}

template<typename T> 
kiwi::string typesTest(){
	switch( types::id<T>() ){
		TypeSwitchMacro( return testCall<KIWI_SWITCH_TYPE>() );
	};
}

int main()
{
	Debug::init(true, true);	
	ScopedBlockMacro( "types::Test")

	assert(typesTest<char>() == kiwi::string("int8"));
	assert(typesTest<unsigned char>()  == kiwi::string("uint8"));
	assert(typesTest<float>()  == kiwi::string("float"));
	assert(typesTest<unsigned int>()  == kiwi::string("uint32"));
	


}
