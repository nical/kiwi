#ifndef KIWI_GENERIC_RANDOMACCESSINTERACE_HPP
#define KIWI_GENERIC_RANDOMACCESSINTERACE_HPP

#include "kiwi/generic/IterableContainerInterface.hpp"

namespace kiwi{
namespace generic{

template<typename TValueType>
class RandomAccessContainerInterface : public IterableContainerInterface<TValueType>
{
public:
  typedef TValueType ValueType;

  // -----
  virtual ValueType getValue( kiwi::uint32_t pos ) const = 0;
  virtual void setValue( kiwi::uint32_t pos, ValueType value ) = 0;
  //TODO: size, resize

};

} //namespace
} //namespace

#endif
