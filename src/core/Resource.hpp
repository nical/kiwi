#pragma once
#ifndef KIWI_RESOURCE_HPP
#define KIWI_RESOURCE_HPP

#include <list>
#include <vector>

#include <boost/scoped_ptr.hpp>

#include "Commons.hpp"
#include <assert.h>

namespace kiwi
{
namespace core
{


#define AllocateReaderMacro(ReaderType, ptrName, index)  boost::scoped_ptr< ReaderType > ptrName( newReaderFromInput< ReaderType >(index) ); 

#define AllocateWriterMacro(WriterType, ptrName, index)  boost::scoped_ptr< WriterType > ptrName( newWriterFromInput< WriterType >(index) ); 

	
class Resource
{
public:
//---------------------------------------  Internal classes declarations
	class Reader;
	class Writer;
	template<class SlotType> class InputPort;
	template<class SlotType> class OutputPort;
	
//------------------------------------------------------------- typedefs

	typedef unsigned char portIndex_t;


// -------------------------------------------- constructor / Destructor

	Resource();
	
	virtual ~Resource();



// ----------------------------------------------------- virtual methods

	virtual Reader* newReader(unsigned index) = 0;
	virtual Writer* newWriter(unsigned index) = 0;
	virtual bool isReaderCompatible(portIndex_t inputIndex, Reader* reader) = 0;
	virtual bool isWriterCompatible(portIndex_t inputIndex, Writer* reader) = 0;

// ------------------------------------------------------- pulic methods

	InputPort<Reader>& readerInputPort(portIndex_t index) const
		{assert(index < getReaderInputCount() ); return *_readerInputs[index];}
	OutputPort<Reader>& readerOutputPort(portIndex_t index) const
		{assert(index < getReaderOutputCount() );return *_readerOutputs[index];}

	InputPort<Writer>& writerInputPort(portIndex_t index) const
		{assert(index < getWriterInputCount() );return *_writerInputs[index];}
	OutputPort<Writer>& writerOutputPort(portIndex_t index) const
		{assert(index < getWriterOutputCount() );return *_writerOutputs[index];}

	inline unsigned getReaderInputCount() const {return _readerInputs.size();}
	inline unsigned getReaderOutputCount() const {return _readerOutputs.size();}
	inline unsigned getWriterInputCount() const {return _writerInputs.size();}
	inline unsigned getWriterOutputCount() const {return _readerOutputs.size();}
	
// --------------------------------------------------- protected methods	
protected:
	// port setup
	void addReaderInputPort(const string& name = "<");
	void removeReaderInputPort();
	void addReaderOutputPort(const string& name = ">");
	void removeReaderOutputPort();
	void addWriterInputPort(const string& name = "<");
	void removeWriterInputPort();
	void addWriterOutputPort(const string& name = ">");
	void removeWriterOutputPort();
	
	// for internal use
	template<typename ReaderType>
	ReaderType* newReaderFromInput(portIndex_t index) const;
	template<typename WriterType>
	WriterType* newWriterFromInput(portIndex_t index) const;
	

// ----------------------------------------------------- private members
private:
	/**
	 * 
	 */ 
	std::vector<InputPort<Reader>* > _readerInputs; //TODO: vector or list ?
	std::vector<InputPort<Writer>* > _writerInputs;
	std::vector<OutputPort<Reader>* > _readerOutputs;
	std::vector<OutputPort<Writer>* > _writerOutputs;

//----------------------------------------------------- Internal Classes
public:
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

//------------------------------------------------------- access classes
	class Reader
	{
	public:
		virtual ~Reader() {}
	};

	class Writer
	{
	public:
		virtual ~Writer() {}
	};

}; // class Resource;



// ----------------------------------------------------------- Operators

template <typename SlotType>
bool operator>>(Resource::OutputPort<SlotType>& output, Resource::InputPort<SlotType>& input );


}//namespace core

}//namespace kiwi

#include "Resource.ih"

#endif
