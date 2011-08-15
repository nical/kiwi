module kiwi.core.dynamic;

import kiwi.core.commons;
import kiwi.core.interfaces;
import kiwi.core.data;


//######################################################################


class Node : NodeInterface {

    override{
        @property {
            NodeListenerInterface listener(){ return _listener; }
            void listener(NodeListenerInterface listnr){ _listener = listnr; }
        }//properties

        PortInterface input(int index = 0){ return _inputPorts[index]; }
        PortInterface output(int index = 0){ return _outputPorts[index]; }
        
        void update(){};
    }//override
private:
    PortInterface[] _inputPorts;
    PortInterface[] _outputPorts;
    NodeListenerInterface _listener;
}



class ContainerNode : NodeInterface {
    this(DataInterface _data){        
        _dataPort  = new Port(this,_data);
    }
    
    @property {
        override NodeListenerInterface listener(){ return _listener; }
        override void listener(NodeListenerInterface listnr){ _listener = listnr; }
    }
    
    
    override void update(){}
    
    Port input(int index = 0){ return null; }
    Port output(int index = 0){
        if(index == 0) return _dataPort;
        return null; 
    }
    
private:
    Port _dataPort;
    NodeListenerInterface _listener;
}


//######################################################################


class Port : PortInterface{

    this(NodeInterface myNode, DataInterface myData, PortCompatibilityPolicy compatibility = null){
        mixin(logFunction!"dynamic.Port.constructor#1");
        this._node = myNode;
        this._data = myData;
        if(myData !is null)
            this._dataTypeInfo = myData.typeInfo();
        else
            this._dataTypeInfo = null;
    }
    
    this(NodeInterface myNode = null, DataTypeInfo dataTypeInfo = null, PortCompatibilityPolicy compatibility = null){
        mixin(logFunction!"dynamic.Port.constructor#2");
        _node = myNode;
        _dataTypeInfo = dataTypeInfo;
        _compatibility = compatibility;
    }


    override{
            
        public bool isCompatible(PortInterface port){    
            mixin(logFunction!"dynamic.Port.isCompatible");
            if(_compatibility is null)
                return true;
            else
                return _compatibility(this,port);
        }

        /**
         *
         */ 
        public bool isComposite(){
            mixin(logFunction!"dynamic.Port.isComposite");
            if( _dataTypeInfo is null )
                return false;
            else
                return _dataTypeInfo.isComposite();    
        }
        
        /**
         *
         */
        public bool disconnectAll(){
            mixin(logFunction!"dynamic.Port.disconnectAll");
            while( connections.length > 0 ){
                connections[$].disconnect(this);
            }
            return true;
        }

        protected void doConnect(PortInterface toConnect){
            mixin(logFunction!"dynamic.Port.doConnect");
            // check that toConnect is not already connected.
            foreach( connectn ; connections ){
                if( connectn is toConnect ) return;
            }
            _connections ~= toConnect;
        }

        /**
         * Returns true if this port is connected to a particular port.
         */
        bool isConnectedTo(PortInterface port){
            foreach( connectn ; connections ){
                if( connectn is port ) return true;
            }
            return false;
        }

        /**
         *  
         */
        protected void doDisconnect(PortInterface toConnect){
            mixin(logFunction!"dynamic.Port.doDisconnect");
            for( int i = 0; i < connections.length; ++i ){
                if( connections[i] is toConnect ){
                    log.writeln(i, " ", connections.length);
                    _connections[i] = _connections[$-1];
                    _connections.length -= 1;
                }
            }
        }

        @property{
            DataInterface data(){ return _data; }
            DataTypeInfo dataTypeInfo(){ return _dataTypeInfo; }
            PortInterface[] connections(){ return _connections; }
            Node node(){ return _node; }
        }//properties
    }//override

    
    final T dataAs(T)(){
        return cast(T) data();
    }

    protected PortCompatibilityPolicy _compatibility;
    protected PortInterface[]     _connections;
    protected DataInterface       _data;
    protected DataTypeInfo        _dataTypeInfo;
    protected NodeInterface       _node;
} // class Port


// ---------------------------------------------------------------------






unittest{
    mixin(logTest!"kiwi.dynamic.unittest");
    
    auto p1 = new kiwi.core.dynamic.Port();
    auto p2 = new kiwi.core.dynamic.Port();

    assert( p1.connect(p2) );

    
}

