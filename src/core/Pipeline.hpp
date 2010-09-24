#pragma once

#ifndef KIWI_PIPELINE_HPP
#define KIWI_PIPELINE_HPP

#include "core/Resource.hpp"
#include "core/Filter.hpp"
#include "core/Commons.hpp"

#include <list>

namespace kiwi
{
namespace core
{

/**
 * @class Pipeline
 * @brief A meta-Filter class
 * 
 */ 	
class Pipeline : public Filter
{
public:
	Pipeline();

	bool contains(Resource* resource);
	
	bool add(Resource* toAdd);

	void update();
	
	void printErrors();

	/**
	 * Process the Filters contained in the pipeline.
	 * Should be used only when updateOk() returns true.
	 */ 
	void process();
	
	/**
	 * Returns false if something went wrong during the last update.
	 */ 
	bool updateOk();
	
	inline bool isReady() {return _ready;}
	
	//TODO
	bool isCompatible(portIndex_t inputIndex, const OutputPort<Reader>& port) const 
	{
		return false;
	}
	
	bool isCompatible(portIndex_t inputIndex, const OutputPort<Writer>& port) const
	{
		return false;
	}

	Resource::OutputPort<Reader>& internalReaderInputPort(portIndex_t index);
	Resource::InputPort<Reader>& internalReaderOutputPort(portIndex_t index);
	Resource::OutputPort<Writer>& internalWriterInputPort(portIndex_t index);
	Resource::InputPort<Writer>& internalWriterOutputPort(portIndex_t index);

protected:
	
	unsigned int index(unsigned int x, unsigned int y);
	int findFilter(Resource* filter);
	typedef std::pair< unsigned int, unsigned int> constraints;
	
private:
	std::vector<Filter*> _filters;
	std::vector<char> _status;
	std::list<Resource*> _resourceList;
	
	std::list<constraints> _constraints;
	
	char* _lookupTable;
	unsigned int _lastSize;
	bool _updateStatus;
	bool _ready;

	std::vector<InputPort<Reader>* > _internalReaderOutputs;
	std::vector<InputPort<Writer>* > _internalWriterOutputs; 
	std::vector<OutputPort<Reader>* > _internalReaderInputs;
	std::vector<OutputPort<Writer>* > _internalWriterInputs;
	
	void updateTableRec(unsigned index1, unsigned index2);


}//namespace core
}//namespace kiwi

#include "Pipeline.ih"


#endif
