#pragma once
#ifndef KIWI_CORE_WRITER_HPP
#define KIWI_CORE_WRITER_HPP


namespace kiwi{
namespace core{

/**
 * @class Writer
 * @brief Base class of objects that read and write data from Containers.
 */
class Writer
{
public:
	virtual ~Writer() {}
	virtual uint32_t nbScalarElements() const = 0;
};


}//namespace
}//namespace

#endif
