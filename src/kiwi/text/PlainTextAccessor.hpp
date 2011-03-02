#ifndef KIWI_TEXT_RAWTEXTACCESSOR_HPP
#define KIWI_TEXT_RAWTEXTACCESSOR_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/text/TextContainerInterface.hpp"


namespace kiwi{
namespace text{


class PlainTextAccessor
{
public:
	
	kiwi::uint32_t nbLines() const { return _nbLines; }
	kiwi::uint32_t nbChars() const;

	char_t getChar(int32_t charNumber) const;

protected:

	kiwi::uint32_t position(kiwi::int32_t lineNb) const;	
	kiwi::uint32_t positionInsert(kiwi::int32_t lineNb) const;	

	TextContainerInterface* _container;
	kiwi::uint32_t _firstLine;
	kiwi::uint32_t _nbLines; // the number of lines 

	void init( TextContainerInterface& container
			, kiwi::uint32_t firstLine
			, kiwi::uint32_t range );

};


}//namespace
}//namespace


#endif
