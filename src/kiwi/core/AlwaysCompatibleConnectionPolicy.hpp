
#pragma once
#ifndef KIWI_CORE_ALWAYSCOMPATIBLECONNECTIONPOLICY_HPP
#define KIWI_CORE_ALWAYSCOMPATIBLECONNECTIONPOLICY_HPP

namespace kiwi{
namespace core{

/**
 * Port connection policy that accepts every connection. 
 *
 */ 
struct AlwaysCompatibleConnectionPolicy{
  bool isCompatible( const ReaderPort& self, const DataPort& port ) const {
    return true;
  }
};



}//namespace
}//namespace


#endif
