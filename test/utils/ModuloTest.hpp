#ifndef KIWI_MODULO_TEST_HPP
#define KIWI_MODULO_TEST_HPP





#include "kiwi/utils/modulo.hpp"

void ModulotTest()
{
	assert(kiwi::utils::modulo(0,10) == 0 );
	assert(kiwi::utils::modulo(10,10) == 0 );
	assert(kiwi::utils::modulo(11,10) == 1 );
	assert(kiwi::utils::modulo(-1,10) == 9 );
	
}





#endif
