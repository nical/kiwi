#pragma once
#ifndef KIWI_CORE_NODE_HPP
#define KIWI_CORE_NODE_HPP

#include <vector>

#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/extern/log/DebugStream.hpp"
#include "kiwi/core/Data.hpp"

namespace kiwi{
namespace core{

class InputPort;
class OutputPort;
class NodeUpdater;

struct NodeInitializer
{
    struct PortInitializer
    {
        PortInitializer(string _name, int _flags, const DataTypeInfo* _type)
        {
            name = _name;
            flags = _flags;
            type = _type;
        }
        string name;
        int flags;
        const DataTypeInfo* type;
    };

    typedef std::vector<PortInitializer> PortInitArray;
    
    NodeInitializer(string nodeName)
    {
        name = nodeName;
        update = 0;
    }

    void addPort(string name, int flags, const DataTypeInfo* type)
    {
        ports.push_back( PortInitializer(name, flags,type) );
    }

    void addUpdate(NodeUpdater* updater)
    {
        update = updater;
    }
    
    string name;
    PortInitArray ports;
    NodeUpdater* update;
};

class Node
{
friend class kiwi::core::Pipeline;    
public:
    typedef std::vector<InputPort*> InputArray;
    typedef std::vector<OutputPort*> OutputArray;
    typedef int ID;

    /**
     * Constructor.
     */ 
    Node(Pipeline* pipeline, NodeInitializer& init);

    const InputArray& inputs() const
    {
        return _inputs;
    }
    const OutputArray& outputs() const
    {
        return _outputs;
    }

    InputPort& input(uint32 i = 0)
    {
        return *_inputs[i];
    }

    const InputPort& input(uint32 i = 0) const
    {
        return *_inputs[i];
    }

    OutputPort& output(uint32 i = 0)
    {
        return *_outputs[i];
    }

    const OutputPort& output(uint32 i = 0) const
    {
        return *_outputs[i];
    }

    Pipeline* pipeline() const
    {
        return _pipeline;
    }

    void update();

private:
    static ID _newId()
    {
        static ID nextId = 0;
        return ++nextId;
    }
protected:
    Pipeline* _pipeline;
private:
    InputArray _inputs;
    OutputArray _outputs;
    NodeUpdater* _updater;
    ID _id;
};



} //namespace
} //namespace


#endif
