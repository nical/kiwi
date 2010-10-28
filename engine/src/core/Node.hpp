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
 * @file Node.h
 * @brief Header file for the base class of every kiwi node and filter.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.1
 */

#pragma once
#ifndef KIWI_NODE_HPP
#define KIWI_NODE_HPP

#include <list>
#include <vector>

#include <boost/scoped_ptr.hpp>

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
 * The namespace for the core of the library
 */ 
namespace core
{

class Reader;
class Writer;
class Node;
struct PortInfo
{
	Node* node;
	portIndex_t index;
};
/**
 * @class Node
 * @brief The base class for every kiwi Node and Filter
 *
 * TODO Lots of explainations needed here 
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
	virtual bool isCompatible(portIndex_t inputIndex, const OutputPort<Writer>& port) const {return false;}

	
	// TODO
	//virtual void save(std::ostream out);
	//virtual void load(std::istream in);

	
	virtual void layoutChanged() { }

// ------------------------------------------------------- pulic methods

	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth InputPort of the Node's Reader interface.
	 *
	 * @param index The index of the port.
	 */ 
	InputPort<Reader>& readerInputPort(portIndex_t index) const
		{assert(index < getReaderInputCount() ); return *_readerInputs[index];}
	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth OutputPort of the Node's Reader interface.
	 *
	 * @param index The index of the port.
	 */ 
	OutputPort<Reader>& readerOutputPort(portIndex_t index) const
		{assert(index < getReaderOutputCount() );return *_readerOutputs[index];}

	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth InputPort of the Node's Writer interface.
	 *
	 * @param index The index of the port.
	 */
	InputPort<Writer>& writerInputPort(portIndex_t index) const
		{assert(index < getWriterInputCount() );return *_writerInputs[index];}
	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth OutputPort of the Node's Writer interface.
	 *
	 * @param index The index of the port.
	 */
	OutputPort<Writer>& writerOutputPort(portIndex_t index) const
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
	 * @brief Returns true if the object is a Filter.
	 */ 
	virtual bool isAFilter() { return false; }
	
	/**
	 * @brief Returns true if the layout event is enabled.
	 * 
	 * The layout event being enabled means that 
	 */ 
	inline bool isLayoutEventEnabled() { return _layoutEvtEnabled; }
	

	portIndex_t indexOf(const ReaderInputPort& port) const;
	portIndex_t indexOf(const WriterInputPort& port) const;
	portIndex_t indexOf(const ReaderOutputPort& port) const;
	portIndex_t indexOf(const WriterOutputPort& port) const;
	

	virtual kiwi::string readerInputPortName( portIndex_t index );
	virtual kiwi::string readerOutputPortName( portIndex_t index );
	virtual kiwi::string writerInputPortName( portIndex_t index );
	virtual kiwi::string writerOutputPortName( portIndex_t index );
	
// --------------------------------------------------- protected methods	
protected:
	// port setup
	/**
	 * @brief Adds an input port to the Reader interface.
	 *
	 * This is to be used in the initialisation phase of a Node/Filter.
	 */ 
	void addReaderInputPort(const string& type, const string& name = "#");

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
	void addReaderOutputPort(const string& type, const string& name = "#");
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
	void addWriterInputPort(const string& type, const string& name = "#");
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
	void addWriterOutputPort(const string& type, const string& name = "#");
	/**
	 * @brief Remove an output port from this Filter's Writer interface.
	 *
	 * Removes The last output port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeWriterOutputPort();
	
	/**
	 * @brief Enables/disables port
	 */ 
	void setReaderInputPortEnabled(portIndex_t index, bool status)
	{ 
		readerInputPort(index).setEnabled(status);
	}
	/**
	 * @brief Enables/disables port
	 */
	void setReaderOutputPortEnabled(portIndex_t index, bool status)
	{ 
		readerOutputPort(index).setEnabled(status);
	}
	/**
	 * @brief Enables/disables port
	 */
	void setWriterInputPortEnabled(portIndex_t index, bool status)
	{ 
		writerInputPort(index).setEnabled(status);
	}
	/**
	 * @brief Enables/disables port
	 */
	void setWriterOutputPortEnabled(portIndex_t index, bool status)
	{ 
		writerOutputPort(index).setEnabled(status);
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
	void bindPort(WriterOutputPort& myPort, WriterOutputPort& toBind);
	void bindPort(ReaderInputPort& myPort, ReaderInputPort& toBind);
	void bindPort(WriterInputPort& myPort, WriterInputPort& toBind);


// ----------------------------------------------------- private members
private:

	// The input/output ports
	std::vector<InputPort<Reader>* > _readerInputs;
	std::vector<InputPort<Writer>* > _writerInputs;
	std::vector<OutputPort<Reader>* > _readerOutputs;
	std::vector<OutputPort<Writer>* > _writerOutputs;
	
	bool _layoutEvtEnabled;

//----------------------------------------------------- Internal Classes
public:

	/**
	 * @class Node::InputPort<Reader|Writer>
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
		InputPort(Node* myNode, const string& type, const string& name);
		void connect(OutputPort<SlotType>& outputPort, bool isMetaPort = true);
		void disconnect();
		inline portIndex_t index() const ;
		inline Node* node() const ;
		inline string name();
		inline string type();
		// TODO this is a temporary solution for port compatibility
		// a more flexible version is to come with use of polymorphism 
		// to get compatibility of child classes.
		inline bool isCompatible(OutputPort<SlotType>& output);
		inline bool isConnected() const ;
		inline bool isEnabled() const ;
		inline OutputPort<SlotType>* connectedOutput() const ;
		
	protected:
		inline void setName(const string& name);
		inline void setType(const string& type);
		void bind( InputPort<SlotType>& port);
		inline void setEnabled(bool status);
		
	private:
		Node* _node;
		InputPort<SlotType>* _subPort;
		OutputPort<SlotType>* _connectedNode;
		string _name;
		string _type;
		bool _enabled;
	};

	/**
	 * @class Node::OutputPort<Reader|Writer>
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
		OutputPort(Node* myNode, const string& type, const string& name);
		inline portIndex_t index() const ;
		inline Node* node() const ;
		OutputPort<SlotType>* subPort() ;//const ;
		inline string name();
		inline string type();
		// TODO this is a temporary solution for port compatibility
		// a more flexible version is to come with use of polymorphism to get compatibility of child classes.
		inline bool isCompatible(OutputPort<SlotType>& output);
			
		inline bool isConnected() const ;
		inline bool isEnabled() const ;
		inline connectionList connections() const ;
		void disconnect(); //empty the connected nodes list
		
	protected:
		inline void setName(const string& name);
		inline void setType(const string& type);
		void bind(OutputPort<SlotType>& port);
		inline void setEnabled(bool status);
		
	private:
		Node* _node;
		OutputPort<SlotType>* _subPort;
		//PortInfo _subNode; // todo remove this
		connectionList _connections;
		string _name; // TODO change this
		string _type; // and this
		bool _enabled;
	};



}; // class Node;



//------------------------------------------------------- access classes
/**
 * @class Reader
 * @brief The base class to read data from Node.
 */ 
class Reader
{
public:
	virtual ~Reader() {}
};

/**
 * @class Writer
 * @brief The base class to read and write data from Node.
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





}//namespace core

}//namespace kiwi

#include "core/Node.ih"
#include "core/InputPort.ih"
#include "core/OutputPort.ih"

#endif
