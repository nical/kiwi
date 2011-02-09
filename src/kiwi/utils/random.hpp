
#pragma once

#ifndef KIWI_UTILS_RANDOM_HPP
#define KIWI_UTILS_RANDOM_HPP

#include <cstdlib>
#include "kiwi/utils/types.hpp"


namespace kiwi{
namespace utils{

namespace random{
/*	kiwi::uint32_t generateUInteger(kiwi::uint32_t max = type<kiwi::uint32_t>::max) {
		return rand() % max;
	}

	kiwi::int32_t generateInteger(kiwi::int32_t max = type<kiwi::int32_t>::max) {
		return rand() % max;
	}
*/
/*	
	kiwi::float_t generateFloat(){
		return (float_t) rand()/(float_t)RAND_MAX;
	}
*/

	char init(int seed = time(0));

	template<class T> T generate(T max = type<T>::max ){
		if( type<T>::isNumber ){
			if( type<T>::isInteger ) {
				return rand() % (int)max;
			}else{
				return static_cast<kiwi::float_t>(rand())
					/ static_cast<kiwi::float_t>(RAND_MAX) * max;
			}
		}
	}
	

	}

namespace{
	static char dummy = kiwi::utils::random::init();
	
}//namespace

	// float f = kiwi::utils::random::generate<float>();

}//namespace
}//namespace




#endif
