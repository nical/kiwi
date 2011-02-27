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

#ifndef KIWI_CORE_FACTORY_HPP
#define KIWI_CORE_FACTORY_HPP


#include <map>
#include <list>
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Tags.hpp"


namespace kiwi{
namespace core{ class Node; }
namespace utils{


template<typename T>
class FactoryDescriptor
{
public:
	typedef T*(*instantiationFunction)(void) ;
	
	FactoryDescriptor() : _tags("#invalid"), _creator(0){ }
	FactoryDescriptor( instantiationFunction fPtr, const kiwi::string& tags = "" )
	: _tags(tags), _creator(fPtr){ }
	
	kiwi::string tags() const { return _tags; }
	instantiationFunction creator() {return _creator;}
	
private:
	kiwi::string _tags;
	instantiationFunction _creator;
};



/**
 * @brief A factory of kiwi::core::Node instances. 
 */
template<class ObjType, class HashKey = kiwi::string>
class Factory
{	private:
public:

	/**
	 * @brief Instanciates an object and returns the pointer.
	 *
	 * Returns a nil pointer if the key does not exist in the factory.
	 */ 
	ObjType* newObject(const HashKey& uniqueId);

	/**
	 * @brief Returns true if the key exists in the factory.
	 */ 
	int exists(const  HashKey& uniqueId);
	std::list<HashKey> searchFromTag(const  kiwi::Tags& uniqueId);

	/**
	 * @brief Adds a key to the factory.
	 *
	 * This step is necessary for each class that needs to be added to the factory. 
	 */ 
	void registerClass(const  HashKey& uniqueId, FactoryDescriptor<ObjType>);

	/**
	 * @brief Removes a key from the factory.
	 */ 
	bool unregisterClass(const  HashKey& uniqueId);

	/**
	 * @brief Returns the list of the available classes.
	 */ 
	std::list< std::pair<HashKey, FactoryDescriptor<ObjType> > > availableClasses();

private:
	typedef std::map<HashKey, FactoryDescriptor<ObjType> > ObjectMap;
	ObjectMap _objects;
};




// -------------------------------------------- Implementation



template<class ObjType, class HashKey>
ObjType* Factory<ObjType,HashKey>::newObject(const  HashKey& uniqueId)
{
	typename ObjectMap::iterator it = _objects.find(uniqueId);
	if(it == _objects.end() ) return 0;
	return (it->second.creator())();
}

template<class ObjType, class HashKey>
int Factory<ObjType,HashKey>::exists(const  HashKey& uniqueId)
{
	if(_objects.find(uniqueId) != _objects.end() ) return 1;
	return 0;
}
	
template<class ObjType, class HashKey>
void Factory<ObjType,HashKey>::registerClass( const HashKey& uniqueId
	, FactoryDescriptor<ObjType> desc)
{
	_objects[uniqueId] = desc;
}

template<class ObjType, class HashKey>
bool Factory<ObjType,HashKey>::unregisterClass(const  HashKey& uniqueId)
{
	_objects.erase(_objects.find(uniqueId) );
	return true; // TODO;
}
/*
template<class ObjType, class HashKey>
std::list<kiwi::string> Factory<ObjType,HashKey>::availableClasses( const kiwi::string& tags )
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
	NodeMap::iterator it = _nodes.begin();
	NodeMap::iterator end = _nodes.end();
	for( ; it != end; ++it)
		result.push_front( it->first );
	return result;
}
*/


typedef Factory<kiwi::core::Node,kiwi::string> NodeFactory;
typedef FactoryDescriptor<kiwi::core::Node> NodeFactoryDescriptor;


}//namespace
}//namespace

#endif
