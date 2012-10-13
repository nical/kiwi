
#ifndef KIWI_CORE_PTRID_HPP
#define KIWI_CORE_PTRID_HPP

#include "stdint.h"

namespace kiwi {
namespace _ {

template<typename T>
struct PtrID 
{
public:
    typedef PtrID<T> Self;

    PtrID(const Self& rhs) : _ptr(rhs._ptr) {}
    bool operator==(const Self& rhs) { return _ptr == rhs._ptr; }
    PtrID(T* ptr) : _ptr(ptr) {}
protected:
    T* _ptr;
};

template<typename T>
struct IntID 
{
public:
    typedef IntID<T> Self;

    bool isValid() const { return _int >= 0; } 

    IntID() : _int(-1) {}
    IntID(const Self& rhs) : _int(rhs._int) {}
    bool operator==(const Self& rhs) { return _int == rhs._int; }
    IntID(int32_t i) : _int(i) {}

    int32_t _int;
};

} // namespace
} // namespace

#endif