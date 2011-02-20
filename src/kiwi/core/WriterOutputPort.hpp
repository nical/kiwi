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

#ifndef KIWI_CORE_WRITEROUTPUTPORT_HPP
#define KIWI_CORE_WRITEROUTPUTPORT_HPP

#include <list>
#include "kiwi/core/Tags.hpp"
#include "kiwi/utils/UnorderedArray.hpp"
#include "kiwi/utils/Connector.hpp"



namespace kiwi{
namespace core{

class WriterInputPort;
class Node;

/**
 * @brief Generic output port class for Writer and Writer interface.
 *
 * An instance of this class is hold by a Node for each of it's outputs.
 * Port classes are designed to do most of the external actions on Node/Filter which are
 * doning connections between Nodes and retrieving informations on their input/output data.
 * 
 * Each port has a name which use is facultative has they are truely accessed using an integer index.
 */ 
class WriterOutputPort
: public kiwi::utils::Connector<WriterOutputPort, WriterInputPort, 100, WRITER>
{
friend class Node;
public:
friend class WriterInputPort;

	typedef kiwi::utils::Connector<WriterOutputPort, WriterInputPort, 100, WRITER> PortConnector;

	// --------------------------------------------------------------------
	typedef std::list< WriterInputPort* > connectionList;
	
	// --------------------------------------------------------------------
	/**
	 * @brief Constructor.
	 * @todo The second argument will disapear in next version.
	 */ 
	WriterOutputPort(Node* myNode, Container* data = 0);
	/**
	 * @brief Returns the index of this port.
	 */ 
	portIndex_t index() const ;
	/**
	 * @brief Returns a pointer to the Node containing this port.
	 */ 
	Node* node() const ;

	/**
	 * @brief Returns true if this port has sub-ports.
	 *
	 * This happens when the port is associated to a composite Container. 
	 */ 
	bool isComposite() const;

	WriterOutputPort& subPort(kiwi::uint32_t i){
		if(i >= _subPorts.size() )
			return *this;
		return *_subPorts[i];
	}

	template<class T>
	T* getContainer() { return dynamic_cast<T*>(_container); }

	ReaderOutputPort* associatedReaderOutputPort(){
		ScopedBlockMacro( ___scp, "WriterOutputPort::associatedReaderOutputPort");
		if(!_associatedReaderOutputPort)
			Debug::print() << "warning: no associated port\n";
		return _associatedReaderOutputPort;
	}
	

	/**
	 * @brief Returns this port's Type as a string.
	 */ 
	string name() const;
	/**
	 * @brief Returns this port's Type as a string.
	 */ 
	Tags tags() const;
	
	/**
	 * @brief Port compatibility check based on the type string.
	 */ 
	bool isCompatible(WriterInputPort& input);

	/**
	 * @brief returns true if this port is enabled.
	 * 
	 * A port as to be enabloed to be connected. 
	 * By default a port is enabled.
	 */ 
	bool isEnabled() const ;
	/**
	 * @brief Returns a list of the connected input ports.
	 * 
	 * Returns a std::list<kiwi::core::InputPort<T> of the port connected to this port
	 */ 
	connectionList connections() const ;
 
	
	bool connect(WriterInputPort& inputPort);
	bool connect(WriterInputPort* inputPort);
	
protected:

	/**
	 * @brief Used internally by kiwi::core::Node to perform port binding.
	 * 
	 * @see kiwi::core::Node::bindPort
	 */ 
	void bind( WriterOutputPort& port );

	void unBind();

	void setData( Container* data );
	
	
private:
	Node* _node;
	Container* _container;
	// port binding
	utils::UnorderedArray<WriterOutputPort*> _linkedOutputPorts;
	// to use with composite containers  
	utils::UnorderedArray<WriterOutputPort*> _subPorts;
	// to associate Writer and Reader of the same data
	ReaderOutputPort* _associatedReaderOutputPort;
};


}// namespace
}// namespace

#endif
