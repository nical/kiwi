
#include "kiwi/text/PlainTextAccessor.hpp"


namespace kiwi{
namespace text{

void PlainTextAccessor::init( AbstractTextContainer& container
	, portIndex_t portIndex
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range  )
{
	_container = &container;
	_firstLine = firstLine;
	if( range == 0 ){
		_containerRange = _container->nbLines() - firstLine;
	}else if( range > _container->nbLines() - firstLine ){
		_containerRange = _container->nbLines() - firstLine;
	}else{
		_containerRange = range;
	}
}

kiwi::uint32_t PlainTextAccessor::nbChars() const
{
	kiwi::uint32_t result = 0;
	for(int i = 0; i < _containerRange; ++i){
		result += _container->line(_firstLine + i)->size();
	}
	return result;
}

kiwi::uint32_t PlainTextAccessor::position(kiwi::int32_t lineNb) const
{
	if( lineNb >= (int)_containerRange ) return _containerRange-1;
	else if( lineNb + (int)_containerRange < 0 ) return 0;
	else if( lineNb < 0 ){ return lineNb + (int)_containerRange; }
	else return lineNb;
}
}//namespace
}//namespace
