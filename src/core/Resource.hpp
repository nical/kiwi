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
class Resource;
struct PortInfo
{
	Resource* resource;
	portIndex_t index;
};
/**
 * @class Resource
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
	
	typedef OutputPort<Reader> ReaderOutputPort;
	typedef InputPort<Reader> ReaderInputPort;
	typedef OutputPort<Writer> WriterOutputPort;
	typedef InputPort<Writer> WriterInputPort;

// -------------------------------------------- constructor / Destructor
	/**
	 * @brief Constructor
	 */ 
	Resource();


	/**
	 * @brief Destructor
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

	
	// TODO
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
	 * @brief Returns the amount of Reader Inputs of this Resource.
	 */ 
	inline unsigned getReaderInputCount() const {return _readerInputs.size();}
	/**
	 * @brief Returns the amount of Reader Outputs of this Resource.
	 */
	inline unsigned getReaderOutputCount() const {return _readerOutputs.size();}
	/**
	 * @brief Returns the amount of Writer inputs of this Resource.
	 */
	inline unsigned getWriterInputCount() const {return _writerInputs.size();}
	/**
	 * @brief Returns the amount of Writer outputs of this Resource.
	 */
	inline unsigned getWriterOutputCount() const {return _readerOutputs.size();}
	
	/**
	 * @brief Returns true if the object is a Filter.
	 */ 
	virtual bool isAFilter() {return false;}
	
	/**
	 * @brief Returns true if the layout event is enabled.
	 * 
	 * The layout event being enabled means that 
	 */ 
	inline bool isLayoutEventEnabled() { return _layoutEvtEnabled; }
	
	
// --------------------------------------------------- protected methods	
protected:
	// port setup
	/**
	 * @brief Adds an input port to the Reader interface.
	 *
	 * This is to be used in the initialisation phase of a Resource/Filter.
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
	 * This is to be used in the initialisation phase of a Resource/Filter.
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
	 * This is to be used in the initialisation phase of a Resource/Filter.
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
	 * This is to be used in the initialisation phase of a Resource/Filter.
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
	 * @brief Redirect a port to the port another Resource's port.
	 * 
	 * bindPort allows a Resource to have ports that are in fact pointing 
	 * to another Resource instead of itself.
	 * Each port contains knows both the Resource that contains it and also
	 * the Resource that actuly contains the data.
	 * This distinction permits to have for instance a Resource that 
	 * contains other Resources and redirects its ports to the one of the
	 * contained Resource (for exemple Pipelines). 
	 * Another use of this method is for any Filter that writes in a 
	 * Resource to provide the output readers of the Resource in its own
	 * outputs.
	 * 
	 * @param myPort This class's port that has to be redirected to another Resource's port.
	 * @param toBind ...
	 */ 
	inline void bindPort(ReaderOutputPort& myPort, const ReaderOutputPort& toBind)
		{ myPort.bind(toBind); }
	inline void bindPort(WriterOutputPort& myPort, const WriterOutputPort& toBind)
		{ myPort.bind(toBind); }
	inline void bindPort(ReaderInputPort& myPort, const ReaderInputPort& toBind)
		{ myPort.bind(toBind); }
	inline void bindPort(WriterInputPort& myPort, const WriterInputPort& toBind)
		{ myPort.bind(toBind); }
	
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
	friend class Resource;
	public:
		InputPort(Resource* myResource, portIndex_t myPort, const string& type, const string& name);
		void connect(OutputPort<SlotType>& outputPort);
		void disconnect();
		inline portIndex_t index() const {return _subResource.index;}
		inline Resource* resource() const {return _subResource.resource;}
		inline portIndex_t metaIndex() const {return _metaResource.index;}
		inline Resource* metaResource() const {return _metaResource.resource;}
		inline string getName() {return _name;}
		inline string getType() {return _type;}
		// TODO this is a temporary solution for port compatibility
		// a more flexible version is to come with use of polymorphism to get compatibility of child classes.
		inline bool isCompatible(OutputPort<SlotType>& output)	
			{ return ( getType().find(output.getType())!= string::npos ); }
		inline bool isConnected() const { return (_connectedResource != 0); }
		inline bool isEnabled() const {return _enabled;}
		inline OutputPort<SlotType>* connectedOutput() const 
			{ return _connectedResource; }
		
	protected:
		inline void setName(const string& name){_name = name;}
		inline void setType(const string& type){_type = type;}
		void bind(const InputPort<SlotType>& port);
		inline void setEnabled(bool status) {_enabled = status;}
		
	private:
		PortInfo _metaResource;
		PortInfo _subResource;
		OutputPort<SlotType>* _connectedResource; // the Resource in input of this
		string _name;
		string _type;
		bool _enabled;
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
	friend class Resource;
	public:
	friend class InputPort<SlotType>;
		// --------------------------------------------------------------------
		typedef typename std::list< InputPort<SlotType>* > connectionList;
		
		// --------------------------------------------------------------------
		OutputPort(Resource* myResource, portIndex_t myPort, const string& type, const string& name);
		inline portIndex_t index() const {return _subResource.index;}
		inline Resource* resource() const {return _subResource.resource;}
		inline portIndex_t metaIndex() const {return _metaResource.index;}
		inline Resource* metaResource() const {return _metaResource.resource;}
		inline string getName() { return _name; }
		inline string getType() { return _type; }
		// TODO this is a temporary solution for port compatibility
		// a more flexible version is to come with use of polymorphism to get compatibility of child classes.
		inline bool isCompatible(OutputPort<SlotType>& output)	
			{ return ( getType().find(output.getType())!= string::npos 
			|| getType().find("any")!= string::npos ); }
		inline bool isConnected() const { return (_connections.size() != 0); }
		inline bool isEnabled() const { return _enabled; }
		inline connectionList connections() const { return _connections; }
		void disconnect(); //empty the connected resources list
		
	protected:
		inline void setName(const string& name){_name = name;}
		inline void setType(const string& type){_type = type;}
		void bind(const OutputPort<SlotType>& port);
		inline void setEnabled(bool status) {_enabled = status;}
		
	private:
		PortInfo _metaResource;
		PortInfo _subResource;
		connectionList _connections;
		string _name;
		string _type;
		bool _enabled;
	};



}; // class Resource;



//------------------------------------------------------- access classes
/**
 * @class Reader
 * @brief The base class to read data from Resource.
 */ 
class Reader
{
public:
	// TODO any way to force the children classes to implement the following constructor ?
	//Reader(const Resource::InputPort<Reader>& port);
	virtual ~Reader() {}
};

/**
 * @class Writer
 * @brief The base class to read and write data from Resource.
 */
class Writer
{
public:
	virtual ~Writer() {}
};



// ----------------------------------------------------------- Operators
/**
 *	@brief Operator for connections between Resource.
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





}//namespace core

}//namespace kiwi

#include "Resource.ih"

#endif
