module kiwi.core.base;

import kiwi.core.commons;
import kiwi.core.interfaces;
import kiwi.core.data;

import std.string;
import std.conv;



class StaticPort(dataType) : PortInterface{
    alias dataType DataType;

    this(DataType data = null){
        _data = data;
    }
    
    override{
        @property PortInterface[] connections(){ return _connections; }         
        @property DataTypeInfo dataTypeInfo(){ return _dataTypeInfo; }
        @property DataInterface data() { return _data; }
        @property NodeInterface node() { return _node; }
        bool isCompatible(PortInterface port){ return true; }                   //TODO
        bool isComposite() { return false; }                                    //TODO
        

        public bool disconnectAll(){
            mixin(logFunction!"dynamic.Port.disconnectAll");
            while( connections.length > 0 ){
                connections[$].disconnect(this);
            }
            return true;
        }

        bool isConnectedTo(PortInterface port){
            foreach( connectn ; connections ){
                if( connectn is port ) return true;
            }
            return false;
        }

        protected void doConnect(PortInterface toConnect){
            mixin(logFunction!"StaticPort.Port.doConnect");
            // check that toConnect is not already connected.
            foreach( connectn ; connections ){
                if( connectn is toConnect ) return;
            }
            _connections ~= toConnect;
        }

        protected void doDisconnect(PortInterface toConnect){
            mixin(logFunction!"StaticPort.doDisconnect");
            for( int i = 0; i < connections.length; ++i ){
                if( connections[i] is toConnect ){
                    log.writeln(i, " ", connections.length);
                    _connections[i] = _connections[$-1];
                    _connections.length -= 1;
                }
            }
        }
    }//override

private:
    static DataTypeInfo   _dataTypeInfo;
    PortInterface[]       _connections;
    DataType              _data;
    NodeInterface         _node;
    NodeListenerInterface _listener;
}


/*

template NodeSystem(string name, layout...){

alias layout Layout;
alias name Name;

string _declareConstants(){
  int i = 0;
  string result = "enum{";
  foreach(symbol; layout){
    result ~= symbol.toupper() ~ " = " ~ to!string(i++) ~ ", ";    
  }
  result ~= "INVALID};";
  return result;
}

mixin( _declareConstants() );

string _declareFunctions(){
  string result;
  foreach(symbol; layout){
    result ~= "PortInterface " ~ symbol ~ "(int index = 0)"
        ~ "{ return _ports[" ~ symbol.toupper() ~ "][index];}";
  }
  return result;
}

class DynamicNode : NodeInterface{
    mixin( _declareFunctions() );
    mixin _listenerMixin ;

    override{
        void update(){}
        PortInterface opIndex(int portType, int index = 0){
            return _ports[index][portType];        
        }
    }
    
private:
    PortInterface[][] _ports;    
}
/+
class StaticNode(portDeclarations...) : NodeInterface{
    
}

class ContainerNode(ContainerClass) : NodeInterface{

}
+/
    
}// template NodeSystem


mixin template _listenerMixin(){
    @property{
        public NodeListenerInterface listener(){ return _listener; }
        public void listener(NodeListenerInterface val){ _listener = val; }
    }
    private NodeListenerInterface _listener;
        
}


template DeclarePort(T, int portType, string portName){
    alias T Class;
    alias int Type;
    alias portName Name;
}

*/


// -----------------------------------------------------------------------------




unittest{
    mixin( logTest!"NodeSystem.unittest" );

    //alias NodeSystem!("UnittestSystem","input","output") UnittestSystem;

    //auto n1 = new UnittestSystem.DynamicNode();

    auto p1 = new StaticPort!(ContainerWrapper!float);
}

