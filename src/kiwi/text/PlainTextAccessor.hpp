#ifndef KIWI_TEXT_RAWTEXTACCESSOR_HPP
#define KIWI_TEXT_RAWTEXTACCESSOR_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/text/AbstractTextContainer.hpp"


namespace kiwi{
namespace text{


class PlainTextAccessor
{
public:
	
	kiwi::uint32_t nbLines() const { return _containerRange; }
	kiwi::uint32_t nbChars() const;

	char_t getChar(int32_t charNumber) const;

protected:

	kiwi::uint32_t position(kiwi::int32_t lineNb) const;	

	AbstractTextContainer* _container;
	kiwi::uint32_t _firstLine;
	kiwi::uint32_t _containerRange; // the number of lines 

	void init( AbstractTextContainer& container
			, portIndex_t index
			, kiwi::uint32_t firstLine
			, kiwi::uint32_t range );

};


}//namespace
}//namespace


#endif
