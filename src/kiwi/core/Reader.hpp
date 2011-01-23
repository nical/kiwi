#ifndef KIWI_CORE_READER_HPP
#define KIWI_CORE_READER_HPP


#include "kiwi/core/Commons.hpp" 

namespace kiwi{
namespace core{
	
/**
 * @class Reader
 * @brief Base class of objects that read data from Containers.
 */ 
class Reader
{
public:
	virtual ~Reader() {}
	virtual uint32_t nbScalarElements() const = 0;
};



}//namespace
}//namespace


#endif
