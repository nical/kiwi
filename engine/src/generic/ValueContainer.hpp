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

#ifndef KIWI_VALUE_HPP
#define KIWI_VALUE_HPP

#include "core/Container.hpp"
#include "core/Commons.hpp"
#include "utils/types.hpp"

namespace kiwi
{
namespace generic
{

using namespace kiwi::core;

// ----------------------------------------------------------- Interface
/**
 * @class kiwi::core::AbstractValueContainer<T>
 * Interface that must be implemented by any Container that provide 
 * a Value<T> port type
 */ 
template <typename T>
class AbstractValueContainer : public virtual Container
{
public:
	/**
	 * returns the value.
	 */ 
	virtual T& getValue(portIndex_t port = 0) = 0;
};

// ------------------------------------------------------------ Container
template <typename TValueType>
class ValueContainer : public AbstractValueContainer<TValueType>
{
public:
	typedef TValueType ValueType;

	ValueContainer(ValueType init)
	: _data(init)
	{
		// string("value_")+types::str<TValueType>()
		Node::addWriterOutputPort();
		Node::addReaderOutputPort();
	}
	
	string readerOutputName(portIndex_t){return string("read");}
	string WriterOutputName(portIndex_t){return string("write");}
	
	// AbstractValueContainer implementation --------------------------------------
	virtual ValueType& getValue(portIndex_t port = 0) {return _data;}
	
private:	
	ValueType _data;
	
};


// ----------------------------------------------------- Reader / Writer
template<typename TValueType>
class ValueReader : public Reader
{
public:
	typedef TValueType ValueType;
	// -----------------------------------------------------------------
	ValueReader(const Container::ReaderInputPort& port)
	{
		assert( port.connectedOutput()->subPort()->node() );
		
		_resource = dynamic_cast<AbstractValueContainer<TValueType>* >( 
			port.connectedOutput()->subPort()->node() 
		);
		
		if(!_resource)
		{
			Debug::error() << "ValueReader<"
				<< types::str<ValueType>() 
				<< ">::Constructor : "
				<< "enable to determine the Container type" 
				<< endl();
		}
		_port = port.connectedOutput()->subPort()->index();
	}
	
	virtual ValueType get() {return _resource->getValue(_port);}
private:
	AbstractValueContainer<ValueType>* _resource;
	portIndex_t _port;
};

template<typename TValueType>
class ValueWriter : public Writer
{
public:
	typedef TValueType ValueType;
	// -----------------------------------------------------------------
	ValueWriter(const Container::WriterInputPort& port)
	{
		_resource = dynamic_cast<AbstractValueContainer<TValueType>* >(
			port.connectedOutput()->subPort()->node() 
		);
		DEBUG_ONLY(
			if(!_resource)
			{
				Debug::error() << "ValueWriter<"
					<< types::str<ValueType>() 
					<< ">::Constructor : "
					<< "enable to determine the Container type" 
					<< endl();
			}
		)//DEBUG_ONLY
		_port = port.connectedOutput()->subPort()->index();
	}
	
	virtual ValueType get() {return _resource->getValue(_port);}
	virtual void set(ValueType val) {_resource->getValue(_port) = val; }
private:
	AbstractValueContainer<ValueType>* _resource;
	portIndex_t _port;
};



}//namespace
}

#endif
