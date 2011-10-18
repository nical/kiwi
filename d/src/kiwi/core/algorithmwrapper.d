module kiwi.core.algorithmwrapper;

import kiwi.core.node;
import kiwi.core.data;
import kiwi.core.container;
import kiwi.core.commons;
import kiwi.core.datastrategy;

import std.traits;



class FunctionWrapper(FuncType) : NodeUpdater
{
    alias ParameterTypeTuple!FuncType Params;
    this( FuncType* funcPtr )
    {
        _funcPtr = funcPtr;
    }

    override void update(Node n)
    {
        Params params;
        int i = 0;// why ? and idx ?
        foreach( int idx, param ; params ) // needs ref
        {
            if ( i < n.inputCount )
            {
                static if( __traits(compiles, cast(typeof(param)) new Data ) )
                {
                    params[idx] = cast(typeof(param)) n.inputs[i].data;
                }
                else
                {
                    auto p = (n.inputs[i].dataAs!(Container!(typeof(param)))).value;
                    params[idx] = p;
                }
            }
            else
            {
                static if( __traits(compiles, cast(typeof(param)) new Data ) )
                {
                    params[idx] = cast(typeof(param)) n.outputs[i-n.inputCount].data;
                }
                else
                {
                    params[idx] = (cast(Container!(typeof(param))) n.outputs[i-n.inputCount].data).value;
                }
            }
            ++i;
        }
        //foreach( p; params ){ log.writeln("| ", p ); }
        _funcPtr(params);

        // if one of the output is a container of a value semantic type, we need
        // to put it's value back manually because it seems the parameter type tuple
        // doesn't take references.
        // TODO: find a nicer way to work around this reference problem 
        foreach( int idx, param ; params )
        {
            if ( idx >= n.inputCount )
            {
                static if( !__traits(compiles, cast(typeof(param)) new Data ) )
                {
                    (cast(Container!(typeof(param))) n.outputs[idx-n.inputCount].data).value = params[idx];                    
                }
                else
                {
                    log.writeln("--");
                }
            }
        }
    }

    FuncType* _funcPtr;
}

NodeUpdater WrapFunction(T)(T* func)
{
    return new FunctionWrapper!T(func);
}

version(unittest)
{
    import kiwi.core.node;
    import kiwi.core.port;

    void algorithmTest(int in_a, float in_b, ref float out_ab)
    {
        mixin( logFunction!"algorithmTest" );
        log.writeln("params: ", in_a, ", ", in_b, ", [out] ", out_ab);
        out_ab = in_a + in_b;
        assert(in_a == 42);
        assert(in_b > 3);
        assert(in_b < 4);
        
        assert(out_ab > 45.0);
        assert(out_ab < 50.0);
    }

}

unittest
{
    mixin( logTest!"kiwi.core.algorithmwrapper" );
    
    auto plop = WrapFunction( &algorithmTest );
    
    auto n = new Node
    (
        null, // typeInfo("FuncWrapperTestNode",...
        [
            DeclareInput("A", Container!int.Type, READ ),
            DeclareInput("B", Container!float.Type, READ )
        ],
        [
            DeclareOutput("out", new UserAllocatedDataStrategy(new Container!float, READ_WRITE)) 
        ],
        WrapFunction( &algorithmTest )
    );

    auto in1 = NewContainerNode( new Container!int(42) );
    auto in2 = NewContainerNode( new Container!float(3.14) );

    (cast(Container!float)n.output.data).value = 0.5f;

    assert( in1.output.dataAs!int == 42 );
    
    in1.output >> n.input(0);
    in2.output >> n.input(1);

    
    n.update;

    log.writeln( n.output.dataAs!float );

    assert( n.output.dataAs!float > 45.0 );
    assert( n.output.dataAs!float < 50.0 );
    

    int[4] ints;
    foreach( ref i ; ints ){ i = 42; }
    foreach( i ; ints ){ assert( i == 42 ); }

}
