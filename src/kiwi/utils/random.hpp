#ifndef KIWI_UTILS_RANDOM_HPP
#define KIWI_UTILS_RANDOM_HPP

#include <cstdlib>
#include "kiwi/utils/types.hpp"


namespace kiwi{
namespace utils{

namespace random{
	kiwi::uint32_t generateUInteger(kiwi::uint32_t max = type<kiwi::uint32_t>::max) {
		return rand() % max;
	}

	kiwi::int32_t generateInteger(kiwi::int32_t max = type<kiwi::int32_t>::max) {
		return rand() % max;
	}

	
	kiwi::float_t generateFloat(){
		return (float_t) rand()/(float_t)RAND_MAX;
	}


	char init(int seed = time(0))
	{
		srand(seed);
		return 0;
	}

	template<class T> T generate(){
		if( type<T>::isNumber ){
			if( type<T>::isInteger ) {
				return rand() % type<T>::max;
			}else{
				return (kiwi::float_t)rand()/(kiwi::float_t)RAND_MAX;
			}
		}
/*		else{
			return T::random();
		} */
	}
	

	}

namespace{
	static char dummy = kiwi::utils::random::init();
	
}//namespace

	// PointVector P = kiwi::utils::random::generate<PointVector>();
	// float f = kiwi::utils::random::generate<float>();

}//namespace
}//namespace




#endif
