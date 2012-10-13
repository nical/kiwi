
#ifndef KIWI_CORE_TYPESYSTEM_HPP
#define KIWI_CORE_TYPESYSTEM_HPP

#include <string>
#include <vector>
#include <stdint.h>
#include <assert.h>

#include "kiwi/core/ID.hpp"

namespace kiwi {

class Node;
class NodeTypeInfo;
class NodeLayoutInfo;


struct DataType
{
    enum { LIST = 1, REF = 2 };

    DataType(uint32_t idx = 0, uint32_t f = 0)
    : typeIndex(idx), flags(f) {}
 
    uint32_t typeIndex;
    uint32_t flags;

    bool isCompatible(DataType rhs) const {
        return typeIndex == rhs.typeIndex;
    }
    bool isList() const {
        return flags & LIST;
    }
    bool isRef() const {
        return flags & REF;
    }
};

struct PortInfo
{
    std::string name;
    DataType    dataType;
    //uint32_t    flags;

    bool isCompatible(const PortInfo& rhs) const {
        return dataType.isCompatible(rhs.dataType);
    }
};

struct NodeLayoutInfo
{
public:
    typedef std::vector<PortInfo> PortInfoArray;

    std::string   name;
    PortInfoArray inputs;
    PortInfoArray outputs;
};

struct NodeTypeInfo
{
public:
    NodeTypeInfo() : layoutID(0), engineID(0), optID(0) {}
    NodeTypeInfo(const std::string& aName, NodeLayoutID aLayout,
                   int32_t aEngine, int32_t aOptID)
    {
        name     = aName;
        layoutID = aLayout;
        engineID = aEngine;
        optID    = aOptID;
    }

    std::string  name;
    NodeLayoutID layoutID;
    int32_t      engineID;
    int32_t      optID;
};

class TypeSystem
{
public:
    NodeLayoutID registerNodeLayout(NodeLayoutInfo& layout);
    NodeTypeID registerNodeType(const std::string& name, NodeLayoutID layout,
                                int32_t engineID, int32_t optID = 0);

    const NodeTypeInfo* getNodeType(NodeTypeID aID) const;
    const NodeLayoutInfo* getNodeLayout(NodeLayoutID aID) const;
    const NodeLayoutInfo* getNodeLayout(NodeTypeID aID) const;

    bool nodeLayoutExists(NodeLayoutID aID) const
    {
        return getNodeLayout(aID) != nullptr;
    }

    bool nodeTypeExists(NodeTypeID aID) const
    {
        return getNodeType(aID) != nullptr;
    }

    uint32_t getNodeTypesCount() const
    {
        return static_cast<uint32_t>(_nodes.size());
    }

    bool exists(NodeTypeID aID) const;
    bool exists(NodeLayoutID aID) const;

private:
    std::vector<NodeTypeInfo> _nodes;
    std::vector<NodeLayoutInfo> _layouts;
};

template<typename T> 
class NodeTypeAttributeArray
{
    NodeTypeAttributeArray(uint32_t prealloc)
    {
        if (prealloc > 0) _array.reserve(prealloc);
    }
private:
    T& operator[](NodeTypeID aID) {
        if (aID.value >= _array.size()) {
            _array.resize(aID.value);
        }
        return _array[aID.value];
    }

    std::vector<T> _array;
};

} //namespace

#endif
