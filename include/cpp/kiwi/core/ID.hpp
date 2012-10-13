#ifndef KIWI_CORE_ID_HPP
#define KIWI_CORE_ID_HPP

#include <stdint.h>

namespace kiwi {

template<typename T, typename V> struct ID
{
    typedef ID<T,V> Self;
    ID(V val) : value(val) {}
    ID() : value(0) {}
    bool operator == (Self rhs) {
        return value == rhs.value;
    }
    bool operator < (Self rhs) const {
        return value < rhs.value;
    }
    V value;
};

template<typename T> struct pointerID
{
    T* value;
};

class Node;
class Link;
class InputPort;
class OutputPort;
class NodeTypeInfo;
class NodeLayoutInfo;

typedef ID<Node, int32_t> NodeID;
typedef ID<Link, uint32_t> LinkID;
//typedef ID<InputPort, uint16_t> InputPortID;
//typedef ID<OutputPort, uint16_t> OutputPortID;
typedef ID<NodeTypeInfo, int32_t> NodeTypeID;
typedef ID<NodeLayoutInfo, int32_t> NodeLayoutID;

} // namespace

#endif
