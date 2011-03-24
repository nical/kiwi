
#pragma once
#ifndef KIWI_CORE_SAMETYPECONNECTIONPOLICY_HPP
#define KIWI_CORE_SAMETYPECONNECTIONPOLICY_HPP

namespace kiwi{
namespace core{

/**
 * Port connection policy that accepts only connection of the exact same type. 
 *
 */ 
template<typename ContainerType>
struct SameTypeConnectionPolicy{
  bool isCompatible( const ReaderPort& self, const DataPort& port ) const {
    return false; // TODO !
  }
};



}//namespace
}//namespace


#endif
