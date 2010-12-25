#pragma once

#ifndef KIWI_TEXT_RAWLINE_HPP
#define KIWI_TEXT_RAWLINE_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/text/Line.hpp"

namespace kiwi{
namespace text{


class RawLine : public Line
{
public:
	RawLine( const kiwi::string& str ){}
	kiwi::int8_t operator[]( kiwi::int32_t pos ) const;
	kiwi::int8_t& operator[]( kiwi::int32_t pos );
	uint32_t size() const;
	kiwi::string str() const;
	void operator+=( char const* txt );
	void operator+=( kiwi::string txt );

protected:
	kiwi::string _data;
};



}//namespace
}//namespace

#endif
