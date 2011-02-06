#ifndef KIWI_GENERIC_POINTACCESSINTERACE_HPP
#define KIWI_GENERIC_POINTACCESSINTERACE_HPP

#include "kiwi/generic/RandomAccessContainerInterface.hpp"
#include "kiwi/generic/Point.hpp"

namespace kiwi{
namespace generic{

template<typename TValueType, unsigned int TDimension>
class PointAccessContainerInterface : public RandomAccessContainerInterface<TValueType>
{
public:
  typedef TValueType ValueType;
  typedef kiwi::generic::Point<kiwi::uint32_t, TDimension> Point;
  static const unsigned int Dimension = TDimension;
  // -----
  virtual ValueType getValue( const Point& point ) const = 0;
  virtual void setValue( const Point& point, ValueType value ) = 0;
  //TODO: bounds, resize

};

} //namespace
} //namespace

#endif
