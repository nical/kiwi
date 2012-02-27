
import kiwi.utils.testing;
import kiwi.core.commons;
import kiwi.core.context;
import kiwi.core.pipeline;
import kiwi.core.node;
import kiwi.core.nodeinfo;
import kiwi.core.runtimetype;
import kiwi.utils.hstring;

import std.stdio;

template type(T) { auto type = typeid(T); }
alias CompileHash name;

int main()
{
    { // test quite scope
        auto unit = TestSuite("Use case");
        
        auto nodeProcess1 = delegate(RuntimeType*[] inputs, RuntimeType*[] outputs) {
            int a = inputs[0].get!int;
            int b = inputs[1].get!int;
            log.write("nodeUpdate1(",a,", ",b,")");
            outputs[0].get!int = a+b;
            log.writeln(" => ", outputs[0].get!int );
            return true;
        };
        
        
        NodeTypeInfo intContainerInfo = {
            name : name!"IntContainer",
            outputs : [
                { name!"value", type!int, READ|WRITE }
            ]
        };
        
        NodeTypeInfo addIntInfo = {
            name : name!"Node#1",
            inputs : [
                { name!"in#1", type!int, READ },
                { name!"in#2", type!int, READ }
            ],
            outputs : [
                { name!"out", type!int, READ },
            ],
            onProcess : nodeProcess1
        };
        
        import kiwi.core.nodefactory;
        Context ctx = Context( null, new NodeFactory);
        
        auto container_info = ctx.registerNodeType(intContainerInfo);
        auto add_info       = ctx.registerNodeType(addIntInfo);
        
        Pipeline p1 = Pipeline(&ctx);
        
        auto nodeIdx = p1.instanciateNode( add_info );
        auto containerIdx = p1.instanciateNode( container_info );
        
        p1.node(containerIdx).output().connect( p1.node(nodeIdx).input(0) );
        p1.node(containerIdx).output().connect( p1.node(nodeIdx).input(1) );
        
        p1.node(containerIdx).output().setData!int(12);
        
        
        assert( p1.node(containerIdx).output().data.type == typeid(int) );
        
        p1.node(nodeIdx).update();
        
        log.writeln( p1.node(nodeIdx).input(0).data.get!int );
        log.writeln( p1.node(nodeIdx).input(1).data.get!int );
        log.writeln( p1.node(nodeIdx).output().data.get!int );
        assert( p1.node(nodeIdx).output().data.get!int == 24 );
    }
    
    
    if( TestSuite.FailedTestSuites.length > 0 )
    {
        log.writeln("\nThe following test suites failed: ");
        foreach( testName ; TestSuite.FailedTestSuites )
            log.writeln(RED, "   - ", testName, RESET );
        
        return 1;
    }
    return 0; 
}
