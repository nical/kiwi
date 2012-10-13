#ifndef KIWI_CORE_NODEGROUP_HPP
#define KIWI_CORE_NODEGROUP_HPP

#include <stdint.h>
#include <vector>
#include <list>

#include "kiwi/core/TypeSystem.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/ID.hpp"

namespace kiwi {

class Node;
class TypeSystem;

typedef uint16_t PortIndex;

class NodeGroupIterator
{
public:
    typedef std::vector<Node*>::iterator StdIterator;
    NodeGroupIterator(StdIterator i) {
        _it = i;
    }

    NodeGroupIterator operator++() {
        return NodeGroupIterator(++_it);
    }

    NodeGroupIterator operator++(int) {
        return NodeGroupIterator(_it++);
    }

    Node& operator*() const {
        return **_it;
    }

    bool operator==(const NodeGroupIterator& rhs) {
        return _it == rhs._it;
    }
    bool operator!=(const NodeGroupIterator& rhs) {
        return _it != rhs._it;
    }
private:
    StdIterator _it;
};

class ConstNodeGroupIterator
{
public:
    typedef std::vector<Node*>::const_iterator StdIterator;
    ConstNodeGroupIterator(StdIterator i) {
        _it = i;
    }

    ConstNodeGroupIterator operator++() {
        return ConstNodeGroupIterator(++_it);
    }

    ConstNodeGroupIterator operator++(int) {
        return ConstNodeGroupIterator(_it++);
    }

    const Node& operator*() const {
        return **_it;
    }

    bool operator==(const ConstNodeGroupIterator& rhs) {
        return _it == rhs._it;
    }
    bool operator!=(const ConstNodeGroupIterator& rhs) {
        return _it != rhs._it;
    }
private:
    StdIterator _it;
};

class NodeGroup
{
public:
    typedef std::vector<Node*> NodeArray;
    typedef NodeGroupIterator iterator;
    typedef ConstNodeGroupIterator const_iterator;

    NodeGroup(TypeSystem* ts) : _typeSystem(ts) 
    {
        _internalNode.initAsNodeGroup(this);
    }

    TypeSystem& getTypeSystem() { return *_typeSystem; }
    const TypeSystem& getTypeSystem() const { return *_typeSystem; }

    Node& getNode(NodeID nID) { return *_nodes[nID.value]; }
    NodeID newNode(NodeTypeID typeID);
    bool deleteNode(NodeID);
    NodeID findNode(Node* n) const;

    bool connect(Node* outNode, PortIndex outIdx,
                 Node* inNode, PortIndex inIdx);

    bool disconnect(Node* outNode, PortIndex outIdx,
                    Node* inNode, PortIndex inIdx);

    NodeGroupIterator begin() { return _nodes.begin(); }
    NodeGroupIterator end() { return _nodes.end(); }
    ConstNodeGroupIterator begin() const { return _nodes.begin(); }
    ConstNodeGroupIterator end() const { return _nodes.end(); }
    size_t size() const { return _nodes.size(); }

    typedef bool(* ConstFunctor)(const Node&);
    typedef bool(* ConstFunctorUsrData)(const Node&, void*);
    typedef bool(* Functor)(Node&);
    typedef bool(* FunctorUsrData)(Node&, void*);
    
    void forEach(ConstFunctor f) const;
    void forEach(ConstFunctorUsrData f, void* usrData) const;
    void forEach(Functor f);
    void forEach(FunctorUsrData f, void* usrData);
    
    Node* find(ConstFunctor f);
    const Node* find(ConstFunctor f) const;
    void findAll(ConstFunctor f, std::list<Node*>& result);
    void findAll(ConstFunctor f, std::list<const Node*>& result) const;

    InputPort internalInputPort(PortIndex idx) {
        return _internalNode.inputPort(idx);
    }

    OutputPort internalOutputPort(PortIndex idx) {
        return _internalNode.outputPort(idx);
    }
private:
    TypeSystem* _typeSystem;
    NodeArray _nodes;
    Node _internalNode;
};

} //namespace

#endif