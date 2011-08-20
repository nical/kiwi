module kiwi.dynamic.port;

import kiwi.core;
import kiwi.data;
import kiwi.commons;

//alias bool delegate(kiwi.core.OutputPort, kiwi.core.InputPort) PortCompatibilityPolicy;

interface PortCompatibility
{
    bool isCompatible( OutputPort port ) pure;
}

class DynamicInputPort : InputPort
{
    this(Node n, string myName = "input"){
        super(n);    
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

class DynamicOutputPort : OutputPort
{
    this(Node n, DataTypeInfo dataTypeInfo, string myName = "output"){
        super(n);    
        _name = myName;
    }
    override{
        @property{
            int maxConnections() { return -1; }
            string name() { return _name; }
            OutputPort[] subPorts() { return []; }
            const(DataTypeInfo ) dataType() pure { return _dataType; }
        }

        bool isComposite() { return false; }
        bool isCompatible( InputPort port ){ return (port !is null); }
        Data data(){ return _data; }             
    }

private:
    string _name;
    Data _data;  
    DataTypeInfo _dataType;  
}