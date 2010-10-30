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
