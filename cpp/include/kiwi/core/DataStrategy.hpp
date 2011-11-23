#pragma once
#ifndef KIWI_CORE_DATASTRATEGY_HPP
#define KIWI_CORE_DATASTRATEGY_HPP

namespace kiwi{
namespace core{

class DataTypeInfo;
class Data;

/**
 * Defines the way output ports should handle data.
 */ 
class DataStrategy
{
public:
    virtual const DataTypeInfo* dataType() const = 0;
    virtual Data* data() = 0;
    virtual const Data* data() const = 0;
    virtual ~DataStrategy(){}
};


class AutoDataStrategy : public DataStrategy
{
public:
    AutoDataStrategy(const DataTypeInfo* info)
    : _dataTypeInfo(info)
    {
        _data = _dataTypeInfo->newInstance();
    }
    
    virtual const DataTypeInfo* dataType() const
    {
        return _dataTypeInfo;
    }
    
    virtual Data* data()
    {
        if ( _data == 0 )
            _data = _dataTypeInfo->newInstance();
        return _data;
    }

    virtual const Data* data() const
    {
        if ( _data == 0 )
            const_cast<Data*&>(_data) = _dataTypeInfo->newInstance();
        return _data;
    }
    
private:
    const DataTypeInfo* _dataTypeInfo; 
    Data* _data; 
};


} //namespace
} //namespace


#endif
