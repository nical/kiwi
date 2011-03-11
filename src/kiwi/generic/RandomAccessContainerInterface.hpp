#ifndef KIWI_GENERIC_RANDOMACCESSINTERACE_HPP
#define KIWI_GENERIC_RANDOMACCESSINTERACE_HPP

#include "kiwi/generic/IterableContainerInterface.hpp"

namespace kiwi{
namespace generic{

/**
 * @brief Interface class for containers that can be random accessed using a
 * single scalar number. 
 */ 
template<typename TValueType>
class RandomAccessContainerInterface : public IterableContainerInterface<TValueType>
{
public:
  typedef TValueType ValueType;

  /**
	 * @brief Returns the number of scalar elements in the container.
   * @todo This method should be moved to a child class
	 */ 
	virtual kiwi::uint32_t size() const { return 0; }

  // -----
  virtual ValueType getValue( kiwi::uint32_t pos ) const = 0;
  virtual void setValue( kiwi::uint32_t pos, ValueType value ) = 0;
  

};

} //namespace
} //namespace

#endif
