module kiwi.dynamic.node;

import kiwi.commons;
import kiwi.core;
import kiwi.data;
import kiwi.dynamic.port;

import std.typecons;

//######################################################################

alias void function(Data[] inputData, Data[] outputData) NodeUpdateFunction;
alias Tuple!(string, PortCompatibility) InputPortInitializer;
alias Tuple!(string, DataTypeInfo)      OutputPortInitializer;


class DynamicNode : Node {

    this( InputPortInitializer[] inputs, OutputPortInitializer[] outputs
        , NodeUpdateFunction updateFunction = null )
    {
        mixin( logFunction!"DynamicNode.constructor" );
        foreach( ipi ; inputs )  addInputPort( ipi[1], ipi[0] );
        foreach( opi ; outputs ) addOutputPort( opi[1], opi[0] );
        _updateFunc = updateFunction;
    }

    override{
        @property {
            NodeListener listener(){ return _listener; }
            void listener(NodeListener listnr){ _listener = listnr; }
            InputPort[] inputs() { return _inputPorts; }
            OutputPort[] outputs() { return _outputPorts; }            
        }//properties

        InputPort input(int index = 0){ return _inputPorts[index]; }
        OutputPort output(int index = 0){ return _outputPorts[index]; }
        
        void update()
        {
            mixin( logFunction!"DynamicNode.update" );
            allocateData();
            if(_updateFunc !is null)
            {
                Data[] inputData = [];
                Data[] outputData = [];

                foreach( inputPort ; _inputPorts )
                    inputData ~= inputPort.connections[0].data;
                foreach( outputPort ; _outputPorts )
                    outputData ~= outputPort.data;
                
                _updateFunc(inputData, outputData);
            }   
        }
    }//override

    void allocateData()
    {
        foreach( port ; outputs )
            port.allocateData();        
    }

    void addInputPort( PortCompatibility compatibility, string name)
    {        
        _inputPorts ~= new DynamicInputPort( this, compatibility, name );
    }
    void addOutputPort( DataTypeInfo typeInfo, string name)
    {        
        _outputPorts ~= new DynamicOutputPort( this, typeInfo, name );
    }

    bool setOutputPortData( int index, Data data )
    in
    {
        assert( index > 0 );
        assert( index < outputs.length );
    }
    body
    {
        if(output(index).dataType !is data.type && output(index).dataType !is null) return false;
        output(index).data = data;
        return true;
    }

private:
    InputPort[] _inputPorts;
    OutputPort[] _outputPorts;
    NodeListener _listener;
    NodeUpdateFunction _updateFunc;
}


Node NewContainerNode( kiwi.core.Data data )
{
    mixin( logFunction!"NewContainerNode" );

    OutputPortInitializer[] dataPort = [];
    dataPort ~= OutputPortInitializer("Data", data.type );
    auto n = new DynamicNode( [], dataPort, null );
    n.output().data = data;
    return n;
}

/*
             #####   #####    ####   #####    ####
               #     #       #         #     #
               #     ###      ###      #      ###
               #     #           #     #         #
               #     #####   ####      #     ####
*/


version(unittest)
{
    bool processCalled = false;
    void processTest()
    {
        mixin( logFunction!"unittest.processTest" );
        
        processCalled = true;
    }
}

unittest
{
    mixin(logTest!"kiwi.dynamic.node");
    

    Node n1 = new DynamicNode( [], [], &processTest );

    n1.update();

    assert( processCalled );

}