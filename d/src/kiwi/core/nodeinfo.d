module kiwi.core.nodeinfo;

import kiwi.utils.hstring;
import kiwi.core.node;
import kiwi.core.commons;
import kiwi.core.runtimetype;

struct NodeTypeInfo
{
    HString             name;
    InputPortInfo[]     inputs;
    OutputPortInfo[]    outputs;
    // callbacks
    void delegate(Node*) onCreation;
    void delegate(Node*) onDestruction;
    bool delegate(Node*) onUpdate;
    bool delegate(RuntimeType*[] inputs, RuntimeType*[] outputs) onProcess;
}


struct InputPortInfo
{
    HString     name;
    DataTypeID  dataType;
    ubyte       flags;
}


struct OutputPortInfo
{
    HString     name;
    DataTypeID  dataType;
    ubyte       flags;
}


unittest
{
    import kiwi.utils.testing;
    auto unit = TestSuite("kiwi.core.nodeinfo");
    
    DataTypeID intID;

    auto nUpdate = delegate(Node*) {
        log.writeln("Node updating");
        return true;
    };
    
    NodeTypeInfo nti = {
        name : HString("NodeName"),
        inputs : [
            { HString("in#1"), intID, READ },
            { HString("in#2"), intID, READ }
        ],
        outputs : [
            { HString("out"), intID, READ },
        ],
        onUpdate : nUpdate
    };


}
