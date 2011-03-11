
#include "kiwi/text/PlainTextAccessor.hpp"


namespace kiwi{
namespace text{

void PlainTextAccessor::init( TextContainerInterface& container
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range  )
{
	_container = &container;
	_firstLine = firstLine;
	if( range == 0 ){
		_nbLines = _container->nbLines() - firstLine;
	}else if( range > _container->nbLines() - firstLine ){
		_nbLines = _container->nbLines() - firstLine;
	}else{
		_nbLines = range;
	}
}

kiwi::uint32_t PlainTextAccessor::nbChars() const
{
	kiwi::uint32_t result = 0;
	for(int i = 0; i < _nbLines; ++i){
		result += _container->line(_firstLine + i).size();
	}
	return result;
}

kiwi::uint32_t PlainTextAccessor::position(kiwi::int32_t lineNb) const
{
	//ScopedBlockMacro(__scop, "PlainTextAccessor::position")
	//Debug::print() << "lineNb = " << lineNb << " nbLines = "
	//	<< _nbLines <<  endl(); 
	if( lineNb >= (int)_nbLines ){
		if(_nbLines > 0 ) return _nbLines-1;
		else return 0;
	}
	else if( lineNb + (int)_nbLines < 0 ) return 0;
	else if( lineNb < 0 ){ return lineNb + (int)_nbLines; }
	else return lineNb;
}

kiwi::uint32_t PlainTextAccessor::positionInsert(kiwi::int32_t lineNb) const
{
	//ScopedBlockMacro(__scop, "PlainTextAccessor::positionInsert")
	//Debug::print() << "lineNb = " << lineNb << " nbLines = "
	//	<< _nbLines <<  endl(); 
	if( lineNb > (int)_nbLines ){
		if(_nbLines > 0 ) return _nbLines;
		else return 0;
	}
	else if( lineNb + (int)_nbLines < 0 ) return 0;
	else if( lineNb < 0 ){ return lineNb + (int)_nbLines+1; }
	else return lineNb;
}

}//namespace
}//namespace
