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
 * @version 0.2
 */

#pragma once
#ifndef KIWI_NODE_HPP
#define KIWI_NODE_HPP

#include <list>
#include <vector>



#include "Commons.hpp"
#include <assert.h>
/**
 * @namespace kiwi
 * Kiwi's main namespace
 */ 
namespace kiwi
{
/**
 * @namespace kiwi::core
 * The namespace for the core of the library.
 */ 
namespace core
{

class Reader;
class Writer;
class Node;

/**
 * @class Node
 * @brief The base class for every kiwi Container and Filter
 *
 * This is the most important class in the library. kiwi::Node implements
 * the connection system that represents Kiwi's main feature.
 *
 */ 
class Node
{
public:
//---------------------------------------  Internal classes declarations
	
	template<class SlotType> class InputPort;
	template<class SlotType> class OutputPort;
	
//------------------------------------------------------------- typedefs
	
	typedef OutputPort<Reader> ReaderOutputPort;
	typedef InputPort<Reader> ReaderInputPort;
	typedef OutputPort<Writer> WriterOutputPort;
	typedef InputPort<Writer> WriterInputPort;

	enum { FILTER, CONTAINER};

// -------------------------------------------- constructor / Destructor
	/**
	 * @brief Constructor
	 */ 
	Node();


	/**
	 * @brief Destructor.
	 */ 
	virtual ~Node();



// ----------------------------------------------------- virtual methods

	virtual int nodeType() = 0;

	/**
	 * @brief Verifies the compatibility of a given Reader to one of the input ports
	 *
	 * Returns true if the output port passed in parameter is compatible with the input ports.
	 * This method must be implemented by every Node/Filter.
	 *
	 * @param inputIndex The index of the input port concerned
	 * @param port A reference to the output port that is to be checked.
	 */
	virtual bool isCompatible(portIndex_t inputIndex, const OutputPort<Reader>& port) const {return false;}
	
	/**
	 * @brief Verifies the compatibility of a given Reader to one of the input ports
	 *
	 * Returns true if the output port passed in parameter is compatible with the input ports.
	 * This method must be implemented by every Node/Filter.
	 *
	 * @param inputIndex The index of the input port concerned
	 * @param port A reference to the output port that is to be checked.
	 */virtual bool isCompatible(portIndex_t inputIndex, const OutputPort<Writer>& port) const {return false;}


	/**
	 * @brief Automatically called when port are connected or disconnected.
	 * 
	 * This virtual method is automatically called whenever a port is 
	 * connected or disconnected. One can optionnaly override it if there 
	 * is any need to execute some custom code when it happens.
	 * 
	 * By default it does nothing.
	 * 
	 * Note: This method should be overload a least only to call the parent
	 * class's method in case it does override it and you want to keep
	 * this behaviour.
	 */  
	virtual void layoutChanged() { }

// ------------------------------------------------------ pulic methods

	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth InputPort of the Node's Reader interface.
	 *
	 * @param index The index of the port.
	 */ 
	ReaderInputPort& readerInputPort(portIndex_t index) const
		{assert(index < getReaderInputCount() ); return *_readerInputs[index];}
	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth OutputPort of the Node's Reader interface.
	 *
	 * @param index The index of the port.
	 */ 
	ReaderOutputPort& readerOutputPort(portIndex_t index) const
		{assert(index < getReaderOutputCount() );return *_readerOutputs[index];}

	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth InputPort of the Node's Writer interface.
	 *
	 * @param index The index of the port.
	 */
	WriterInputPort& writerInputPort(portIndex_t index) const
		{assert(index < getWriterInputCount() );return *_writerInputs[index];}
	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth OutputPort of the Node's Writer interface.
	 *
	 * @param index The index of the port.
	 */
	WriterOutputPort& writerOutputPort(portIndex_t index) const
		{assert(index < getWriterOutputCount() );return *_writerOutputs[index];}

	/**
	 * @brief Returns the amount of Reader Inputs of this Node.
	 */ 
	inline unsigned getReaderInputCount() const {return _readerInputs.size();}
	/**
	 * @brief Returns the amount of Reader Outputs of this Node.
	 */
	inline unsigned getReaderOutputCount() const {return _readerOutputs.size();}
	/**
	 * @brief Returns the amount of Writer inputs of this Node.
	 */
	inline unsigned getWriterInputCount() const {return _writerInputs.size();}
	/**
	 * @brief Returns the amount of Writer outputs of this Node.
	 */
	inline unsigned getWriterOutputCount() const {return _readerOutputs.size();}
	
	/**
	 * @brief Returns true if the layout event is enabled.
	 * 
	 * The layout event being enabled means that 
	 */ 
	inline bool isLayoutEventEnabled() { return _layoutEvtEnabled; }
	
	/**
	 * @brief Returns the index of the port passed in parameter.
	 * 
	 * The port must belong to this Node.
	 */ 
	portIndex_t indexOf(const ReaderInputPort& port) const;
	/**
	 * @brief Returns the index of the port passed in parameter.
	 * 
	 * The port must belong to this Node.
	 */ 
	portIndex_t indexOf(const WriterInputPort& port) const;
	/**
	 * @brief Returns the index of the port passed in parameter.
	 * 
	 * The port must belong to this Node.
	 */ 
	portIndex_t indexOf(const ReaderOutputPort& port) const;
	/**
	 * @brief Returns the index of the port passed in parameter.
	 * 
	 * The port must belong to this Node.
	 */ 
	portIndex_t indexOf(const WriterOutputPort& port) const;
	
	/**
	 * @brief Returns the name of a Reader input port.
	 * 
	 * This is one of the methods to override in order to define the port's names.
	 */ 
	virtual kiwi::string readerInputName( portIndex_t index );
	/**
	 * @brief Returns the name of a Reader output port.
	 * 
	 * This is one of the methods to override in order to define the port's names.
	 */ 
	virtual kiwi::string readerOutputName( portIndex_t index );
	/**
	 * @brief Returns the name of a Writer input port.
	 * 
	 * This is one of the methods to override in order to define the port's names.
	 */ 
	virtual kiwi::string writerInputName( portIndex_t index );
	/**
	 * @brief Returns the name of a Writer output port.
	 * 
	 * This is one of the methods to override in order to define the port's names.
	 */ 
	virtual kiwi::string writerOutputName( portIndex_t index );
	
	/**
	 * @brief Returns the type of a Reader input port.
	 * 
	 * This is one of the methods to override in order to define the port's types.
	 */ 
	virtual kiwi::string readerInputType( portIndex_t index );
	/**
	 * @brief Returns the type of a reader output port.
	 * 
	 * This is one of the methods to override in order to define the port's types.
	 */ 
	virtual kiwi::string readerOutputType( portIndex_t index );
	/**
	 * @brief Returns the type of a Writer input port.
	 * 
	 * This is one of the methods to override in order to define the port's types.
	 */ 
	virtual kiwi::string writerInputType( portIndex_t index );
	/**
	 * @brief Returns the type of a Writer output port.
	 * 
	 * This is one of the methods to override in order to define the port's types.
	 */ 
	virtual kiwi::string writerOutputType( portIndex_t index );
	
// --------------------------------------------------- protected methods	
protected:
	// port setup
	/**
	 * @brief Adds an input port to the Reader interface.
	 *
	 * This is to be used in the initialisation phase of a Node/Filter.
	 */ 
	void addReaderInputPort();

	/**
	 * @brief Remove an input port from this Filter's Reader interface.
	 *
	 * Removes The last input port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeReaderInputPort();
	/**
	 * @brief Adds an output port to the Reader interface.
	 *
	 * This is to be used in the initialisation phase of a Node/Filter.
	 */ 
	void addReaderOutputPort();
	/**
	 * @brief Remove an output port from this Filter's Reader interface.
	 *
	 * Removes The last output port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeReaderOutputPort();
	/**
	 * @brief Adds an input port to the Writer interface.
	 *
	 * This is to be used in the initialisation phase of a Node/Filter.
	 */ 
	void addWriterInputPort();
	/**
	 * @brief Remove an input port from this Filter's Writer interface.
	 *
	 * Removes The last input port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeWriterInputPort();
	/**
	 * @brief Adds an output port to the Writer interface.
	 *
	 * This is to be used in the initialisation phase of a Node/Filter.
	 */ 
	void addWriterOutputPort();
	/**
	 * @brief Remove an output port from this Filter's Writer interface.
	 *
	 * Removes The last output port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeWriterOutputPort();

// ------------------------------------------------------
	
	/**
	 * @brief Enables/disables port
	 */
	template<typename SlotType>
	void setPortEnabled(InputPort<SlotType>& port, bool status)
	{
		port.setEnabled(status);
	}
	
	/**
	 * @brief Enables/disables port
	 */
	template<typename SlotType>
	void setPortEnabled(OutputPort<SlotType>& port, bool status)
	{
		port.setEnabled(status);
	}
	
	
	/**
	 * @brief Enables/disables the automatic call to layoutChanged()
	 * 
	 * Disabling layoutChanged() is sometimes necessary, for exemple 
	 * within the constructor or the destructor as in many cases
	 * layout changed needs the object to be completely initialized.
	 * Note that it is useless to disable it if layoutChanged() is not 
	 * overloaded by the child class.
	 */ 
	inline void setLayoutEventEnabled(bool status) { _layoutEvtEnabled = status; }
	
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
	void bindPort(ReaderOutputPort& myPort, ReaderOutputPort& toBind);
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
	void bindPort(WriterOutputPort& myPort, WriterOutputPort& toBind);
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
	void bindPort(ReaderInputPort& myPort, ReaderInputPort& toBind);
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
	void bindPort(WriterInputPort& myPort, WriterInputPort& toBind);

// ----------------------------------------------------- private members
private:

	// The input/output ports
	std::vector<ReaderInputPort* > _readerInputs;
	std::vector<WriterInputPort* > _writerInputs;
	std::vector<ReaderOutputPort* > _readerOutputs;
	std::vector<WriterOutputPort* > _writerOutputs;
	
	bool _layoutEvtEnabled;

//----------------------------------------------------- Internal Classes
public:

	/**
	 * @brief Generic input port class for Reader and Writer interface.
	 *
	 * An instance of this class is hold by a kNode for each of it's inputs.
	 * Port classes are designed to do most of the external actions on Node/Filter which are
	 * doning connections between Nodes and retrieving informations on their input/output data.
	 * 
	 * Each port has a name which use is facultative has they are truely accessed using an integer index.
	 */
	template<class SlotType>
	class InputPort
	{
	friend class Node;
	public:
		/**
		 * @brief Constructor.
		 * @todo The second argument will disapear in next version.
		 */ 
		InputPort(Node* myNode);
		
		/**
		 * @brief Connection method.
		 */ 
		void connect(OutputPort<SlotType>& outputPort, bool isMetaPort = true);
		/**
		 * @brief Disconnect the port if connected.
		 */ 
		void disconnect();
		/**
		 * @brief Returns the index of this port.
		 */ 
		inline portIndex_t index() const ;
		/**
		 * @brief Returns a pointer to the Node containing this port.
		 */ 
		inline Node* node() const ;
		
		InputPort<SlotType>* subPort() ;
		
		/**
		 * @brief Returns this port's Name as a string.
		 */ 
		inline string name();
		/**
		 * @brief Returns this port's Type as a string.
		 */ 
		inline string type();
		// TODO this is a temporary solution for port compatibility
		// a more flexible version is to come with use of polymorphism 
		// to get compatibility of child classes.
		/**
		 * @brief Port compatibility check based on the type string.
		 */ 
		inline bool isCompatible(OutputPort<SlotType>& output) ;
		/**
		 * @brief Resturns true if this port is connected.
		 */ 
		inline bool isConnected() const ;
		/**
		 * @brief returns true if this port is enabled.
		 * 
		 * A port as to be enabloed to be connected. 
		 * By default a port is enabled.
		 */ 
		inline bool isEnabled() const ;
		/**
		 * @brief Returns a pointer to the OutputPort connected to this InputPort.
		 * 
		 * Returns 0 if not connected. 
		 */ 
		inline OutputPort<SlotType>* connectedOutput() const ;
		
	protected:
		inline void setType(const string& type);
		/**
		 * @brief Used internally by kiwi::core::Node to perform port binding.
		 * 
		 * @see kiwi::core::Node::bindPort
		 */ 
		void bind( InputPort<SlotType>& port);
		/**
		 * @brief Used internally by kiwi::core::Node to enable/disable ports.
		 * 
		 * @see kiwi::core::setReaderInputPortEnabled
		 * @see kiwi::core::setReaderOutputPortEnabled
		 * @see kiwi::core::setWriterInputPortEnabled
		 * @see kiwi::core::setWriterOutputPortEnabled
		 */ 
		inline void setEnabled(bool status);
		
	private:
		Node* _node;
		InputPort<SlotType>* _subPort;
		OutputPort<SlotType>* _connectedNode;
//		string _type;
		bool _enabled;
	};

	/**
	 * @brief Generic output port class for Reader and Writer interface.
	 *
	 * An instance of this class is hold by a Node for each of it's outputs.
	 * Port classes are designed to do most of the external actions on Node/Filter which are
	 * doning connections between Nodes and retrieving informations on their input/output data.
	 * 
	 * Each port has a name which use is facultative has they are truely accessed using an integer index.
	 */
	template<class SlotType>
	class OutputPort
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
		inline portIndex_t index() const ;
		/**
		 * @brief Returns a pointer to the Node containing this port.
		 */ 
		inline Node* node() const ;
		
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
		OutputPort<SlotType>* subPort() ;//const ;
		/**
		 * @brief Returns this port's Type as a string.
		 */ 
		inline string name();
		/**
		 * @brief Returns this port's Type as a string.
		 */ 
		inline string type();
		// TODO this is a temporary solution for port compatibility
		// a more flexible version is to come with use of polymorphism to get compatibility of child classes.
		/**
		 * @brief Port compatibility check based on the type string.
		 */ 
		inline bool isCompatible(InputPort<SlotType>& input);
		/**
		 * @brief Resturns true if this port is connected.
		 */ 
		inline bool isConnected() const ;
		/**
		 * @brief returns true if this port is enabled.
		 * 
		 * A port as to be enabloed to be connected. 
		 * By default a port is enabled.
		 */ 
		inline bool isEnabled() const ;
		/**
		 * @brief Returns a list of the connected input ports.
		 * 
		 * Returns a std::list<kiwi::core::InputPort<T> of the port connected to this port
		 */ 
		inline connectionList connections() const ;
		/**
		 * @brief Break all of this port's connecions.
		 */ 
		void disconnect();
		
	protected:
		/**
		 * @todo deprecated
		 */ 
//		inline void setType(const string& type);
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
		inline void setEnabled(bool status);
		
	private:
		Node* _node;
		OutputPort<SlotType>* _subPort;
		connectionList _connections;
//		string _type; // to change
		bool _enabled;
	};



}; // class Node;




//------------------------------------------------------- access classes
/**
 * @class Reader
 * @brief Base class of objects that read data from Node.
 */ 
class Reader
{
public:
	virtual ~Reader() {}
};

/**
 * @class Writer
 * @brief Base class of objects that read and write data from Node.
 */
class Writer
{
public:
	virtual ~Writer() {}
};



// ----------------------------------------------------------- Operators
/**
 *	@brief Operator for connections between Node.
 * 
 * The operator to connect Nodes port in an elegant way.
 * Corresonds to InputPort::connect(OutputPort<SlotType>& outputPort);
 *
 * exemple:
 * 	// connects myNode1's first OutputPort to myNode2's second InputPort
 * 	myNode1.readerOutputPort(0) >> myNode2.readerInputPort(1);
 */ 
template <typename SlotType>
bool operator>>(Node::OutputPort<SlotType>& output, Node::InputPort<SlotType>& input );





// >_< ...
// I don't know why, this does not link when put in the cpp file ...
// #cpp build system sucks
inline void 
Node::bindPort(ReaderOutputPort& myPort, ReaderOutputPort& toBind)
{ 
	myPort.bind(toBind); 
}

inline void 
Node::bindPort(WriterOutputPort& myPort, WriterOutputPort& toBind)
{ 
	myPort.bind(toBind);
}

inline void 
Node::bindPort(ReaderInputPort& myPort, ReaderInputPort& toBind)
{ 
	myPort.bind(toBind); 
}

inline void 
Node::bindPort(WriterInputPort& myPort, WriterInputPort& toBind)
{ 
	myPort.bind(toBind); 
}





}//namespace core
}//namespace kiwi



#include "core/InputPort.ih"
#include "core/OutputPort.ih"

#endif
