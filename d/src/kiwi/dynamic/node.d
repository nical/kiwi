module kiwi.dynamic.node;

import kiwi.commons;
import kiwi.core;
import kiwi.data;
import kiwi.dynamic.port;

//######################################################################

alias void function(Data[] inputData, Data[] outputData) NodeUpdateFunction;

class DynamicNode : Node {

    this( InputPort[] inputs, OutputPort[] outputs, NodeUpdateFunction updateFunction = null )
    {
        mixin( logFunction!"DynamicNode.constructor" );
        _inputPorts = inputs;
        _outputPorts = outputs;
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
private:
    InputPort[] _inputPorts;
    OutputPort[] _outputPorts;
    NodeListener _listener;
    NodeUpdateFunction _updateFunc;
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