
#pragma once

#ifndef KIWI_CORE_NODETYPEMANAGER_HPP
#define KIWI_CORE_NODETYPEMANAGER_HPP

#include "kiwi/core/Commons.hpp"
#include <vector>
#include <map>

namespace kiwi{
namespace core{

class NodeTypeManager;
class NodeTypeInfo;
class DataTypeInfo;
class Node;
class Pipeline;
class NodeUpdater;

/**
 * Describes an input port.
 *
 * Used to store informations about ports and keep them in NodeTypeInfo objects.
 * This information is then used to instanciate the nodes with the corresponding set
 * of ports.
 */ 
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

/**
 * Describes an output port.
 *
 * Used to store informations about ports and keep them in NodeTypeInfo objects.
 * This information is then used to instanciate the nodes with the corresponding set
 * of ports.
 */ 
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


/**
 * Describes the layout of a node type (its input and output ports).
 *
 * This information is then used to instanciate the nodes with the corresponding set
 * of ports.
 */ 
struct NodeLayoutDescriptor
{
    typedef std::vector<InputPortDescriptor> InputDescriptorArray;
    typedef std::vector<OutputPortDescriptor> OutputDescriptorArray;
    InputDescriptorArray inputs;
    OutputDescriptorArray outputs;
};

/**
 * Runtime type info object for nodes.
 *
 * keeps informations about a given node type and can create instances of the node.
 */ 
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


/**
 * Manager for runtime node type info objects.
 */ 
class NodeTypeManager
{
public:
    typedef std::map<string,NodeTypeInfo*> NodeTypeMap;
    typedef NodeTypeMap::iterator NodeTypeIterator;
   

    const NodeTypeInfo* typeOf(const string& name)
    {
        return _TypeOf(name);
    }

    const NodeTypeInfo* registerNodeType(
        const string& nodeName
        , const NodeLayoutDescriptor& layout
        , NodeUpdater* updater )
    {
        return _RegisterNode(nodeName, layout, updater);
    }

    /**
     * Instanciates a node corresponding to its type name.
     */
    Node* instanciate(string name, Pipeline* p = 0)
    {
        return Create(name, p);
    }


    // -------------------------------------------------------------- deprecated

    /**
     * Register a node type.
     */ 
    static const NodeTypeInfo* _RegisterNode( string nodeName
        , const NodeLayoutDescriptor& layout, NodeUpdater* updater );
    
    /**
     * Returns a pointer to the runtime node type info for a given name.
     *
     * Returns a nil pointer if the name doesn't correspond to a registered type.
     */ 
    static const NodeTypeInfo* _TypeOf(string name);

    /**
     * Instanciates a node corresponding to its type name.
     */
    static Node* Create(string name, Pipeline* p = 0);

    /**
     * Iterator.
     */ 
    static NodeTypeIterator Types_begin();
    static NodeTypeIterator Types_end();

    /**
     * Remove a node type from the manager.
     */ 
    static void Unregister(string name);

    /**
     * Remove all the node types.
     */ 
    static void UnregisterAll();

};



}//namespace
}//namespace

#endif
