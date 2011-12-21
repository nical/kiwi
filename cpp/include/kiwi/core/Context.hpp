
#pragma once
#ifndef KIWI_CORE_CONTEXT_HPP
#define KIWI_CORE_CONTEXT_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{

class Blob;

class Context
{
public:
    typedef uint32 DataIndex;

    static Context * Default();

    Blob data( DataIndex idx );
};


} //namespace

} //namespace

#endif
