module kiwi.dynamic.node;

import kiwi.core.all;
import kiwi.dynamic.port;

import std.typecons;

//######################################################################

alias void function(Data[] inputData, Data[] outputData) NodeUpdateFunction;
alias Tuple!(string, DataTypeInfo)      OutputPortInitializer;

struct InputPortInitializer
{
    this(string pname, PortCompatibility comp, int pflags = 0) 
    { 
        name = pname;
        compatibility = comp; 
        flags = pflags;
    }
    string name;
    PortCompatibility compatibility;
    int flags;
}



class DynamicNode : Node {

    this( InputPortInitializer[] inputs, OutputPortInitializer[] outputs
        , NodeUpdateFunction updateFunction = null )
    {
        mixin( logFunction!"DynamicNode.constructor" );
        foreach( ipi ; inputs )  addInputPort( ipi.compatibility, ipi.flags, ipi.name);
        foreach( opi ; outputs ) addOutputPort( opi[1], opi[0] );
        _updateFunc = updateFunction;
    }

    override{
        @property {
            NodeListener listener(){ return _listener; }
            void listener(NodeListener listnr){ _listener = listnr; }
            InputPort[] inputs() { return _inputPorts; }
            OutputPort[] outputs() { return _outputPorts; }     
            NodeGroup group() { return _group; }
            void group(NodeGroup value) { _group = value; }
            string name(){ return "DynamicNode"; }
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
                {
                    // returns if non optional inputs are not connected
                    // TODO should throw an exception !
                    if(!inputPort.isOptional && !inputPort.isConnected)
                        return;
                    if(inputPort.isConnected)
                        inputData ~= inputPort.connection.data;
                    else
                        inputData ~= null;        
                }
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

    void addInputPort( PortCompatibility compatibility, int portFlags, string name)
    {        
        _inputPorts ~= new DynamicInputPort( this, compatibility, portFlags, name );
    }
    void addOutputPort( DataTypeInfo typeInfo, string name)
    {        
        _outputPorts ~= new DynamicOutputPort( this, null, typeInfo, 0, name ); // TODO flags
    }

    bool setOutputPortData( int index, DataRef dataref )
    in
    {
        assert( dataref !is null );
        assert( index > 0 );
        assert( index < outputs.length );
    }
    body
    {        
        if( dataref.data !is null )
            if(output(index).dataType !is dataref.data.type && output(index).dataType !is null) return false;
        output(index).dataRef = dataref;
        return true;
    }

private:
    InputPort[]         _inputPorts;
    OutputPort[]        _outputPorts;
    NodeListener        _listener;
    NodeUpdateFunction  _updateFunc;
    NodeGroup           _group;
}


Node NewContainerNode( kiwi.core.base.Data data )
{
    mixin( logFunction!"NewContainerNode" );

    OutputPortInitializer[] dataPort = [];
    dataPort ~= OutputPortInitializer("Data", data.type );
    auto n = new DynamicNode( [], dataPort, null );
    n.output().data = data;
    return n;
}




//            #####   #####    ####   #####    ####
//              #     #       #         #     #
//              #     ###      ###      #      ###
//              #     #           #     #         #
//              #     #####   ####      #     ####





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
