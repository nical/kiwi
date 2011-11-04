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
class NodeTypeInfo;

/**
 * Composant of a scripting graph (or pipeline).
 *
 * Nodes are connected to one another through input and output ports.
 * To create a node its type must first be registered.
 * Use NodeTypeManager to create nodes.
 */ 
class Node
{
friend class kiwi::core::Pipeline;    
public:
    typedef std::vector<InputPort*> InputArray;
    typedef std::vector<OutputPort*> OutputArray;
    typedef uint32 ID;

    /**
     * Constructor.
     */ 
    Node(Pipeline* pipeline, const NodeTypeInfo* type);

    /**
     * Returns the input ports as a vector.
     */ 
    const InputArray& inputs() const
    {
        return _inputs;
    }
    /**
     * Returns the output ports as a vector.
     */ 
    const OutputArray& outputs() const
    {
        return _outputs;
    }

    /**
     * Returns the ith input port.
     */ 
    InputPort& input(uint32 i = 0)
    {
        return *_inputs[i];
    }

    /**
     * Returns the ith input port (const).
     */ 
    const InputPort& input(uint32 i = 0) const
    {
        return *_inputs[i];
    }

    /**
     * Returns the ith output port.
     */ 
    OutputPort& output(uint32 i = 0)
    {
        return *_outputs[i];
    }

    /**
     * Returns the ith output port (const).
     */ 
    const OutputPort& output(uint32 i = 0) const
    {
        return *_outputs[i];
    }

    /**
     * Returns a pointer to the pipeline this node belongs to.
     */ 
    Pipeline* pipeline() const
    {
        return _pipeline;
    }

    /**
     * Updates the node if its type has a NodeUpdater component.
     *
     * This is when the algorithm carried by the node (if any) is executed.
     */ 
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
    const NodeTypeInfo* _type;
    ID _id;
};



} //namespace
} //namespace


#endif
