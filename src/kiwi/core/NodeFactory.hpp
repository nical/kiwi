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

#ifndef KIWI_NODEFACTORY_HPP
#define KIWI_NODEFACTORY_HPP

#include "kiwi/core/Node.hpp"
#include "kiwi/core/Filter.hpp"
#include "kiwi/core/Container.hpp"
#include <map>
#include <list>



namespace kiwi{
namespace core{

/**
 * @brief 
 */ 
template<typename TValueType>
class Descriptor
{
public:
	typedef TValueType ValueType;
	typedef TValueType*(*instantiationFunction)(void) ;
	
	Descriptor(const kiwi::string& nodeName
		, instantiationFunction fPtr
		, const kiwi::string& tags = "" )
	:_name(nodeName), _tags(tags), _creator(fPtr)
	{ }
		
	
	const kiwi::string& name() const { return _name; }
	const kiwi::string& tags() const { return _tags; }
	instantiationFunction creator() {return _creator;}
	
private:
	kiwi::string _name;
	kiwi::string _tags;
	instantiationFunction _creator;
};



/**
 * @brief A factory of kiwi::core::Node instances. 
 */ 
class NodeFactory
{
public:
	enum{FALSE=0, NODE, FILTER, CONTAINER};
	
	kiwi::core::Node* newNode(const  kiwi::string& uniqueId);
	kiwi::core::Filter* newFilter(const  kiwi::string& uniqueId);
	kiwi::core::Container* newContainer(const  kiwi::string& uniqueId);
	
	int exists(const  kiwi::string& uniqueId);
	std::list<kiwi::string> searchFromTag(const  kiwi::string& uniqueId);
	
	void registerNode(const  kiwi::string& uniqueId, Descriptor<Container> nd);
	void registerNode(const  kiwi::string& uniqueId, Descriptor<Filter> nd);
	
	void unregister(const  kiwi::string& uniqueId);
	
	std::list<kiwi::string> availableFilters(const kiwi::string& tags = "#any");
	std::list<kiwi::string> availableContainers(const kiwi::string& tags = "#any");
	std::list<kiwi::string> availableNodes(const kiwi::string& tags = "#any");

private:
	typedef std::map<kiwi::string, Descriptor<Filter>* > FilterMap;
	typedef std::map<kiwi::string, Descriptor<Container>* > ContainerMap;
	FilterMap _filters;
	ContainerMap _containers;
};


}//namespace
}//namespace

#endif
