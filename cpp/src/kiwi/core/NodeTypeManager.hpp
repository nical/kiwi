
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


struct InputPortDescriptor
{
    InputPortDescriptor(string portName
        , const DataTypeInfo* type, DataAccessFlags flags )
    : name(portName), dataType(type), accessFlags(flags) 
    {
    }
    
    string name;
    const DataTypeInfo* dataType;
    DataAccessFlags accessFlags;
};

struct OutputPortDescriptor
{
    OutputPortDescriptor( string portName
        , const DataTypeInfo* type, DataAccessFlags flags )
    : name(portName), dataType(type), accessFlags(flags) 
    {
    }
    
    string name;
    const DataTypeInfo* dataType;
    DataAccessFlags accessFlags;
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
    static Node* Create(string name);
};




}//namespace
}//namespace

#endif
