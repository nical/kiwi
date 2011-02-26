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

#ifndef KIWI_CORE_READEROUTPUTPORT_HPP
#define KIWI_CORE_READEROUTPUTPORT_HPP

//#include "kiwi/core/Node.hpp"

#include <list>
#include "kiwi/core/Tags.hpp"
#include "kiwi/utils/UnorderedArray.hpp"
#include "kiwi/utils/Connector.hpp"



namespace kiwi{
namespace core{

class ReaderPort;
class Node;

/**
 * @brief Generic output port class for Reader and Writer interface.
 *
 * An instance of this class is hold by a Node for each of it's outputs.
 * Port classes are designed to do most of the external actions on Node/Filter which are
 * doning connections between Nodes and retrieving informations on their input/output data.
 * 
 * Each port has a name which use is facultative has they are truely accessed using an integer index.
 */ 
class DataPort
: public kiwi::utils::Connector<DataPort, ReaderPort, 32, READER>
, public kiwi::utils::Connector<DataPort, WriterPort, 32, READER>
{
friend class Node;
public:
friend class ReaderPort;
friend class WriterPort;

	typedef kiwi::utils::Connector<DataPort, ReaderPort, 32, READER> ReaderConnector;
	typedef kiwi::utils::Connector<DataPort, WriterPort, 32, WRITER> WriterConnector;

	// --------------------------------------------------------------------
	/**
	 * @brief Constructor.
	 */ 
	DataPort(Node* myNode, Container* data = 0);
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
	bool isComposite() const ;

	DataPort& subPort(kiwi::uint32_t i){
		if(i >= _subPorts.size() ){
			Debug::error() << "DataPort::subPort: subPort not found!\n";
			return *this;
		}
		return *_subPorts[i];
	}

	kiwi::uint32_t nbSubPorts() const { return _subPorts.size(); }

	template<class T>
	T* getContainer() { return dynamic_cast<T*>(_container); }
	
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
	bool isCompatible(ReaderPort& input);

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
	//connectionList connections() const ;
 
	
	bool connect(ReaderPort& port);
	bool connect(ReaderPort* port);
	
	bool connect(WriterPort& port);
	bool connect(WriterPort* port);
	
protected:

	/**
	 * @brief Used internally by kiwi::core::Node to perform port binding.
	 * 
	 * @see kiwi::core::Node::bindPort
	 */ 
	void bind( DataPort& port );

	void unBind();

	/**
	 * @brief Sets this port's container.
	 */ 
	void setContainer( Container* data );
	
private:
	Node* _node;
	Container* _container; 
	utils::UnorderedArray<DataPort*> _linkedOutputPorts;
	utils::UnorderedArray<DataPort*> _subPorts;
};


}// namespace
}// namespace

#endif
