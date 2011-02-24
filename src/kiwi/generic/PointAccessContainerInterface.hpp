#ifndef KIWI_GENERIC_POINTACCESSINTERACE_HPP
#define KIWI_GENERIC_POINTACCESSINTERACE_HPP

#include "kiwi/generic/RandomAccessContainerInterface.hpp"
#include "kiwi/generic/Point.hpp"

namespace kiwi{
namespace generic{

template<typename TValueType, unsigned int TDimension, typename AccessType = kiwi::uint32_t>
class PointAccessContainerInterface : public RandomAccessContainerInterface<TValueType>
{
public:
  typedef TValueType ValueType;
  typedef kiwi::generic::Point<AccessType, TDimension> CoordinateVector;
  static const unsigned int Dimension = TDimension;
  // -----
  virtual ValueType getValue( const CoordinateVector& point ) const = 0;
  virtual void setValue( const CoordinateVector& point, ValueType value ) = 0;

  /**
  * Returns the size of each span.
  */
  virtual CoordinateVector spanSize() const = 0;
  //TODO: bounds, resize

};

} //namespace
} //namespace

#endif
