
#include "kiwi/core/NodeGroup.hpp"

namespace kiwi {

NodeID NodeGroup::newNode(NodeTypeID typeID)
{
    NodeID id = _nodes.size();
    _nodes.push_back(new Node(this, id, typeID));
    return id;
}

bool NodeGroup::connect(Node* outNode, PortIndex outIdx,
                        Node* inNode, PortIndex inIdx)
{
    if (!outNode->outputPort(outIdx).canConnect(inNode->inputPort(inIdx))) {
        return false;
    }

    Link* l = new Link(outNode, outIdx, inNode, inIdx);
    outNode->_outputs.push_back(l);
    inNode->_inputs.push_back(l);

    assert(inNode == l->inputNode());
    assert(outNode == l->outputNode());

    return true;
}

bool NodeGroup::disconnect(Node* outNode, PortIndex outIdx,
                           Node* inNode, PortIndex inIdx)
{
    if (!outNode->outputPort(outIdx).isConnectedTo(inNode->inputPort(inIdx))) {
        return false;
    }

    Link* l1 = nullptr;
    auto it = outNode->_outputs.begin();
    auto stop = outNode->_outputs.end();
    for (; it != stop; ++it) {
        l1 = (*it);
        if (l1->outputIndex() == outIdx 
         && l1->inputNode() == inNode 
         && l1->inputIndex()==inIdx) {
            outNode->_outputs.erase(it);
            break;
        }
    }

    Link* l2 = nullptr;
    it = inNode->_inputs.begin();
    stop = inNode->_inputs.end();
    for (; it != stop; ++it) {
        l2 = (*it);
        if (l2->inputIndex() == inIdx 
         && l2->outputNode() == outNode 
         && l2->outputIndex()==outIdx) {
            inNode->_inputs.erase(it);
            break;
        }
    }

    assert(l1==l2);

    delete l1;

    return true;
}

void NodeGroup::forEach(ConstFunctor f) const
{
    const_iterator it = begin();
    const_iterator stop = end();
    for (; it!=stop; ++it) {
        if (!f(*it)) {
            return;
        }
    }
}

void NodeGroup::forEach(ConstFunctorUsrData f, void* usrData) const
{
    const_iterator it = begin();
    const_iterator stop = end();
    for (; it!=stop; ++it) {
        if (!f(*it, usrData)) {
            return;
        }
    }
}

void NodeGroup::forEach(Functor f)
{
    iterator it = begin();
    iterator stop = end();
    for (; it!=stop; ++it) {
        if (!f(*it)) {
            return;
        }
    }
}

void NodeGroup::forEach(FunctorUsrData f, void* usrData)
{
    iterator it = begin();
    iterator stop = end();
    for (; it!=stop; ++it) {
        if (!f(*it, usrData)) {
            return;
        }
    }
}

const Node* NodeGroup::find(ConstFunctor f) const
{
    const_iterator it = begin();
    const_iterator stop = end();
    for (; it!=stop; ++it) {
        if (f(*it)) {
            return &(*it);
        }
    }
    return nullptr;
}

Node* NodeGroup::find(ConstFunctor f)
{
    iterator it = begin();
    iterator stop = end();
    for (; it!=stop; ++it) {
        if (f(*it)) {
            return &(*it);
        }
    }
    return nullptr;
}

void NodeGroup::findAll(ConstFunctor f, std::list<const Node*>& result) const
{
    const_iterator it = begin();
    const_iterator stop = end();
    for (; it!=stop; ++it) {
        if (f(*it)) {
            result.push_back(&(*it));
        }
    }
}

void NodeGroup::findAll(ConstFunctor f, std::list<Node*>& result)
{
    iterator it = begin();
    iterator stop = end();
    for (; it!=stop; ++it) {
        if (f(*it)) {
            result.push_back(&(*it));
        }
    }
}

} //namepsace