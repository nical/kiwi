
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
  static bool isCompatible( const ReaderPort& self, const DataPort& port ) {
    return true;
  }
  static bool isCompatible( const WriterPort& self, const DataPort& port ) {
    return true;
  }
};



}//namespace
}//namespace


#endif
