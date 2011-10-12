#pragma once
#ifndef KIWI_CORE_DATA_HPP
#define KIWI_CORE_DATA_HPP


#include "kiwi/core/Commons.hpp"
#include <vector>

namespace kiwi{
namespace core{

class Data;

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

class Data
{
public:
    typedef unsigned int TypeId;
    
	virtual const DataTypeInfo* type() const = 0;
	virtual TypeId dataTypeId() const = 0;
    virtual ~Data(){};
};


}//namespace
}//namespace

#endif
