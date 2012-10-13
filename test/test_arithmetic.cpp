
#include "kiwi/core/Node.hpp"
#include "kiwi/core/NodeGroup.hpp"
#include "kiwi/core/TypeSystem.hpp"
#include "kiwi/utils/AttributeMap.hpp"

#include <map>
#include <vector>
#include <string>
#include "stdio.h"
#include "math.h"

using namespace std;
using namespace kiwi;

typedef std::map<string,NodeTypeID> NodeTypeMap;
typedef std::map<string,DataType> DataTypeMap;

static const int MATH = 1;

enum {
    ADD, SUB, MUL, DIV, SIN, COS, EXP, SQRT, INPUT, OUTPUT
};

void* UsrData(int arg) {
    return reinterpret_cast<void*>(arg);
}

NodeID input1;
NodeID input2;
NodeID input3;
NodeID output1;
NodeID output2;
NodeAttributeMap<float*> NodeAttribs;

class OpBin;
class OpUn;
class Operation
{
public:
    enum { UNARY, BINARY };
    virtual void compute() = 0;
    virtual ~Operation() {};
};

#define BINARY_OP(name, func) struct name : public Operation { name(float*x,float*y,float*r):_a(x),_b(y),_r(r){} float* _a; float *_b; float *_r; virtual void compute() {float a=*_a;float b=*_b; *_r=func;} };
#define UNARY_OP(name, func) struct name : public Operation { name(float*x,float*r):_a(x),_r(r){} float* _a;float* _r; virtual void compute() {float a=*_a; *_r=func;} };
BINARY_OP(OpAdd, a+b)
BINARY_OP(OpSub, a-b)
BINARY_OP(OpMul, a*b)
BINARY_OP(OpDiv, a/b)
UNARY_OP(OpExp, exp(a))
UNARY_OP(OpCos, cos(a))
UNARY_OP(OpSin, sin(a))

std::list<Operation*> ops;
std::vector<float> data;
std::list<const Node*> sorted;
std::list<const Node*> outputNodes;
std::list<const Node*> inputNodes;
std::vector<float*> inputData;
std::vector<float*> outputData;

bool isOutput(const Node& n) {
    return n.typeInfo().optID == OUTPUT;
}
bool isInput(const Node& n) {
    return n.typeInfo().optID == INPUT;
}

void printType(const Node& n) {
    switch (n.typeInfo().optID) {
        case ADD : printf("ADD\n"); return;
        case SUB : printf("SUB\n"); return;
        case MUL : printf("MUL\n"); return;
        case DIV : printf("DIV\n"); return;
        case OUTPUT : printf("OUTPUT\n"); return;
        case INPUT : printf("INPUT\n"); return;
        case EXP : printf("EXP\n"); return;
        case SIN : printf("SIN\n"); return;
        case COS : printf("COS\n"); return;
        default : printf("UNKNOWN\n");
    }
}

Operation* newOp(int type, float* a, float* b, float* r, NodeID id)
{
    switch (type) {
        case ADD : {
            assert(a); assert(b);
            return new OpAdd(a,b,r);
        }
        case SUB : {
            assert(a); assert(b);
            return new OpSub(a,b,r);
        }
        case MUL : {
            assert(a!=nullptr); assert(b);
            return new OpMul(a,b,r);
        }
        case DIV : {
            assert(a); assert(b);
            return new OpDiv(a,b,r);
        }
        case SIN : {
            assert(a); assert(b);
            return new OpSin(a,r);
        }
        case COS : {
            assert(a); assert(b);
            return new OpCos(a,r);
        }
        case EXP : {
            assert(a);
            return new OpExp(a,r);
        }
        case INPUT : {
            inputData.push_back(r);
            return nullptr;
        }
        case OUTPUT : {
            assert(a);
            NodeAttribs[id] = a;

            outputData.push_back(a);
            return nullptr;
        }
        default : {
            assert("unknown " == "node type");
        }
    }
}

void recTraverseNodes(const Node* n)
{
    if (n->flags() != Node::STANDARD) {
        return;
    }

    auto it = sorted.begin();
    auto stop = sorted.end();
    bool found = false;
    for (;it != stop; ++it) {
        if (*it == n) {
            found = true;
            break;
        }
    }
    if (!found) {
        std::list<const Node*> prevs;
        n->previousNodes(prevs);
        auto pi = prevs.begin();
        auto ps = prevs.end();
        for (; pi!=ps; ++pi) {
            recTraverseNodes(*pi);
        }
        sorted.push_back(n);
    }
}
void clearData() {
    outputData.clear();
    outputNodes.clear();
    inputNodes.clear();
    sorted.clear();
}

bool build(const NodeGroup& ng)
{
    clearData();    

    ng.findAll(&kiwi::isOutputNode, outputNodes);
    ng.findAll(&isInput, inputNodes);
    assert(outputNodes.size() == 2);
    assert(inputNodes.size() == 3);

    data.resize(ng.size());

    auto itr = outputNodes.begin();
    auto stopr = outputNodes.end();
    for (; itr != stopr; ++itr) {
        recTraverseNodes(*itr);
    }
    printf("sorted.size() = %i, ng.size() = %i\n",
           (int)sorted.size(),(int)ng.size());

    assert(sorted.size()==ng.size());

    data.resize(sorted.size());
    int i = 0;
    auto its = sorted.begin();
    auto stops = sorted.end();
    for (; its != stops; ++its) {
        const Node& n = **its; 
        Operation* op = nullptr;
        float* r = &data[i];
        float* a = nullptr;
        float* b = nullptr;
        if (n.inputPort(0).isConnected()) {
            a = NodeAttribs[n.previousNode(0)->id()];
            assert(a);
        } else {
        }
        if (n.inputPort(1).isConnected()) {
            b = NodeAttribs[n.previousNode(1)->id()];
            assert(b);
        } else {
        }
        NodeAttribs[n.id()] = r;
        
        op = newOp((**its).typeInfo().optID, a, b, r, n.id());

        if (op) {
            ops.push_back(op);
        }
        ++i;
    }

    return true;
}

bool run() {
    printf("run\n");
            
    *NodeAttribs[input1] = 10.0;
    *NodeAttribs[input2] = 5.0;
    *NodeAttribs[input3] = 2.0;
    
    printf("input data: %f %f %f \n", *inputData[0], *inputData[1], *inputData[2]);
    assert(*inputData[0] - 10.0 < 0.01);
    assert(*inputData[1] - 5.0 < 0.01);
    assert(*inputData[2] - 2.0 < 0.01);
    auto stop = ops.end();
    for (auto it = ops.begin(); it != stop; ++it) {
        if (*it) {
            (*it)->compute();
        }
    }
    for (int i = 0; i < outputData.size(); ++i) {
        printf("Output value %i: %f\n", i, *outputData[i]);
    }
    assert(*NodeAttribs[output1] - 15.0 < 0.01);
    assert(*NodeAttribs[output2] - 30.0 < 0.01);
    return true;
}

void registerNodes(TypeSystem& ts, NodeTypeMap& nodeTypes, DataTypeMap dataTypes)
{
    DataType& Float = dataTypes["Float"];

    NodeLayoutInfo layout1;
    layout1.inputs = {
        {"A", Float},
        {"B", Float}
    };
    layout1.outputs = {
        {"Out", Float}
    };

    NodeLayoutInfo layout2;
    layout2.inputs = {
        {"In", Float}
    };
    layout2.outputs = {
        {"Out", Float}
    };

    NodeLayoutInfo layout3;
    layout3.outputs = {
        {"Out", Float}
    };

    NodeLayoutInfo layout4;
    layout4.inputs = {
        {"In", Float}
    };

    NodeLayoutID l1 = ts.registerNodeLayout(layout1);
    NodeLayoutID l2 = ts.registerNodeLayout(layout2);
    NodeLayoutID l3 = ts.registerNodeLayout(layout3);
    NodeLayoutID l4 = ts.registerNodeLayout(layout4);
    nodeTypes["Add"] = ts.registerNodeType("Add",       l1, MATH, ADD);
    nodeTypes["Sub"] = ts.registerNodeType("Substract", l1, MATH, SUB);
    nodeTypes["Mul"] = ts.registerNodeType("Multiply",  l1, MATH, MUL);
    nodeTypes["Div"] = ts.registerNodeType("Divide",    l1, MATH, DIV);
    nodeTypes["Sin"] = ts.registerNodeType("Sin",       l2, MATH, SIN);
    nodeTypes["Cos"] = ts.registerNodeType("Cos",       l2, MATH, COS);
    nodeTypes["Exp"] = ts.registerNodeType("Exp",       l2, MATH, EXP);
    nodeTypes["Sqr"] = ts.registerNodeType("Sqrt2",     l2, MATH, SQRT);
    nodeTypes["In"]  = ts.registerNodeType("Input",     l3, MATH, INPUT);
    nodeTypes["Out"] = ts.registerNodeType("Output",    l4, MATH, OUTPUT);

}

void registerTypes(DataTypeMap& dataTypes)
{
    dataTypes["Float"] = DataType(1);
}

void instanciateNodes(NodeGroup& ng, NodeTypeMap& nodeTypes)
{
    input1 = ng.newNode(nodeTypes["In"]);
    input2 = ng.newNode(nodeTypes["In"]);
    input3 = ng.newNode(nodeTypes["In"]);
    //NodeID in4_ = ng.newNode(nodeTypes["In"]);
    NodeID output1 = ng.newNode(nodeTypes["Out"]);
    NodeID output2 = ng.newNode(nodeTypes["Out"]);
    //NodeID out3_ = ng.newNode(nodeTypes["Out"]);
    NodeID add_ = ng.newNode(nodeTypes["Add"]);
    //NodeID sub_ = ng.newNode(nodeTypes["Sub"]);
    NodeID mul_ = ng.newNode(nodeTypes["Mul"]);

    Node& in1 = ng.getNode(input1);
    Node& in2 = ng.getNode(input2);
    Node& in3 = ng.getNode(input3);
    //Node& in4 = ng.getNode(in4_);
    Node& out1 = ng.getNode(output1);
    Node& out2 = ng.getNode(output2);
    //Node& out3 = ng.getNode(out3_);
    Node& add = ng.getNode(add_);
    Node& mul = ng.getNode(mul_);

/*           _____
    [10]*--*| add |
     [5]*--*|_____|*--*[out1]
                    \     _____
                     `--*| mul |
                 [2]*---*|_____|*--*[out2]


*/
    assert(in1.outputPort().connect(add.inputPort(0)));
    assert(in2.outputPort().connect(add.inputPort(1)));
    assert(add.outputPort().connect(out1.inputPort()));
    assert(add.outputPort().connect(mul.inputPort(0)));
    assert(in3.outputPort().connect(mul.inputPort(1)));
    assert(mul.outputPort().connect(out2.inputPort()));

    assert(mul.inputPort(0).isConnected());
    assert(mul.inputLink(0));
    assert(mul.previousNode(0));
    assert(mul.inputPort(1).isConnected());
    assert(mul.inputLink(1));
    assert(mul.previousNode(1));

}

int main()
{
    printf("-- kiwi::test_arithmemtic\n");
    TypeSystem ts;
    NodeTypeMap nodeTypes;
    DataTypeMap dataTypes;

    registerTypes(dataTypes);
    registerNodes(ts, nodeTypes, dataTypes);

    NodeGroup ng(&ts);

    instanciateNodes(ng, nodeTypes);
    assert(build(ng));
    assert(run());
    assert(run());
    assert(build(ng));
    assert(run());

    printf("-- success\n");
    return 0;
}
