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


#pragma once

#ifndef KIWI_VALUE_HPP
#define KIWI_VALUE_HPP

#include "core/Resource.hpp"
#include "core/Commons.hpp"
#include "utils/types.hpp"

namespace kiwi
{
namespace generic
{

using namespace kiwi::core;

// ----------------------------------------------------------- Interface
/**
 * @class kiwi::core::ValueHolder<T>
 * Interface that must be implemented by any Resource that provide 
 * a Value<T> port type
 */ 
template <typename T>
class ValueHolder : public virtual Resource
{
public:
	/**
	 * returns the value.
	 */ 
	virtual T& getValue(portIndex_t port = 0) = 0;
};

// ------------------------------------------------------------ Resource
template <typename TValueType>
class Value : public ValueHolder<TValueType>
{
public:
	typedef TValueType ValueType;

	Value(ValueType init)
	: _data(init)
	{
		addWriterOutputPort(string("value_")+types::str<TValueType>(),"W");
		addReaderOutputPort(string("value_")+types::str<TValueType>(),"R");
	}
	
	// ValueHolder implementation --------------------------------------
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
	ValueReader(const Resource::ReaderInputPort& port)
	{
		assert( port.connectedOutput()->node() );
		
		_node = dynamic_cast<ValueHolder<TValueType>* >( 
			port.connectedOutput()->node() 
		);
		
		if(!_node)
		{
			Debug::error() << "ValueReader<"
				<< types::str<ValueType>() 
				<< ">::Constructor : "
				<< "enable to determine the Resource type" 
				<< endl();
		}
		_port = port.connectedOutput()->index();
	}
	
	virtual ValueType get() {return _node->getValue(_port);}
private:
	ValueHolder<ValueType>* _node;
	portIndex_t _port;
};

template<typename TValueType>
class ValueWriter : public Writer
{
public:
	typedef TValueType ValueType;
	// -----------------------------------------------------------------
	ValueWriter(const Resource::WriterInputPort& port)
	{
		_node = dynamic_cast<ValueHolder<TValueType>* >(
			port.connectedOutput()->node() 
		);
		
		if(!_node)
		{
			Debug::error() << "ValueWriter<"
				<< types::str<ValueType>() 
				<< ">::Constructor : "
				<< "enable to determine the Resource type" 
				<< endl();
		}
		_port = port.connectedOutput()->index();
	}
	
	virtual ValueType get() {return _node->getValue(_port);}
	virtual void set(ValueType val) {_node->getValue(_port) = val; }
private:
	ValueHolder<ValueType>* _node;
	portIndex_t _port;
};



}//namespace
}

#endif
