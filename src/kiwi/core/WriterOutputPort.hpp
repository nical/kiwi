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

//#include "kiwi/core/Node.hpp"

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

	template<class T>
	T* getContainer() { return dynamic_cast<T*>(_container); }
	
	/**
	 * @brief Returns a pointer to the port that catually contains the Data.
	 * 
	 * If this port is binded to another port, then this method returns
	 * A pointer to this other port. If this port is not binded, then
	 * this returns a pointer to self.
	 * 
	 * This method is to be used whenever you need to access the port that
	 * is directly linked to the data. When a port A is binded to another
	 * port B, it means that A's Node doesn't contain the data whereas B
	 * (or another port C that B is binded to) has it. subPort() is called
	 * recursively untill the Node containing the data is found and returns
	 * the pointer to the corresponding port.
	 * 
	 * So this method MUST be used when accessing a Node's data through its
	 * port (when initializing Writers and Writers for instance) because
	 * you don't know if the node doesn't encapsulate other Nodes that
	 * actually contain the Data and bind it's ports to it.
	 */ 
//	const WriterOutputPort* subPort() const ;
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
	
	/**
	 * @brief Used internally by kiwi::core::Node to enable/disable ports.
	 * 
	 * @see kiwi::core::setWriterInputPortEnabled
	 * @see kiwi::core::setWriterOutputPortEnabled
	 * @see kiwi::core::setWriterInputPortEnabled
	 * @see kiwi::core::setWriterOutputPortEnabled
	 */
	void setEnabled(bool status);
	
private:
	Node* _node;
	Container* _container; 
	utils::UnorderedArray<WriterOutputPort*> _linkedOutputPorts; 
	bool _enabled;
};


}// namespace
}// namespace

#endif
