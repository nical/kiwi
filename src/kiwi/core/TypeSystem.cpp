
#include "kiwi/core/TypeSystem.hpp"
#include "kiwi/core/test.hpp"

#include "stdint.h"

namespace kiwi {

NodeLayoutID TypeSystem::registerNodeLayout(NodeLayoutInfo& layout)
{
    int32_t i = _layouts.size();
    _layouts.push_back(layout);
    return NodeLayoutID(i);
}

NodeTypeID TypeSystem::registerNodeType(const std::string& name, NodeLayoutID layout,
                                        int32_t engineID, int32_t aOptID)
{
    int32_t i = _nodes.size();
    _nodes.push_back(NodeTypeInfo(name, layout, engineID, aOptID));
    return NodeTypeID(i);
}

const NodeTypeInfo* TypeSystem::getNodeType(NodeTypeID aID) const
{
    if (!exists(aID)) return nullptr;
    return &_nodes[aID.value];
}
const NodeLayoutInfo* TypeSystem::getNodeLayout(NodeLayoutID aID) const
{
    if (!exists(aID)) return nullptr;
    return &_layouts[aID.value]; 
}
const NodeLayoutInfo* TypeSystem::getNodeLayout(NodeTypeID aID) const
{
    if (!exists(aID)) return nullptr;
    return &_layouts[getNodeType(aID)->layoutID.value]; 
}

bool TypeSystem::exists(NodeTypeID aID) const
{
    return aID.value >= 0 && aID.value < _nodes.size();
}
bool TypeSystem::exists(NodeLayoutID aID) const
{
    return aID.value >= 0 && aID.value < _layouts.size();
}

} // namespace


#ifdef KIWI_TEST
#include "assert.h"
#include "stdio.h"
using namespace kiwi;
void kiwi_unittest_TypeSystem()
{
    printf("-- kiwi::core::TypeSystem unittest\n");
    DataType T1(1);
    DataType T2(2);

    NodeLayoutInfo layout1;
    layout1.name = "Layout1";
    layout1.inputs = { 
        {"A", T1},
        {"B", T1}
    };
    layout1.outputs = {
        {"Result", T1}
    };

    NodeLayoutInfo layout2;
    layout2.name = "Layout2";
    layout2.inputs = { 
        {"A", T1},
        {"B", T2}
    };
    layout2.outputs = {
        {"Result", T1}
    };

    TypeSystem ts;

    NodeLayoutID l1 = ts.registerNodeLayout(layout1);
    assert(l1.value >= 0);
    NodeLayoutID l2 = ts.registerNodeLayout(layout2);
    assert(l2.value >= 0);

    NodeTypeID nt1 = ts.registerNodeType("NodeType1", l1, 0);
    assert(nt1.value >= 0);
    NodeTypeID nt2 = ts.registerNodeType("NodeType2", l2, 0);
    assert(nt1.value >= 0);

    const NodeLayoutInfo* reg_layout1 = ts.getNodeLayout(l1);
    assert(reg_layout1 != nullptr);
    assert(reg_layout1 == ts.getNodeLayout(nt1));
    assert(reg_layout1->name == "Layout1");

    const NodeTypeInfo* reg_type1 = ts.getNodeType(nt1);
    assert(reg_type1 != nullptr);
    assert(reg_type1->name == "NodeType1");

    const NodeLayoutInfo* reg_layout2 = ts.getNodeLayout(l2);
    assert(reg_layout2 != nullptr);
    assert(reg_layout2 == ts.getNodeLayout(nt2));
    assert(reg_layout2->name == "Layout2");

    const NodeTypeInfo* reg_type2 = ts.getNodeType(nt2);
    assert(reg_type2 != nullptr);
    assert(reg_type2->name == "NodeType2");

    printf("-- success\n\n");
}
#endif
