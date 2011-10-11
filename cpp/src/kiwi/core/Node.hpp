#pragma once
#ifndef KIWI_CORE_NODE_HPP
#define KIWI_CORE_NODE_HPP

#include <vector>

#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Commons.hpp"
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
    enum{ IN, OUT, READ, WRITE, SIGNAL };
    
    NodeInitializer(string nodeName)
    {
        name = nodeName;
    }

    void addPort(string name, int flags, const DataTypeInfo* type)
    {
        ports.push_back( PortInitializer(name, flags,type) );
    }
    
    string name;
    PortInitArray ports;
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
    Node(Pipeline* pipeline, const InputArray& inputports, const OutputArray& outputports, NodeUpdater* updater)
    : _pipeline(pipeline), _inputs(inputports), _outputs(outputports), _updater(updater)
    {
        if(pipeline) pipeline->addNode(this);
        _id = _newId();
    }

    InputPort& input(int index = 0) const
    {
        return *_inputs[index];
    }
    OutputPort& output(int index = 0) const
    {
        return *_outputs[index];
    }
    const InputArray& inputs() const
    {
        return _inputs;
    }
    const OutputArray& outputs() const
    {
        return _outputs;
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
