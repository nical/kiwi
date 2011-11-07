
#pragma once
#ifndef KIWI_CORE_DYNAMICNODEUPDATER_HPP
#define KIWI_CORE_DYNAMICNODEUPDATER_HPP

#include "kiwi/core/NodeUpdater.hpp"
#include <vector>

namespace kiwi{
namespace core{

class Data;

/**
 * Node updater that accepts functions of the type 'bool myFunction(const DataArray& inputs, const DataArray& outputs)'.
 */ 
class DynamicNodeUpdater : public NodeUpdater
{
public:
    typedef std::vector<Data*> DataArray; 
    typedef bool (*FunctionPointer)( const DataArray& inputs, const DataArray& outputs );

    DynamicNodeUpdater( FunctionPointer fptr )
    : _fptr(fptr) { }
    
    bool update(const Node& n);

private:
    FunctionPointer _fptr;
};



}//namespace
}//namespace

#endif
