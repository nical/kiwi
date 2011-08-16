module kiwi.core.dynamic;

import kiwi.core.commons;
import kiwi.core.base;
import kiwi.core.data;


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

class PermissiveInputPort : InputPort
{
    this(string myName = "input"){
        _name = myName;
    }
    override{
        @property{
            int maxConnections(){ return -1; }
            string name(){ return _name; }
        }
        
        bool isCompatible( OutputPort port ){ return (port !is null); }        
    }

private:
    string _name;    
}

class PermissiveOutputPort : OutputPort
{
    this(string myName = "input"){
        _name = myName;
    }
    override{
        @property{
            int maxConnections() { return -1; }
            string name() { return _name; }
            OutputPort[] subPorts() { return []; }
        }
        
        bool isCompatible( InputPort port ){ return (port !is null); }        
    }

private:
    string _name;    
}


unittest{
    mixin(logTest!"kiwi.dynamic.unittest");
    
    auto pin = new PermissiveInputPort();
    auto pout = new PermissiveOutputPort();

    assert( pin.connect(pout) );

    
}

