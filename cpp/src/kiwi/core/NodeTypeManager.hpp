
#pragma once

#ifndef KIWI_CORE_NODETYPEMANAGER_HPP
#define KIWI_CORE_NODETYPEMANAGER_HPP

#include "kiwi/core/Commons.hpp"
#include <vector>

namespace kiwi{
namespace core{

class NodeTypeManager;
class NodeTypeInfo;
class DataTypeInfo;
class Node;
class Pipeline;
class NodeUpdater;


class InputPortDescriptor
{
public:
    InputPortDescriptor(string portName
        , const DataTypeInfo* type, DataAccessFlags flags )
    : _name(portName), _dataType(type), _accessFlags(flags) 
    {
    }

    InputPortDescriptor( const InputPortDescriptor& toCopy )
    {
        _name = toCopy._name;
        _dataType = toCopy._dataType;
        _accessFlags = toCopy._accessFlags;
    }

    string name() const
    {
        return _name;
    }

    const DataTypeInfo* dataType() const
    {
        return _dataType;
    }
    
    DataAccessFlags accessFlags() const
    {
        return _accessFlags;
    }

private:
    string _name;
    const DataTypeInfo* _dataType;
    DataAccessFlags _accessFlags;
};

class OutputPortDescriptor
{
public:
    OutputPortDescriptor( string portName
        , const DataTypeInfo* type, DataAccessFlags flags )
    : _name(portName), _dataType(type), _accessFlags(flags) 
    {
    }

    OutputPortDescriptor( const OutputPortDescriptor& toCopy )
    {
        _name = toCopy._name;
        _dataType = toCopy._dataType;
        _accessFlags = toCopy._accessFlags;
    }

    string name() const
    {
        return _name;
    }

    const DataTypeInfo* dataType() const
    {
        return _dataType;
    }
    
    DataAccessFlags accessFlags() const
    {
        return _accessFlags;
    }

private:

    string _name;
    const DataTypeInfo* _dataType;
    DataAccessFlags _accessFlags;
};



struct NodeLayoutDescriptor
{
    typedef std::vector<InputPortDescriptor> InputDescriptorArray;
    typedef std::vector<OutputPortDescriptor> OutputDescriptorArray;
    InputDescriptorArray inputs;
    OutputDescriptorArray outputs;
};


class NodeTypeInfo
{
friend class NodeTypeManager;
friend class Node;
public:
    
    string name() const
    {
        return _name;
    }

    const NodeLayoutDescriptor::InputDescriptorArray& inputs() const
    {
        return _layout.inputs;
    }

    const NodeLayoutDescriptor::OutputDescriptorArray& outputs() const
    {
        return _layout.outputs;
    }

    NodeUpdater* updater() const
    {
        return _updater;
    }

    Node* newInstance(Pipeline* p = 0) const;
    
private:
    string _name;
    NodeLayoutDescriptor _layout;
    NodeUpdater* _updater;
};


class NodeTypeManager
{
public:
    static const NodeTypeInfo* RegisterNode( string nodeName
        , const NodeLayoutDescriptor& layout, NodeUpdater* updater );
    
    static void Unregister(string name);
    static void UnregisterAll();

    static const NodeTypeInfo* TypeOf(string name);
    static Node* Create(string name, Pipeline* p = 0);
};




}//namespace
}//namespace

#endif
