module kiwi.core.mock;

import kiwi.core.commons;
import kiwi.core.node;
import kiwi.core.port;
import kiwi.core.container;
import kiwi.core.data;
import kiwi.core.datastrategy;



struct MockData
{
    int val;
}



Node NewMockNode(uint nbImputs, uint nbOutputs)
{
    InputDescriptor[] inputs;
    OutputDescriptor[] outputs;

    for(int i = 0; i < nbImputs; ++i)
        inputs ~= DeclareInput("in", new AlwaysCompatible, 0, true);
        
    for(int i = 0; i < nbOutputs; ++i)
        outputs ~= DeclareOutput("out"
            , new UserAllocatedDataStrategy(DataTypeManager["MockDataContainer"].newInstance));

    return new Node
    (
        null,
        inputs,
        outputs,
        null
    );
}

unittest
{
    mixin( logTest!"kiwi.core.mock" );
    log.foo;
    DataTypeManager.Register!(Container!MockData);
    log.foo;
    auto n1 = NewMockNode(2,2);
    log.foo;
    auto n2 = NewMockNode(1,3);
    log.foo;
    assert( n1.inputs.length == 2 );
    assert( n1.outputs.length == 2 );
    assert( n2.inputs.length == 1 );
    assert( n2.outputs.length == 3 );

    assert( n1.output(0) >> n2.input(0) );
    
    n1.update;
    n2.update;
}
