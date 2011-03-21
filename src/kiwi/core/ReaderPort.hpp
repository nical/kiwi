// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once
#ifndef KIWI_CORE_READERINPUTPORT_HPP
#define KIWI_CORE_READERINPUTPORT_HPP

//#include "kiwi/core/Node.hpp"
#include "kiwi/utils/Tags.hpp"
#include "kiwi/utils/UnorderedArray.hpp"
#include "kiwi/core/DataPort.hpp"

namespace kiwi{
namespace core{

class Node;
class Reader;
class ReaderPort;
class DataPort;


/**
 * @brief Generic input port class for Reader and Writer interface.
 *
 * An instance of this class is hold by a Node for each of it's inputs.
 * Port classes are designed to do most of the external actions on Node/Filter which are
 * doning connections between Nodes and retrieving informations on their input/output data.
 * 
 * Each port has a name which use is facultative has they are also accessed using an integer index.
 */

class ReaderPort
{
friend class Node;
public:

	/**
	 * @brief Constructor.
	 */ 
	ReaderPort(Node* myNode);

  /**
	 * @brief Returns the index of this port.
	 */ 
	portIndex_t index() const ;
	/**
	 * @brief Returns a pointer to the Node containing this port.
	 */ 
	Node* node() const ;
  
	/**
	 * @brief Returns this port's Type as a string.
	 */ 
	utils::Tags tags() const;

	/**
	 * @brief Returns a pointer to the OutputPort connected to this InputPort.
	 * 
	 * Returns 0 if not connected. 
	 */ 
	DataPort* connectedPort() const ;

	/**
	 * @brief Returns a pointer to the container provided by fthe connected
	 * data port. if there is no connection or the container could not be casted
	 * to the requested classe type, returns a nil pointer. 
	 */ 
	template<class T>
	T* safeDownCastContainer() const{
		if( isConnected() )	return connectedPort()->safeDownCastContainer<T>();
		else return 0;
	}
  
	/**
	 * @brief Connection method.
	 */ 
	bool connect(DataPort* outputPort);

  virtual const Container* getAbstractContainer() const{
    return connectedPort()->getAbstractContainer();
  }

	/**
	 * @brief Disconnect the port if connected.
	 */ 
	virtual bool disconnect( DataPort* port = 0 );

  virtual bool isConnected( DataPort* port = 0 ) const;

	/**
	 * @brief Port compatibility check based on the type tag.
	 */ 
	virtual bool isCompatible(DataPort& output) ;
	/**
	 * @brief Port compatibility check based on the type tag.
	 */ 
	virtual bool isCompatible(const kiwi::utils::Tags& tag) ;

	/**
	 * @brief returns true if this port is enabled.
	 * 
	 * A port as to be enabloed to be connected. 
	 * By default a port is enabled.
	 */ 
	virtual bool isEnabled() const ;

  virtual void updatePort() { }
	
protected:

  virtual void connect_impl( DataPort* port );
  virtual void disconnect_impl( DataPort* port );
  
	void bind( ReaderPort& port);
	/**
	 * @brief Used internally by kiwi::core::Node to enable/disable ports.
	 * 
	 * @see kiwi::core::setReaderPortEnabled
	 * @see kiwi::core::setAbstractContainerPortEnabled
	 * @see kiwi::core::setWriterPortEnabled
	 * @see kiwi::core::setAbstractContainerPortEnabled
	 */ 
	void setEnabled(bool status);

protected:
  Node* _node;
private:
	utils::UnorderedArray<ReaderPort*> _linkedInputPorts;
  DataPort* _connectedDataPort;
	bool _enabled;
};


}// namespace
}// namespace

#endif
