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
    Node(Pipeline* pipeline, const NodeTypeInfo* type);

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
    const NodeTypeInfo* _type;
    ID _id;
};



} //namespace
} //namespace


#endif
