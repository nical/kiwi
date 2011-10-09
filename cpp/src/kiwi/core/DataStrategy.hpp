#pragma once
#ifndef KIWI_CORE_DATASTRATEGY_HPP
#define KIWI_CORE_DATASTRATEGY_HPP

namespace kiwi{
namespace core{

class DataTypeInfo;
class Data;


class DataStrategy
{
public:
    virtual const DataTypeInfo* dataType() = 0;
    virtual Data* data() = 0;
    virtual ~DataStrategy(){}
};


} //namespace
} //namespace


#endif
