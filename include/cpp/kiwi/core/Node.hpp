
#ifndef KIWI_CORE_NODE_HPP
#define KIWI_CORE_NODE_HPP

#include <vector>
#include <list>
#include "stdint.h"
#include "assert.h"
#include "kiwi/core/TypeSystem.hpp"
#include "kiwi/core/ID.hpp"

namespace kiwi {

class Node;
class Link;
class InputPort;
class OutputPort;
class NodeTypeInfo;
class NodeGroup;
class TypeSystem;

typedef uint16_t PortIndex;

class InputPort
{
friend class OutputPort;
public:
    // TODO: :(
    InputPort(const Node* n, PortIndex i)
    : _node(const_cast<Node*>(n)), _index(i) {}

    InputPort(Node* n, PortIndex i)
    : _node(n), _index(i) {}

    const PortInfo& info() const;

    PortIndex connectionCount() const;
    bool isConnected() const {
        return exists() && connectionCount() != 0;
    }
    Link* linkTo(const OutputPort& input) const;
    bool isConnectedTo(const OutputPort& output) const {
        return exists() && linkTo(output) != nullptr;
    }
    Node* node() const { return _node; }
    PortIndex index() const { return _index; }
    bool exists() const;
private:
    Node* _node;
    PortIndex _index;
};

class OutputPort
{
public:
    typedef PortIndex Index;

    OutputPort(const Node* n, Index i)
    : _node(const_cast<Node*>(n)), _index(i) {}

    OutputPort(Node* n, Index i)
    : _node(n), _index(i) {}
    
    const PortInfo& info() const;
    uint16_t connectionCount() const;
    bool isConnected() const {
        return exists() && connectionCount() != 0;
    }
    Link* linkTo(const InputPort& input) const;
    bool isConnectedTo(const InputPort& input) const {
        return exists() && linkTo(input) != nullptr;
    }
    bool isCompatible(const InputPort& rhs) const;
    bool canConnect(const InputPort& rhs) const;

    bool connect(const InputPort& input) const;

    Node* node() const { return _node; }
    PortIndex index() const { return _index; }

    bool exists() const;
private:
    Node* _node;
    Index _index;
};

class Link
{
public:
    Link(Node* aOutNode, PortIndex aOutIndex,
        Node* aInNode, PortIndex aInIndex)
    : _outputNode(aOutNode), _inputNode(aInNode),
      _outputPort(aOutIndex), _inputPort(aInIndex)
    {
        assert(_inputNode);
        assert(_outputNode);
    }

    Node* outputNode() const {
        return _outputNode;
    }

    Node* inputNode() const {
        return _inputNode;
    }

    PortIndex outputIndex() const {
        return _outputPort;
    }

    PortIndex inputIndex() const {
        return _inputPort;
    }

    InputPort inputPort() const {
        return InputPort(_inputNode, _inputPort);
    }

    OutputPort outputPort() const {
        return OutputPort(_outputNode, _outputPort);
    }

private:
    Node* _outputNode;
    Node* _inputNode;
    PortIndex _outputPort;
    PortIndex _inputPort;
};


class Node
{
public:
    enum NodeFlags { STANDARD = 0, SPECIAL = 1, NODEGROUP = 3 };
    typedef std::vector<Link*> LinkArray;
    typedef typename LinkArray::iterator InputLinkIterator; 
    typedef typename LinkArray::iterator OutputLinkIterator; 

    InputPort inputPort(PortIndex i = 0) {
        return InputPort(this,i);
    }

    OutputPort outputPort(PortIndex i = 0) {
        return OutputPort(this,i);
    }

    // TODO constness is kinda sketchy in here...
    const InputPort inputPort(PortIndex i = 0) const {
        return InputPort(this,i);
    }
    const OutputPort outputPort(PortIndex i = 0) const {
        return OutputPort(this,i);
    }

    PortIndex inputPortConnectionCount(PortIndex index) const;
    PortIndex outputPortConnectionCount(PortIndex index) const;

    Link* inputLink(PortIndex i, PortIndex j = 0) {
        auto it = _inputs.begin();
        auto stop = _inputs.end();
        while (it != stop) {
            if ((*it)->inputIndex() == i) {
                if (j == 0) return *it;
                --j;
            }
            ++it;
        }
        return nullptr;
    }
    Link* outputLink(PortIndex i, PortIndex j = 0) {
        auto it = _outputs.begin();
        auto stop = _outputs.end();
        while (it != stop) {
            if ((*it)->outputIndex() == i) {
                if (j == 0) return *it;
                --j;
            }
            ++it;
        }
        return nullptr;
    }
    const Link* inputLink(PortIndex i, PortIndex j = 0) const {
        auto it = _inputs.begin();
        auto stop = _inputs.end();
        while (it != stop) {
            if ((*it)->inputIndex() == i) {
                if (j == 0) return *it;
                --j;
            }
            ++it;
        }
        return nullptr;
    }
    const Link* outputLink(PortIndex i, PortIndex j = 0) const {
        auto it = _outputs.begin();
        auto stop = _outputs.end();
        while (it != stop) {
            if ((*it)->outputIndex() == i) {
                if (j == 0) return *it;
                --j;
            }
            ++it;
        }
        return nullptr;
    }

    InputLinkIterator inputLinksBegin() {
        return _inputs.begin();
    }
    InputLinkIterator inputLinksEnd() {
        return _inputs.end();
    }


    Node* previousNode(PortIndex i, PortIndex j = 0) {
        return inputLink(i,j)->outputNode();
    }
    Node* nextNode(PortIndex i, PortIndex j = 0) {
        return outputLink(i,j)->outputNode();
    }
    const Node* previousNode(PortIndex i, PortIndex j = 0) const {
        return inputLink(i,j)->outputNode();
    }
    const Node* nextNode(PortIndex i, PortIndex j = 0) const {
        return outputLink(i,j)->outputNode();
    }

    PortIndex inputCount() const;
    PortIndex outputCount() const;

    NodeFlags flags() const {
        return _flags;
    }
    NodeID id() const { return _id; }
    const NodeTypeInfo& typeInfo() const;
    const NodeLayoutInfo& layoutInfo() const;
    NodeGroup& parent() { return *_parent; }
    const NodeGroup& parent() const { return *_parent; }

    void previousNodes(std::list<const Node*>& outPrevious) const;
    void nextNodes(std::list<const Node*>& outNext) const;
protected:
    Node(NodeGroup* ng, NodeID aID, NodeTypeID type);
    Node() : _parent(nullptr), _typeID(-1), _flags(SPECIAL) {}
    
    void initAsNodeGroup(NodeGroup* ng)
    {
        _flags = NODEGROUP;
        _parent = ng;
    }

    std::vector<Link*> _inputs;
    std::vector<Link*> _outputs;
    NodeGroup* _parent;
    NodeTypeID _typeID;
    NodeFlags  _flags;
    NodeID     _id;

    friend class kiwi::TypeSystem;
    friend class kiwi::NodeGroup;
    friend class kiwi::InputPort;
    friend class kiwi::OutputPort;
};


bool isInputNode(const Node& n);
bool isOutputNode(const Node& n);

} //namespace

#endif