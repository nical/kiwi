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

/**
 * @file Node.hpp
 * @brief Header file for the base class of every kiwi resources and filters.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.4
 */

#pragma once
#ifndef KIWI_NODE_HPP
#define KIWI_NODE_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/Tags.hpp"

#include "kiwi/core/NodeListener.hpp"
#include "kiwi/utils/UnorderedArray.hpp"

#include <list>
#include <vector>
#include <assert.h>


/**
 * @namespace kiwi
 * Kiwi's main namespace
 */ 
namespace kiwi{

/**
 * @namespace kiwi::core
 * The namespace for the core of the library.
 */ 
namespace core{


class ReaderPort;
class WriterPort;
class DataPort;
class Container;
class NodeInitializer;

/**
 * @class Node
 * @brief The base class for every kiwi nodes, Filter in particular.
 *
 * This is the most important class in the library. kiwi::Node implements
 * the connection system that represents Kiwi's main feature.
 *
 */ 
class Node
{
public:
//--------------------------------------------------------------------- typedefs

// ---------------------------------------------------- constructor / Destructor
	/**
	 * @brief Constructor.
	 */ 
	Node();
	Node( const NodeInitializer& init );

	/**
	 * @brief Constructor.
	 *
	 * Initializes the Node with one container, adding one reader output
	 * port and one writer output port. (convenient shortcut)
	 */ 
	Node( Container* init );

	/**
	 * @brief Destructor.
	 */ 
	virtual ~Node();

// ------------------------------------------------------------- virtual methods

	virtual bool update(int phase = 0){}

	/**
	 * @brief Returns true if the Node is reday to update
	 * (process in the case of a Filter).
	 *
   * by default returns true;
	 */
	bool isReady() const { return true; } // TODO check that Containers are ready

	/**
	 * @brief Automatically called when port are connected or disconnected.
	 * 
	 * This virtual method is automatically called whenever a port is 
	 * connected or disconnected. One can optionnaly override it if there 
	 * is any need to execute some custom code when it happens.
	 * 
	 * By default it does nothing.
	 * 
	 * Note: If overloaded this method should call the parent
	 * class's method in case it does override it, to keep its behaviour.
	 */  
	virtual void layoutChanged() { }

	/**
	 * @brief Optionnal higher level interface. 
	 * 
	 * Enables the Node derived classes to react from custom high level 
	 * interface.
	 * The command passed to the Node is a string and the result may 
	 * only return a string.
	 * The purpose of this is to enable a runtime resolved interface for
	 * client-server usage. 
	 */ 
	virtual kiwi::string strCommand( const kiwi::string& command);
	
	
// ------------------------------------------------------ pulic methods

	/**
	 * @brief Set this Node's Listener.
	 *
	 * A NodeListener is a class that can listen to a Node in order to
	 * detect when the Node's layout changes (a port is created etc...).
	 *
	 * This feature is intended for user interfaces or controlers, so that
	 * they can be aware of when a Node changes. 
	 * kiwi::core::NodeListener is an abstract class that can be inherited
	 * by any user-defined class.
	 */ 
	void setListener( NodeListener* listener ) { _listener = listener; }

	/**
	 * @brief Returns true if this Node has a Listener.
	 */ 
	bool hasListener() const { return _listener != 0; }

	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth InputPort of the Node's Reader interface.
	 *
	 * @param index The index of the port.
	 */ 
	ReaderPort& readerPort(portIndex_t index) const
		{assert(index < nbReaderPorts() ); return *_readerPorts[index];}
	
	
	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth InputPort of the Node's Writer interface.
	 *
	 * @param index The index of the port.
	 */
   
	WriterPort& writerPort(portIndex_t index) const
		{assert(index < nbWriterPorts() );return *_writerPorts[index];}
	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth OutputPort of the Node's Writer interface.
	 *
	 * @param index The index of the port.
	 */
	DataPort& dataPort(portIndex_t index) const
		{assert(index < nbDataPorts() );return *_dataPorts[index];}

	/**
	 * @brief Returns the amount of data ports of this Node.
	 */ 
	inline kiwi::portIndex_t nbDataPorts() const {return _dataPorts.size();}
	/**
	 * @brief Returns the amount of Reader inputs of this Node.
	 */
	inline kiwi::portIndex_t nbReaderPorts() const {return _readerPorts.size();}
	/**
	 * @brief Returns the amount of Writer inputs of this Node.
	 */
	inline kiwi::portIndex_t nbWriterPorts() const {return _writerPorts.size();}
	
	

	/**
	 * @brief Returns the index of the port passed in parameter.
	 * 
	 * The port must belong to this Node.
	 */ 
	portIndex_t indexOf(const DataPort& port) const;
	/**
	 * @brief Returns the index of the port passed in parameter.
	 * 
	 * The port must belong to this Node.
	 */ 
	portIndex_t indexOf(const WriterPort& port) const;
	/**
	 * @brief Returns the index of the port passed in parameter.
	 * 
	 * The port must belong to this Node.
	 */ 
	portIndex_t indexOf(const ReaderPort& port) const;
	
	
	
	/**
	 * @brief Returns the type of a Reader input port.
	 * 
	 * This is one of the methods to override in order to define the port's types.
	 */ 
	virtual kiwi::Tags readerTags( portIndex_t index ) const;
	/**
	 * @brief Returns the type of a reader output port.
	 * 
	 * This is one of the methods to override in order to define the port's types.
	 */ 
	virtual kiwi::Tags writerTags( portIndex_t index ) const;
	/**
	 * @brief Returns the type of a Writer input port.
	 * 
	 * This is one of the methods to override in order to define the port's types.
	 */ 
	virtual kiwi::Tags dataTags( portIndex_t index ) const;
	
// --------------------------------------------------- protected methods	
protected:
	/**
	 * @brief Adds an input port to the Reader interface.
	 *
	 * This is meant to be used in the initialisation phase of a Node/Filter.
	 * 
	 * @return the index of the added port.
	 */ 
	portIndex_t addReaderPort( ReaderPort* port );
  
	portIndex_t addReaderPort();

	/**
	 * @brief Remove an input port from this Filter's Reader interface.
	 *
	 * Removes The last input port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeReaderPort();
	/**
	 * @brief Adds an output port to the Reader interface.
	 *
	 * This is meant to be used in the initialisation phase of a Node/Filter.
	 * 
	 * @return the index of the added port.
	 */ 
	portIndex_t addDataPort( DataPort* port );

  portIndex_t addDataPort(Container* data = 0, kiwi::uint8_t flags = 3);


  /**
	 * @brief Remove an output port from this Filter's Reader interface.
	 *
	 * Removes The last output port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeDataPort();
	/**
	 * @brief Adds an input port to the Writer interface.
	 *
	 * This is meant to be used in the initialisation phase of a Node/Filter.
	 * 
	 * @return the index of the added port.
	 */ 
	portIndex_t addWriterPort( WriterPort* port );

  
	portIndex_t addWriterPort();

  
	/**
	 * @brief Remove an input port from this Filter's Writer interface.
	 *
	 * Removes The last input port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeWriterPort();
	
	

	void addContainer(Container* data, bool addPort = true, kiwi::uint8_t flags = 3);

// ------------------------------------------------------
	

	void setDataPortContainer(DataPort& port, Container* container);
	
	
	/**
	 * @brief Redirect a port to the port another Node's port.
	 * 
	 * bindPort allows a Node to have ports that are in fact pointing 
	 * to another Node instead of itself.
	 * Each port contains knows both the Node that contains it and also
	 * the Node that actuly contains the data.
	 * This distinction permits to have for instance a Node that 
	 * contains other Nodes and redirects its ports to the one of the
	 * contained Node (for exemple Pipelines). 
	 * Another use of this method is for any Filter that writes in a 
	 * Node to provide the output readers of the Node in its own
	 * outputs.
	 * 
	 * @param myPort This class's port that has to be redirected to another Node's port.
	 * @param toBind The other Node's port.
	 */
	void bindPort(DataPort& myPort, DataPort& toBind);
	
	/**
	 * @brief Redirect a port to the port another Node's port.
	 * 
	 * bindPort allows a Node to have ports that are in fact pointing 
	 * to another Node instead of itself.
	 * Each port contains knows both the Node that contains it and also
	 * the Node that actuly contains the data.
	 * This distinction permits to have for instance a Node that 
	 * contains other Nodes and redirects its ports to the one of the
	 * contained Node (for exemple Pipelines). 
	 * Another use of this method is for any Filter that writes in a 
	 * Node to provide the output readers of the Node in its own
	 * outputs.
	 * 
	 * @param myPort This class's port that has to be redirected to another Node's port.
	 * @param toBind The other Node's port.
	 */ 
	void bindPort(ReaderPort& myPort, ReaderPort& toBind);

	/**
	 * @brief Redirect a port to the port another Node's port.
	 * 
	 * bindPort allows a Node to have ports that are in fact pointing 
	 * to another Node instead of itself.
	 * Each port contains knows both the Node that contains it and also
	 * the Node that actuly contains the data.
	 * This distinction permits to have for instance a Node that 
	 * contains other Nodes and redirects its ports to the one of the
	 * contained Node (for exemple Pipelines). 
	 * Another use of this method is for any Filter that writes in a 
	 * Node to provide the output readers of the Node in its own
	 * outputs.
	 * 
	 * @param myPort This class's port that has to be redirected to another Node's port.
	 * @param toBind The other Node's port.
	 */ 
	void bindPort(WriterPort& myPort, WriterPort& toBind);


	

// ----------------------------------------------------- private members
private:

	utils::UnorderedArray<Container*> _containers;	
	// The input/output ports
	std::vector<ReaderPort*> _readerPorts;
	std::vector<WriterPort*> _writerPorts;
	std::vector<DataPort*> _dataPorts;
	
	NodeListener* _listener;

}; // class Node;





// ----------------------------------------------------------- Operators
/**
 *	@brief Operator for connections between Node.
 * 
 * The operator to connect Nodes port in an elegant way.
 * Corresonds to InputPort::connect(OutputPort<SlotType>& outputPort);
 *
 * exemple:
 * 	// connects myNode1's first OutputPort to myNode2's second InputPort
 * 	myNode1.dataPort(0) >> myNode2.readerPort(1);
 */ 
bool operator >> (DataPort& output, ReaderPort& input );

/**
 *	@brief Operator for connections between Node.
 * 
 * The operator to connect Nodes port in an elegant way.
 * Corresonds to InputPort::connect(OutputPort<SlotType>& outputPort);
 *
 * exemple:
 * 	// connects myNode1's first OutputPort to myNode2's second InputPort
 * 	myNode1.dataPort(0) >> myNode2.readerPort(1);
 */ 
bool operator>>(DataPort& output, WriterPort& input );


/**
 * @brief This class is not yet ready for use.
 */ 
class NodeInitializer
{
public:
	void addContainer(Container* data, bool addReader = true, bool addWrier = false);
	kiwi::uint32_t nbContainers() const;
	Container* container(kiwi::uint32_t index) const;
	bool addReader(kiwi::uint32_t index) const;
	bool addWriter(kiwi::uint32_t index) const;
	
private:	
	struct ContainerInit{ Container* container; bool addReader; bool addWriter; };
	utils::UnorderedArray<ContainerInit> _data;
};



/**
 * @brief optionnal macro that produces typedef vType ValueType;
 */ 
#define ValueTypeMacro( vType ) typedef vType ValueType;

}//namespace core
}//namespace kiwi


#endif
