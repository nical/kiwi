#include "RawLine.hpp"

namespace kiwi{
namespace text{


kiwi::int8_t RawLine::operator[]( kiwi::int32_t pos ) const
{
	// TODO modulo
	return _data[pos];
}

kiwi::int8_t& RawLine::operator[]( kiwi::int32_t pos )
{
	// TODO modulo
	return _data[pos];
}


uint32_t RawLine::size() const
{
	return _data.size();
}

kiwi::string RawLine::str() const
{
	return _data;
}

void RawLine::operator+=( char const* txt )
{
	_data+= kiwi::string(txt);
}

void RawLine::operator+=( kiwi::string txt )
{
	_data+=txt;
}






}//namespace
}//namespace
