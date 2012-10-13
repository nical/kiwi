#include "kiwi/core/Node.hpp"
#include "kiwi/core/NodeGroup.hpp"
#include "kiwi/core/TypeSystem.hpp"
#include "kiwi/core/test.hpp"

namespace kiwi {

Node::Node(NodeGroup* ng, NodeID aID, NodeTypeID aTypeID)
{
    _flags = STANDARD;
    _parent = ng;
    _typeID = aTypeID;
    _id = aID;
}

const NodeTypeInfo& Node::typeInfo() const
{
    return *_parent->getTypeSystem().getNodeType(_typeID);
}

const NodeLayoutInfo& Node::layoutInfo() const
{
    return *_parent->getTypeSystem().getNodeLayout(typeInfo().layoutID);
}

PortIndex Node::inputCount() const
{
    return layoutInfo().inputs.size();
}

PortIndex Node::outputCount() const
{
    return layoutInfo().outputs.size();
}


void Node::nextNodes(std::list<const Node*>& outNext) const
{
    auto it1 = _outputs.begin();
    auto stop1 = _outputs.end();
    for (; it1 != stop1; ++it1) {
        bool found = false;
        auto it2 = outNext.begin();
        auto stop2 = outNext.end();
        for (; it2 != stop2; ++it2) {
            if ((*it1)->inputNode() == *it2) {
                found = true;
                break;
            }
        }
        if (!found) {
            outNext.push_back((*it1)->inputNode());
            assert((*it1)->inputNode()!=this);
        }
    }
}

void Node::previousNodes(std::list<const Node*>& outPrevious) const
{
    auto it1 = _inputs.begin();
    auto stop1 = _inputs.end();
    for (; it1 != stop1; ++it1) {
        bool found = false;
        auto it2 = outPrevious.begin();
        auto stop2 = outPrevious.end();
        for (; it2 != stop2; ++it2) {
            if ((*it1)->outputNode() == *it2) {
                found = true;
                break;
            }
        }
        if (!found) {
            outPrevious.push_back((*it1)->outputNode());
            assert((*it1)->outputNode()!=this);
        }
    }
}


NodeID NodeGroup::findNode(Node* n) const
{
    if (_nodes.size() == 0) return -1;
    int32_t i = 0;
    for(auto it = begin(); it != end(); ++it, ++i) {
        if (&(*it) == n) {
            return i; 
        }
    }
    return -1;
}


PortIndex Node::inputPortConnectionCount(PortIndex index) const
{
    unsigned int count = 0;
    auto stop = _inputs.end();
    for (auto it = _inputs.begin(); it != stop; ++it) {
        if ((**it).inputIndex() == index) ++count;
    }
    return count;
}

PortIndex Node::outputPortConnectionCount(PortIndex index) const
{
    unsigned int count = 0;
    auto stop = _outputs.end();
    for (auto it = _outputs.begin(); it != stop; ++it) {
        if ((**it).outputIndex() == index) ++count;
    }
    return count;
}

PortIndex OutputPort::connectionCount() const {
    return _node->outputPortConnectionCount(_index);
}


const PortInfo& OutputPort::info() const
{
    return _node->layoutInfo().outputs[_index];
}

bool OutputPort::isCompatible(const InputPort& rhs) const
{
    return info().isCompatible(rhs.info());
}

bool OutputPort::canConnect(const InputPort& rhs) const
{
    if (!isCompatible(rhs)) return false;
    if (rhs.isConnected() && !rhs.info().dataType.isList()) return false;
    if (&_node->parent() != &rhs._node->parent()) return false;
    return true;
}

bool OutputPort::connect(const InputPort& input) const
{
    if (!canConnect(input)) return false;

    return _node->parent().connect(_node, _index, input._node, input._index);
}

Link* OutputPort::linkTo(const InputPort& input) const
{
    auto stop = _node->_outputs.end();
    for (auto it = _node->_outputs.begin(); it != stop; ++it) {
        if ((**it).outputIndex()==_index && (**it).inputIndex()==input.index()) {
            return *it;
        }
    }

}

bool OutputPort::exists() const
{
    return _node->outputCount() > _index;
}


PortIndex InputPort::connectionCount() const
{
    return _node->inputPortConnectionCount(_index);
}

const PortInfo& InputPort::info() const
{
    return _node->layoutInfo().inputs[_index];
}

Link* InputPort::linkTo(const OutputPort& output) const
{
    auto stop = _node->_inputs.end();
    for (auto it = _node->_inputs.begin(); it != stop; ++it) {
        if ((**it).inputIndex()==_index && (**it).outputIndex()==output.index()) {
            return *it;
        }
    }
}

bool InputPort::exists() const
{
    return _node->inputCount() > _index;
}


bool isOutputNode(const Node& n)
{
    for (PortIndex i = 0; i < n.outputCount(); ++i) {
        const Node* on = n.nextNode(i);
        if (on && !(on->flags() & Node::NODEGROUP)) return false;
    }
    return true;
}

} //namespace


// ----------------------------------------------------------------------------


#ifdef KIWI_TEST
#include "assert.h"
#include "stdio.h"
using namespace kiwi;

void kiwi_unittest_Node()
{
    printf("-- kiwi::core::Node unittest\n");
    DataType T1(1);
    DataType T2(2);

    NodeLayoutInfo layout1;
    layout1.inputs = {
        {"A", T1},
        {"B", T1}
    };
    layout1.outputs = {
        {"Result", T1},
        {"Foo", T1}
    };

    NodeLayoutInfo layout2;
    layout2.inputs = {
        {"A", T1},
        {"B", T2},
        {"C", T1}
    };
    layout2.outputs = {
        {"Result", T1}
    };

    TypeSystem ts;
    NodeLayoutID l1 = ts.registerNodeLayout(layout1);
    NodeLayoutID l2 = ts.registerNodeLayout(layout2);
    NodeTypeID nt1 = ts.registerNodeType("NodeType1", l1, 0);
    NodeTypeID nt2 = ts.registerNodeType("NodeType2", l2, 0);

    NodeGroup ng(&ts);

    auto n1a = ng.newNode(nt1);
    auto n1b = ng.newNode(nt1);
    auto n1c = ng.newNode(nt1);
    auto n2a = ng.newNode(nt2);

    assert(n1a.value >= 0);
    assert(n1b.value >= 0);
    assert(n1c.value >= 0);
    assert(n2a.value >= 0);

    Node& node1a = ng.getNode(n1a);
    Node& node1b = ng.getNode(n1b);
    Node& node1c = ng.getNode(n1c);
    Node& node2a = ng.getNode(n2a);

    assert(node1a.outputPort(0).canConnect(node2a.inputPort(0)));
    assert(node1a.outputPort(1).canConnect(node2a.inputPort(2)));
    assert(!node1a.outputPort(0).canConnect(node2a.inputPort(1)));

    assert(!node1a.outputPort(1).connect(node2a.inputPort(1)));
    assert(node1a.outputPort(0).connect(node2a.inputPort(0)));
    assert(node1a.outputPort(1).connect(node2a.inputPort(2)));

    // check connectivity
    assert(node1a.outputPort(0).isConnected());
    assert(node1a.outputPort(1).isConnected());
    assert(node1a.outputPort(0).isConnectedTo(node2a.inputPort(0)));
    assert(node1a.outputPort(1).isConnectedTo(node2a.inputPort(2)));
    assert(node1a.outputPort(0).linkTo(node2a.inputPort(0)) != nullptr);
    assert(node1a.outputPort(1).linkTo(node2a.inputPort(2)) != nullptr);
    // same thing the other way around
    assert(node2a.inputPort(0).isConnected());
    assert(node2a.inputPort(2).isConnected());
    assert(node2a.inputPort(0).isConnectedTo(node1a.outputPort(0)));
    assert(node2a.inputPort(0).linkTo(node1a.outputPort(0)) != nullptr);
    assert(node2a.inputPort(2).isConnectedTo(node1a.outputPort(1)));
    assert(node2a.inputPort(2).linkTo(node1a.outputPort(1)) != nullptr);

    assert(node1b.outputPort(0).isCompatible(node2a.inputPort(0)));
    assert(!node1b.outputPort(0).canConnect(node2a.inputPort(0)));

    std::list<const Node*> prev2a;
    node2a.previousNodes(prev2a);
    assert(prev2a.size() == 1);

    std::list<const Node*> next1a;
    node1a.nextNodes(next1a);
    assert(next1a.size() == 1);

    printf("-- success\n\n");
}
#endif
