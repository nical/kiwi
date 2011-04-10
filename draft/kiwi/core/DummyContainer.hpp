
#ifndef KIWI_DUMMY_CONTAINER_HPP
#define KIWI_DUMMY_CONTAINER_HPP

#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/Tuple.hpp"

class IntContainer : public kiwi::core::Container
{
public:
  int& value() { return *_value; }
  const int& value() const { return *_value; }
  void init( int* ptr ){ _value = ptr; }
protected:
  int* _value;
};

class Vector3iContainer
: public kiwi::core::CompositeContainer<TypeList_3(IntContainer,IntContainer,IntContainer)>
{
public:
    Vector3iContainer(int x = 0, int y = 0, int z = 0){
      _data[0] = x;
      _data[1] = y;
      _data[2] = z;
      subContainer<0>().init( &_data[0] );
      subContainer<1>().init( &_data[1] );
      subContainer<2>().init( &_data[2] );
    }
    int& operator[](int i){
      return _data[i];
    }
    int _data[3];
};

#endif
