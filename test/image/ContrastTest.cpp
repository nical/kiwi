
#ifndef KIWI_GENERIC_CONTRAST_TEST
#define KIWI_GENERIC_CONTRAST_TEST

#include "kiwi/core/Commons.hpp"
#include "kiwi/image/Contrast.hpp"

void ContrastTest()
{
	kiwi::image::Contrast<kiwi::uint8_t, 2> cf;
}



#ifdef KIWI_TEST_MAIN

int main
{
	ContrastTest();
	return 0;
}

#endif


#endif
