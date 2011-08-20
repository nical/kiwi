module kiwi.dynamic.node;

import kiwi.commons;
import kiwi.core;
import kiwi.data;
import kiwi.dynamic.port;

//######################################################################


class DynamicNode : Node {
    
    override{
        @property {
            NodeListener listener(){ return _listener; }
            void listener(NodeListener listnr){ _listener = listnr; }
            InputPort[] inputs() { return _inputPorts; }
            OutputPort[] outputs() { return _outputPorts; }            
        }//properties

        InputPort input(int index = 0){ return _inputPorts[index]; }
        OutputPort output(int index = 0){ return _outputPorts[index]; }
        
        void update(){};
    }//override
private:
    InputPort[] _inputPorts;
    OutputPort[] _outputPorts;
    NodeListener _listener;
}



unittest{
    mixin(logTest!"kiwi.dynamic.unittest");
    
    auto pin = new DynamicInputPort(null);
    auto pout = new DynamicOutputPort(null, ContainerWrapper!int.Type );

    assert( pin.connect(pout) );

}

