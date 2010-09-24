//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

/**
 * @file Resource.h
 * @brief Header file for the base class of every kiwi resource and filter.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.1
 */

#pragma once
#ifndef KIWI_RESOURCE_HPP
#define KIWI_RESOURCE_HPP

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

/**
 * @brief The base class for every kiwi Resource and Filter
 *
 * TODO Lots of explainations needed here 
 *
 */ 
class Resource
{
public:
//---------------------------------------  Internal classes declarations
	
	template<class SlotType> class InputPort;
	template<class SlotType> class OutputPort;
	
//------------------------------------------------------------- typedefs
	/**
	 * The scalar type used for indexing the ports.
	 */ 
	//typedef unsigned char portIndex_t;


// -------------------------------------------- constructor / Destructor
	/**
	 * Constructor
	 */ 
	Resource();


	/**
	 * Destructor
	 */ 
	virtual ~Resource();



// ----------------------------------------------------- virtual methods

	/**
	 * @brief Verifies the compatibility of a given Reader to one of the input ports
	 *
	 * Returns true if the output port passed in parameter is compatible with the input ports.
	 * This method must be implemented by every Resource/Filter.
	 *
	 * @param inputIndex The index of the input port concerned
	 * @param port A reference to the output port that is to be checked.
	 */
	virtual bool isCompatible(portIndex_t inputIndex, const OutputPort<Reader>& port) const {return false;}
	virtual bool isCompatible(portIndex_t inputIndex, const OutputPort<Writer>& port) const {return false;}

	
	/// TODO
	//virtual void save(std::ostream out);
	//virtual void load(std::istream in);

	
	virtual void layoutChanged() { }

// ------------------------------------------------------- pulic methods

	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth InputPort of the Resource's Reader interface.
	 *
	 * @param index The index of the port.
	 */ 
	InputPort<Reader>& readerInputPort(portIndex_t index) const
		{assert(index < getReaderInputCount() ); return *_readerInputs[index];}
	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth OutputPort of the Resource's Reader interface.
	 *
	 * @param index The index of the port.
	 */ 
	OutputPort<Reader>& readerOutputPort(portIndex_t index) const
		{assert(index < getReaderOutputCount() );return *_readerOutputs[index];}

	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth InputPort of the Resource's Writer interface.
	 *
	 * @param index The index of the port.
	 */
	InputPort<Writer>& writerInputPort(portIndex_t index) const
		{assert(index < getWriterInputCount() );return *_writerInputs[index];}
	/**
	 * @brief Access to a port.
	 *
	 * Retrives the indexth OutputPort of the Resource's Writer interface.
	 *
	 * @param index The index of the port.
	 */
	OutputPort<Writer>& writerOutputPort(portIndex_t index) const
		{assert(index < getWriterOutputCount() );return *_writerOutputs[index];}

	/**
	 * Returns the amount of Reader Inputs of this Resource.
	 */ 
	inline unsigned getReaderInputCount() const {return _readerInputs.size();}
	/**
	 * Returns the amount of Reader Outputs of this Resource.
	 */
	inline unsigned getReaderOutputCount() const {return _readerOutputs.size();}
	/**
	 * Returns the amount of Writer inputs of this Resource.
	 */
	inline unsigned getWriterInputCount() const {return _writerInputs.size();}
	/**
	 * Returns the amount of Writer outputs of this Resource.
	 */
	inline unsigned getWriterOutputCount() const {return _readerOutputs.size();}
	
	virtual bool isAFilter() {return false;}
	
// --------------------------------------------------- protected methods	
protected:
	// port setup
	/**
	 * @brief Adds an input port to the Reader interface.
	 *
	 * Adds an input port to the Reader interface
	 * This is to be used in the initialisation phase of a Resource/Filter.
	 */ 
	void addReaderInputPort(const string& name = "#");

	/**
	 * @brief Remove an input port from this Filter's Reader interface.
	 *
	 * Removes The last input port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeReaderInputPort();
	/**
	 * @brief Adds an output port to the Reader interface.
	 *
	 * Adds an output port to the Reader interface
	 * This is to be used in the initialisation phase of a Resource/Filter.
	 */ 
	void addReaderOutputPort(const string& name = "#");
	/**
	 * @brief Remove an output port from this Filter's Reader interface.
	 *
	 * Removes The last output port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeReaderOutputPort();
	/**
	 * @brief Adds an input port to the Writer interface.
	 *
	 * Adds an input port to the Writer interface
	 * This is to be used in the initialisation phase of a Resource/Filter.
	 */ 
	void addWriterInputPort(const string& name = "#");
	/**
	 * @brief Remove an input port from this Filter's Writer interface.
	 *
	 * Removes The last input port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeWriterInputPort();
	/**
	 * @brief Adds an output port to the Writer interface.
	 *
	 * Adds an output port to the Writer interface
	 * This is to be used in the initialisation phase of a Resource/Filter.
	 */ 
	void addWriterOutputPort(const string& name = "#");
	/**
	 * @brief Remove an output port from this Filter's Writer interface.
	 *
	 * Removes The last output port (the one oh highest index) from this Filter's Reader interface.
	 */
	void removeWriterOutputPort();
	
	

// ----------------------------------------------------- private members
private:

	// The input/output ports
	std::vector<InputPort<Reader>* > _readerInputs;
	std::vector<InputPort<Writer>* > _writerInputs;
	std::vector<OutputPort<Reader>* > _readerOutputs;
	std::vector<OutputPort<Writer>* > _writerOutputs;

//----------------------------------------------------- Internal Classes
public:

	/**
	 * @class Resource::InputPort<Reader|Writer>
	 * @brief Generic input port class for Reader and Writer interface.
	 *
	 * An instance of this class is hold by a kResource for each of it's inputs.
	 * Port classes are designed to do most of the external actions on Resource/Filter which are
	 * doning connections between Resources and retrieving informations on their input/output data.
	 * 
	 * Each port has a name which use is facultative has they are truely accessed using an integer index.
	 */
	template<class SlotType>
	class InputPort
	{
	public:
		InputPort(Resource* myResource, portIndex_t myPort, const string& name);
		void connect(OutputPort<SlotType>& outputPort);
		void disconnect();
		string getName() {return _name;}
		bool isCompatible(OutputPort<SlotType>& output)	{return false;}
		inline bool isConnected() const {return (_connectedResource != 0);}
		OutputPort<SlotType>* connectedOutput() const {return _connectedResource;}
		inline portIndex_t index() const {return _myIndex;}
		inline Resource* resource() const {return _myResource;}	
		
	protected:
		OutputPort<SlotType>* _connectedResource; // the Resource that in input of this
		Resource* _myResource; 		// this Resource
		portIndex_t _myIndex;			// the index of this port
		string _name;
	};

	/**
	 * @class Resource::OutputPort<Reader|Writer>
	 * @brief Generic output port class for Reader and Writer interface.
	 *
	 * An instance of this class is hold by a Resource for each of it's outputs.
	 * Port classes are designed to do most of the external actions on Resource/Filter which are
	 * doning connections between Resources and retrieving informations on their input/output data.
	 * 
	 * Each port has a name which use is facultative has they are truely accessed using an integer index.
	 */
	template<class SlotType>
	class OutputPort
	{
	public:
	friend class InputPort<SlotType>;
		// --------------------------------------------------------------------
		typedef typename std::list< InputPort<SlotType>* > connectionList;
		
		// --------------------------------------------------------------------
		OutputPort(Resource* myResource, portIndex_t myPort, const string& name);
		inline portIndex_t index() const {return _myIndex;}
		inline Resource* resource() const {return _myResource;}
		string getName() {return _name;}
		inline bool isConnected() const {return (_connections.size() != 0); }
		connectionList connections() const {return _connections;}
		void disconnect(); //empty the connected resources list
		
	protected:
		Resource* _myResource;
		portIndex_t _myIndex;
		connectionList _connections;
		string _name;
	};



}; // class Resource;

//------------------------------------------------------- access classes
/**
 * @class Resource::Reader
 * @brief The base class to read data from Resources.
 */ 
class Reader
{
public:
	// TODO any way to force the children classes to implement the following constructor ?
	//Reader(const Resource::InputPort<Reader>& port);
	virtual ~Reader() {}
};

/**
 * @class Resource::Reader
 * @brief The base class to read and write data from Resources.
 */ 
class Writer
{
public:
	virtual ~Writer() {}
};
/*
class PortInfo
{
public:
	PortInfo(Resource* resource, unsigned int port) 
		: _resource(resource), _port(port){}
	Resource* resource() const {return _resource;}
	unsigned int port() const {return _port;}
protected:
	Resource* _resource;
	unsigned int port;
};
*/
// ----------------------------------------------------------- Operators
/**
 *	@brief Operator for connections between Resource
 * 
 * The operator to connect Resources port in an elegant way.
 * Corresonds to InputPort::connect(OutputPort<SlotType>& outputPort);
 *
 * exemple:
 * 	// connects myResource1's first OutputPort to myResource2's second InputPort
 * 	myResource1.readerOutputPort(0) >> myResource2.readerInputPort(1);
 */ 
template <typename SlotType>
bool operator>>(Resource::OutputPort<SlotType>& output, Resource::InputPort<SlotType>& input );




/**
 * @def AllocateReaderMacro
 *
 * A macro that simplifies the syntaxe for getting Readers inside algorthms.
 * a scoped pointer is created with the names specified in parameter so as to be sure that
 * the Readerr will be correctly deallocated at the end of the scope. 
 * @param ReaderType The type of the requested Reader (downcasted).
 * @param ptrName The name of the socped pointer's variable name (used as a classic pointer).
 * @param index The index of the port from which we need to retrieve the Reader.
 */
#define AllocateReaderMacro(ReaderType, ptrName, index)  boost::scoped_ptr< ReaderType > ptrName( newReaderFromInput< ReaderType >(index) );

/**
 * @def AllocateWriterMacro
 *
 * A macro that simplifies the syntaxe for getting  Writers inside algorthms.
 * a scoped pointer is created with the names specified in parameter so as to be sure that
 * the Writer will be correctly deallocated at the end of the scope.
 * @param WriterType The type of the requested Writer (downcasted).
 * @param ptrName The name of the socped pointer's variable name (used as a classic pointer).
 * @param index The index of the port from which we need to retrieve the Writer.
 */ 
#define AllocateWriterMacro(WriterType, ptrName, index)  boost::scoped_ptr< WriterType > ptrName( newWriterFromInput< WriterType >(index) ); 



}//namespace core

}//namespace kiwi

#include "Resource.ih"

#endif
