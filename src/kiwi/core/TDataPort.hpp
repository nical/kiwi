
#pragma once
#ifndef KIWI_CORE_TEMPLATEDATAPORT_HPP
#define KIWI_CORE_TEMPLATEDATAPORT_HPP

#include "kiwi/core/DataPort.hpp"

namespace kiwi{
namespace core{

template<class TContainerType>
class TDataPort : public DataPort
{
public:
  typedef TContainerType ContainerType;


  virtual Container* getAbstractContainer() const{
    return _tcontainer;
  }
  
	/**
	 * @brief returns true if this port is enabled.
	 * 
	 * A port as to be enabloed to be connected. 
	 * By default a port is enabled.
	 */ 
	virtual bool isEnabled() const ;

	/**
	 * @brief returns true if this data port is connected to at least one reader port.
	 */ 
	virtual bool isConnectedToReader( ReaderPort* port = 0) const{
    if(!port) return _connectedReaders.size() > 0;
		return (_connectedReaders.find(port) != -1);
	}

	/**
	 * @brief Returns true if this data port is connected to at least one writer port.
	 */ 
	virtual bool isConnectedToWriter( WriterPort* port = 0 ) const{
    if(!port) return _connectedWriters.size() > 0;
		return (_connectedWriters.find(port) != -1);
	}


protected:

  void connect_impl( ReaderPort* port );
  void disconnect_impl( ReaderPort* port );
  void connect_impl( WriterPort* port );
  void disconnect_impl( WriterPort* port );

  ContainerType* _tcontainer;
};


}//namespace
}//namespace


#endif
