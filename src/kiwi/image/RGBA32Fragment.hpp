
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

	bool operator == (RGBA32Fragment f) const{
		return (r == f.r) && (g == f.g) && (b == f.b) && (a == f.a);
	}

	bool operator != (RGBA32Fragment f) const{
		return (r != f.r) || (g != f.g) || (b != f.b) || (a != f.a);
	}

	RGBA32Fragment operator + (RGBA32Fragment f) const{
		return RGBA32Fragment(
			  (r+f.r) < 255 ? (r+f.r) : 255
			, (g+f.g) < 255 ? (g+f.g) : 255
			, (b+f.b) < 255 ? (b+f.b) : 255
			, (a+f.a) < 255 ? (a+f.a) : 255  );
	}
	
	RGBA32Fragment operator - (RGBA32Fragment f) const{
		return RGBA32Fragment(
			  (r > f.r) ? (r-f.r) : 0
			, (g > f.g) ? (g-f.g) : 0
			, (b > f.b) ? (b-f.b) : 0
			, (a > f.a) ? (a-f.a) : 0 );
	}
	
	template<typename T>
	RGBA32Fragment operator / (T val) const{
		return RGBA32Fragment(r/val, g/val, b/val, a/val);
	}
	
	template<typename T>
	RGBA32Fragment operator * (T val) const{
		return RGBA32Fragment(max(r*val), max(g*val), max(b*val), max(a*val));
	}

	RGBA32Fragment operator += (RGBA32Fragment f){
		r = (r+f.r) < 255 ? (r+f.r) : 255;
		g = (g+f.g) < 255 ? (g+f.g) : 255;
		b = (b+f.b) < 255 ? (b+f.b) : 255;
		a = (a+f.a) < 255 ? (a+f.a) : 255;
		return *this;
	}
	
	RGBA32Fragment operator -= (RGBA32Fragment f){
		r = (r > f.r) ? (r-f.r) : 0;
		g = (g > f.g) ? (g-f.g) : 0;
		b = (b > f.b) ? (b-f.b) : 0;
		a = (a > f.a) ? (a-f.a) : 0;
		return *this;
	}

	inline ColorElement max(kiwi::int32_t c){
		return ( c < 255 )? c : 255; 
	}
	inline ColorElement min(kiwi::int32_t c){
		return ( c > 0 )? c : 0;
	}
	
	ColorElement b;
	ColorElement g;
	ColorElement r;
	ColorElement a;
};


}//namespace
}//namespace

#endif
