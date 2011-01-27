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

#ifndef KIWI_CORE_OUTPUTPORT_HPP
#define KIWI_CORE_OUTPUTPORT_HPP

//#include "kiwi/core/Node.hpp"

#include <list>
#include "kiwi/core/Tags.hpp"
#include "kiwi/utils/UnorderedArray"

namespace kiwi{
namespace core{

template <class T> class InputPort;
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
template<class SlotType> class OutputPort
{
friend class Node;
public:
friend class InputPort<SlotType>;
	// --------------------------------------------------------------------
	typedef typename std::list< InputPort<SlotType>* > connectionList;
	
	// --------------------------------------------------------------------
	/**
	 * @brief Constructor.
	 * @todo The second argument will disapear in next version.
	 */ 
	OutputPort(Node* myNode);
	/**
	 * @brief Returns the index of this port.
	 */ 
	portIndex_t index() const ;
	/**
	 * @brief Returns a pointer to the Node containing this port.
	 */ 
	Node* node() const ;
	
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
	 * port (when initializing Readers and Writers for instance) because
	 * you don't know if the node doesn't encapsulate other Nodes that
	 * actually contain the Data and bind it's ports to it.
	 */ 
	const OutputPort<SlotType>* subPort() const ;
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
	bool isCompatible(InputPort<SlotType>& input);
	/**
	 * @brief Resturns true if this port is connected.
	 */ 
	bool isConnected() const ;
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
	/**
	 * @brief Disconnect from a given port.
	 *
	 * If the parameter input id equal to 0, breaks all of this
	 * port's connecions (this is the default behaviour when no
	 * input port is specified).
	 */ 
	void disconnect( InputPort<SlotType>* input = 0);
	
protected:

	/**
	 * @brief Used internally by kiwi::core::Node to perform port binding.
	 * 
	 * @see kiwi::core::Node::bindPort
	 */ 
	void bind(OutputPort<SlotType>& port);
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
	Container* _container;
	utils::UnorderedArray<OutputPort<SlotType>*> _linkedOutputPorts; 
	OutputPort<SlotType>* _subPort; //deprecated
	connectionList _connections;
	bool _enabled;
};



template class OutputPort<Reader>;
template class OutputPort<Writer>;

}// namespace
}// namespace

#endif
