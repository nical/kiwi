
#pragma once
#ifndef KIWI_CORE_TEMPLATEREADERPORT_HPP
#define KIWI_CORE_TEMPLATEREADERPORT_HPP

#include "kiwi/core/ReaderPort.hpp"

namespace kiwi{
namespace core{

template<class TContainerType>
class TReaderPort : public ReaderPort
{
public:
  typedef TContainerType ContainerType;


protected:

  void connect_impl( DataPort* port );
  void disconnect_impl( DataPort* port );

  ContainerType* _tcontainer;
};


}//namespace
}//namespace


#endif
