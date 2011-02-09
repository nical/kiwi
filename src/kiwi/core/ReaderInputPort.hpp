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
#include "kiwi/core/Tags.hpp"
#include "kiwi/utils/Connector.hpp"
#include "kiwi/utils/UnorderedArray.hpp"
#include "kiwi/core/ReaderOutputPort.hpp"

namespace kiwi{
namespace core{

class Node;
class Reader;
class ReaderInputPort;
class ReaderOutputPort;


/**
 * @brief Generic input port class for Reader and Writer interface.
 *
 * An instance of this class is hold by a Node for each of it's inputs.
 * Port classes are designed to do most of the external actions on Node/Filter which are
 * doning connections between Nodes and retrieving informations on their input/output data.
 * 
 * Each port has a name which use is facultative has they are also accessed using an integer index.
 */

class ReaderInputPort
: public kiwi::utils::Connector<ReaderInputPort, ReaderOutputPort, 1, READER>
{
friend class Node;
public:

	typedef kiwi::utils::Connector<ReaderInputPort, ReaderOutputPort, 1, READER> PortConnector;

	/**
	 * @brief Constructor.
	 * @todo The second argument will disapear in next version.
	 */ 
	ReaderInputPort(Node* myNode);
	
	/**
	 * @brief Connection method.
	 */ 
	bool connect(ReaderOutputPort& outputPort);
	bool connect(ReaderOutputPort* outputPort);
	/**
	 * @brief Disconnect the port if connected.
	 */ 
//	void disconnect();
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
	Tags tags() const;
	// TODO this is a temporary solution for port compatibility
	// a more flexible version is to come with use of polymorphism 
	// to get compatibility of child classes.
	/**
	 * @brief Port compatibility check based on the type tag.
	 */ 
	bool isCompatible(ReaderOutputPort& output) ;
	/**
	 * @brief Port compatibility check based on the type tag.
	 */ 
	bool isCompatible(const kiwi::Tags& tag) ;

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
	ReaderOutputPort* connectedOutput() const ;

	template<class T>
	T* getContainer() const{
		if( isConnected() )	return connectedOutput()->getContainer<T>();
		else return 0;
	}

	
protected:
	void setType(const string& type);
	/**
	 * @brief Used internally by kiwi::core::Node to perform port binding.
	 * 
	 * @see kiwi::core::Node::bindPort
	 */ 
	void bind( ReaderInputPort& port);
	/**
	 * @brief Used internally by kiwi::core::Node to enable/disable ports.
	 * 
	 * @see kiwi::core::setReaderInputPortEnabled
	 * @see kiwi::core::setReaderOutputPortEnabled
	 * @see kiwi::core::setWriterInputPortEnabled
	 * @see kiwi::core::setWriterOutputPortEnabled
	 */ 
	void setEnabled(bool status);
	
private:
	Node* _node;
	utils::UnorderedArray<ReaderInputPort*> _linkedInputPorts;
	bool _enabled;
};


}// namespace
}// namespace

#endif
