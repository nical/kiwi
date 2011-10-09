#pragma once
#ifndef KIWI_CORE_NODE_HPP
#define KIWI_CORE_NODE_HPP

#include <vector>

#include "kiwi/core/Pipeline.hpp"

namespace kiwi{
namespace core{

class InputPort;
class OutputPort;
class NodeUpdater;

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
