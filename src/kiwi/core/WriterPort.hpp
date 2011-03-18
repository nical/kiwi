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
#ifndef KIWI_CORE_WRITERINPUTPORT_HPP
#define KIWI_CORE_WRITERINPUTPORT_HPP

#include "kiwi/utils/Tags.hpp"
#include "kiwi/utils/UnorderedArray.hpp"
#include "kiwi/core/DataPort.hpp"

namespace kiwi{
namespace core{

class Node;
class WriterPort;


/**
 * @brief Generic input port class for Writer and Writer interface.
 *
 * An instance of this class is hold by a Node for each of it's inputs.
 * Port classes are designed to do most of the external actions on Node/Filter which are
 * doning connections between Nodes and retrieving informations on their input/output data.
 * 
 * Each port has a name which use is facultative has they are also accessed using an integer index.
 */

class WriterPort
{
friend class Node;
friend class Filter;
public:

	/**
	 * @brief Constructor.
	 */ 
	WriterPort(Node* myNode);
	virtual ~WriterPort(){}
	
	/**
	 * @brief Connection method.
	 */ 
	bool connect(DataPort* outputPort);

	/**
	 * @brief Returns the index of this port.
	 */ 
	portIndex_t index() const ;
	/**
	 * @brief Returns a pointer to the Node containing this port.
	 */ 
	Node* node() const ;
		
	/**
	 * @brief Returns this port's Name as a string.
	 */ 
	string name() const;
	/**
	 * @brief Returns this port's Type as a string.
	 */ 
	utils::Tags tags() const;

  /**
	 * @brief returns true if this port is enabled.
	 * 
	 * A port as to be enabloed to be connected. 
	 * By default a port is enabled.
	 */ 
	bool isEnabled() const ;
	/**
	 * @brief Returns a pointer to the OutputPort connected to this InputPort.
	 * 
	 * Returns 0 if not connected. 
	 */ 
	DataPort* connectedPort() const ;

	/**
	 * @brief Returns a pointer to the container provided by fthe connected
	 * data port.
	 *
	 * If there is no connection or the container could not be casted
	 * to the requested classe type, returns a nil pointer. 
	 */ 
	template<class T>
	T* safeDownCastContainer() const{
	ScopedBlockMacro("WriterPort::safeDownCastContainer")
		if( isConnected() ){
			return connectedPort()->safeDownCastContainer<T>();	
		}	else return 0;
	}

  bool isConnected( DataPort* port = 0 ) const;

  bool disconnect( DataPort* port = 0 );

  
	/**
	 * @brief Port compatibility check based on the type tag.
	 */ 
	virtual bool isCompatible(DataPort& output) ;
	
  virtual void updatePort() { }
	
protected:

  virtual void connect_impl( DataPort* port );

  virtual void disconnect_impl( DataPort* port );

	/**
	 * @brief Used internally by kiwi::core::Node to perform port binding.
	 * 
	 * @see kiwi::core::Node::bindPort
	 */ 
	void bind( WriterPort& port);
	/**
	 * @brief Used internally by kiwi::core::Node to enable/disable ports.
	 * 
	 * @see kiwi::core::setWriterPortEnabled, kiwi::core::setContainerPortEnabled,
	 * kiwi::core::setContainerPortEnabled
	 */ 
	void setEnabled(bool status);

	void associateReaderPort(DataPort* reader){
		_associatedDataPort = reader;
	}
	
private:
	Node* _node;
	utils::UnorderedArray<WriterPort*> _linkedInputPorts;
	DataPort* _associatedDataPort;
	DataPort* _connectedDataPort;
	bool _enabled;
};


}// namespace
}// namespace

#endif
