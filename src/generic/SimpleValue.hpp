#pragma once

#ifndef KIWI_VALUE_HPP
#define KIWI_VALUE_HPP

#include "core/Resource.hpp"
#include "core/Commons.hpp"

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
class ValueHolder
{
public:
	/**
	 * returns the value.
	 */ 
	virtual T& getValue(portIndex_t port = 0) = 0;
};


// ------------------------------------------------------------ Resource
template <typename TValueType>
class Value : public Resource, ValueHolder<TValueType>
{
public:
	typedef TValueType ValueType;

	Value(ValueType init)
	: _data(init)
	{
		addWriterOutputPort("W");
		addReaderOutputPort("R");
	}
	
	// ValueHolder implementation --------------------------------------
	virtual ValueType& getValue(portIndex_t port = 0) {return _data;}
	
	
	// Resource implementation -----------------------------------------
	// This Resource has no input port so nothing to be compatible with
	virtual bool isCompatible(portIndex_t, const OutputPort<Reader>&) const 
	{ return false; }
	virtual bool isCompatible(portIndex_t, const OutputPort<Writer>&) const 
	{ return false; }
	
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
	ValueReader(ValueHolder<TValueType>* resource, portIndex_t port)
	: _resource(resource), _port(port) { }
	
	virtual ValueType get() {return _resource->getValue(_port);}
private:
	ValueHolder<ValueType>* _resource;
	portIndex_t _port;
};

template<typename TValueType>
class ValueWriter : public Writer
{
public:
	typedef TValueType ValueType;
	// -----------------------------------------------------------------
	ValueWriter(ValueHolder<ValueType>* resource, portIndex_t port)
	: _resource(resource), _port(port) { }
	
	virtual ValueType get() {return _resource->getValue(_port);}
	virtual void set(ValueType val) {_resource->getValue(_port) = val; }
private:
	ValueHolder<ValueType>* _resource;
	portIndex_t _port;
};



}//namespace
}

#endif
