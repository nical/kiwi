
#pragma once
#ifndef KIWI_UTILS_TYPEIDHELPER_HPP
#define KIWI_UTILS_TYPEIDHELPER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/TypeIndex.hpp"

namespace kiwi{
namespace utils{


const string& TypeIdName( kiwi::core::TypeID id );
void RegisterTypeIdName( kiwi::core::TypeID id, const string& name );


}//namespace
}//namespace

#endif
