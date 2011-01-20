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


#include "NodeFactory.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/Filter.hpp"
#include "kiwi/core/Container.hpp"



namespace kiwi{
namespace core{




kiwi::core::Node* NodeFactory::newNode(const  kiwi::string& uniqueId)
{
	// TODO
}

kiwi::core::Filter* NodeFactory::newFilter(const  kiwi::string& uniqueId)
{
	FilterMap::iterator it = _filters.find(uniqueId);
	if(it == _filters.end() ) return 0;
	Descriptor<Filter>* desc = it->second;
	return (desc->creator())();
}

kiwi::core::Container* NodeFactory::newContainer(const  kiwi::string& uniqueId)
{
	ContainerMap::iterator it = _containers.find(uniqueId);
	if(it == _containers.end() ) return 0;
	Descriptor<Container>* desc = it->second;
	return (desc->creator())();
}

int NodeFactory::exists(const  kiwi::string& uniqueId)
{
	if(_containers.find(uniqueId) != _containers.end() ) return CONTAINER;
	if( _filters.find(uniqueId) != _filters.end() ) return FILTER; 
	return FALSE;
}
	
void NodeFactory::registerNode(const kiwi::string& uniqueId, Descriptor<Container> nd)
{
	_containers[uniqueId] = new Descriptor<Container>(nd);
}

void NodeFactory::registerNode(const kiwi::string& uniqueId, Descriptor<Filter> nd)
{
	_filters[uniqueId] = new Descriptor<Filter>(nd);
}
	
void NodeFactory::unregister(const  kiwi::string& uniqueId)
{
	_containers.erase(_containers.find(uniqueId) );
	_filters.erase(_filters.find(uniqueId) );
}

std::list<kiwi::string> NodeFactory::availableFilters( const kiwi::string& tags )
{
	// prepare the tag list
	std::list<kiwi::string> tagList;
	while( tags.find("#",1) != kiwi::string::npos )
	{
		int sharp = tags.find("#",1);
		tagList.push_back( tags.substr(0, sharp) );
	}
	// look for filters
	std::list<kiwi::string> result;
	FilterMap::iterator it = _filters.begin();
	FilterMap::iterator end = _filters.end();
	for( ; it != end; ++it)
		result.push_front( it->first );
	return result;
}


}//namespace
}//namespace
