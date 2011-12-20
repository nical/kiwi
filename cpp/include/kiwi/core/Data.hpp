#pragma once
#ifndef KIWI_CORE_DATA_HPP
#define KIWI_CORE_DATA_HPP


#include "kiwi/core/Commons.hpp"
#include <vector>

namespace kiwi{
namespace core{

class Data;

/**
 * Runtime type information class for data.
 */ 
class DataTypeInfo
{
public:
	typedef std::vector<DataTypeInfo*> SubDataArray;
	typedef Data* (*Instanciator)();

	DataTypeInfo(string dataName, SubDataArray subdata, Instanciator instanciator)
	: _name(dataName), _subData(subdata), _newFunction(instanciator)
	{

	}

	string name() const
	{
		return _name;
	}
	const SubDataArray& subData() const
	{
		return _subData;
	}

	bool isComposite()
	{
		return _subData.size() != 0;
	}

	Data* newInstance() const
	{
		return (*_newFunction)();
	}

private:
	string _name;
	SubDataArray _subData;
	Instanciator _newFunction;
};

template<typename T> class Container;


/**
 * Mother class of Data objects.
 */ 
class Data
{
public:

    /**
     * Returns a pointer to the data's type info.
     */ 
	virtual const DataTypeInfo* type() const = 0;

    /**
     * Returns the value of the data held by this object.
     */
    template<typename T> T* value();
    template<typename T> const T* value() const;
    
    virtual ~Data(){};
};


}//namespace
}//namespace

// need to include Container.hpp because downCast must be defined after Container
#include "kiwi/core/Container.hpp"


#endif
