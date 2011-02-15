
#pragma once

#ifndef KIWI_IMAGE_RGBA32FRAGMENT_HPP
#define KIWI_IMAGE_RGBA32FRAGMENT_HPP

#include "kiwi/core/Commons.hpp"
#include "boost/lexical_cast.hpp"

namespace kiwi{
namespace image{

	
class RGBA32Fragment
{
public:
	typedef kiwi::uint8_t ColorElement;

	RGBA32Fragment(){}
	RGBA32Fragment(ColorElement R, ColorElement G, ColorElement B, ColorElement A)
	: r(R), g(G), b(B), a(A) {}

	kiwi::string toStr() const {
		return kiwi::string("rgba(")
			+ boost::lexical_cast<kiwi::string>((int)r) + ","
			+ boost::lexical_cast<kiwi::string>((int)g) + ","
			+ boost::lexical_cast<kiwi::string>((int)b) + ","
			+ boost::lexical_cast<kiwi::string>((int)a) + ")";
	}
	
	ColorElement b;
	ColorElement g;
	ColorElement r;
	ColorElement a;
};


}//namespace
}//namespace

#endif
