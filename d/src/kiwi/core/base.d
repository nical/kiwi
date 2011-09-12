module kiwi.core.base;
// kiwi imports
import kiwi.core.commons;
import kiwi.core.data;
// external imports
import std.string;
import std.conv;



alias int PortFlags;

enum{ 
    OPTIONAL = 1
    , READ = 2
    , WRITE = 4
    , READ_WRITE = READ | WRITE };

alias Data delegate() DataRef_;

DataRef_ DataGet( Data toGet )
{
    return delegate(){ return toGet; };
}

interface DataRef
{
    @property
    {
        Data data();
        void data(Data val);    
    }
}

class BasicDataRef : DataRef
{
    this(Data initVal)
    {
        data = initVal;
    }
    override{
        @property{
            Data data(){ return _data; }
            void data(Data val){ _data = val; }
        }
    }
    protected Data _data;
}

class InputDataRef : DataRef
{
    this(InputPort port)
    {
        _input = port;
    }

    override{
        @property{
            Data data(){
                if(_input !is null && _input.isConnected)
                    return _input.connection.data;
                return null;
            }
            void data(Data val){}
        }
    }

    private InputPort _input;
}

interface Node{

    @property{
        NodeListener listener();
        void listener(NodeListener listnr);
        InputPort[] inputs();
        OutputPort[] outputs();
        NodeGroup group();
        void group(NodeGroup);
        string name();
    }//properties

    /++
     + Function to override in order to have the node do whatever processing it
     + is supposed to do. 
     +/ 
    void update();

    /++
     + Input port accessor.
     +/ 
    InputPort input(int index = 0);
    
    
    /++
     + Output port accessor.
     +/ 
    OutputPort output(int index = 0);


    /++
     + Access input ports by name.
     +
     + TODO: for composite ports access them like foo.bar with bar the sub port name.
     +/ 
    final InputPort input( string portName )
    {
        foreach(port ; inputs){
            if(port.name == portName)
                return port;
        }
        return null;
    }
    
    /++
     + Access output ports by name.
     +/     
    final OutputPort output( string portName )
    {
        foreach(port ; outputs){
            if(port.name == portName)
                return port;
        }
        return null;
    }

    // TODO
    final string serialize()
    {
        string result = "{\"name\":"~name~", \"inputs\":[";
        bool first = true;
        foreach( inputPort ; this.inputs ){
            if(!first) result ~= ", ";
            first = false;
            //result ~= inputPort.;
        }

        result ~= "], \"outputs\":[";

        first = true;
        foreach( outputPort ; this.outputs ){
            if(!first) result ~= ", ";
            first = false;
            //result ~= inputPort.;
        }
        result ~= "] }";        
        return result;
    }
protected:
    final void notifyInputPortConnected(InputPort myPort, OutputPort otherPort)
    {
        if(listener !is null) listener.inputPortConnected(myPort, otherPort);
    }
    final void notifyInputPortDisconnected(InputPort myPort, OutputPort otherPort)
    {
        if(listener !is null) listener.inputPortDisconnected(myPort, otherPort);
    }
    final void notifyInputPortAdded(InputPort addedPort)
    {
        if(listener !is null) listener.inputPortAdded(addedPort);
    }
    final void notifyInputPortRemoved(InputPort removedPort)
    {
        if(listener !is null) listener.inputPortRemoved(removedPort);
    }
    final void notifyOutputPortConnected(OutputPort myPort, InputPort otherPort)
    {
        if(listener !is null) listener.outputPortConnected(myPort, otherPort);
    }
    final void notifyOutputPortDisconnected(OutputPort myPort, InputPort otherPort)
    {
        if(listener !is null) listener.outputPortDisconnected(myPort, otherPort);
    }
    final void notifyOutputPortAdded(OutputPort addedPort)
    {
        if(listener !is null) listener.outputPortAdded(addedPort);
    }
    final void notifyOutputPortRemoved(OutputPort removedPort)
    {
        if(listener !is null) listener.outputPortRemoved(removedPort);
    }

}// Node





interface NodeGroup
{
    
    bool addNode( Node n );
    bool removeNode( Node n );
    void optimize( int flags );
    void update();
    bool serialize( DataStream stream );
    bool deSerialize( DataStream stream );
    
}




interface InputPort
{
public:
    
    @property{
         /++
         + Returns the name of this port.
         +/ 
        string name();
        
        public PortFlags flags();
        protected void flags(PortFlags value);

        public Node node();
        protected void node(Node value);

        public OutputPort connection();
        protected void connection(OutputPort value);
                                      
    }
    bool isCompatible( OutputPort );

    
    final
    {
        @property{
            Data data() 
            { 
                if ( !isConnected ) return null;
                return connection.data;
            }

            bool isOptional(){ return flags & OPTIONAL; }
        }
        
        

        /++
         + Connects this port to an OutputPort if possible.
         +/ 
        bool connect( OutputPort port )
        out
        {
            assert (isConnectionReciproqual(port), "port connection reciprocity test failed. ");
        }
        body
        {
            mixin( logFunction!"InputPort.connect" );
            if (port is null)
                return false;

            
            if ( port.maxConnections >= 0 && port.connections.length >= port.maxConnections )
                return false;
            
            if ( !this.isCompatible(port) || !port.isCompatible(this) )
                return false;

            if( this.isConnected ) disconnect();

            this.connection = port;
            port._connections ~= this;

            return true;       
        }

        /++
         + Disconnect this port from an OutputPort if they are conected.
         +/ 
        bool disconnect( OutputPort port  = null)
        out
        {
            if(port !is null) assert( !port.isConnectedTo(this), "disconnection failed." ); 
            assert( !this.isConnectedTo(port), "disconnection failed." ); 
        }
        body
        {
            mixin( logFunction!"InputPort.disconnect" );

            if ( port !is null && connection !is port ) return false;
            else
            {
                if ( connection is null ) return false;
                port = this.connection;
            }
            
            int i2 = port.indexOf(this);
                
            // proceed with the disconnection
            this.connection = null;
            port._connections[i2] = port.connections[$-1];
            port._connections.length -= 1;
            return true;
        }

        /++
         + Returns true if this port is connected to the one passed in parameter.
         +/ 
        bool isConnectedTo( OutputPort port )
        {
            return connection is port ;
        }

        /++
         + Returns true if the port is connected.
         +/ 
        bool isConnected()
        {
            return ( connection !is null );
        }
    }
protected:

    /++
     + Checks that the state of the connection between this and the port is reciproqual.
     +
     + In other words, if this.connections contains port then port.connections must contain this, etc. 
     + Should return true in any case. intended for debug.
     +/
    final bool isConnectionReciproqual(OutputPort port)
    {
        bool c1 = connection is port;
        uint i2 = port.indexOf(this);
        if (!c1 && i2 < 0) return true;
        if (c1 && i2 >= 0) return true;
        return false;
    }

    
} // InputPort








class OutputPort{
public:
    this(Node n, PortFlags f = 0)
    {
        _node = n;
        _flags = f;
    }
    
    abstract{
        /++
         + Returns true if this port has sub-ports.
         +/ 
        bool isComposite();
        /++
         + Returns true if this port is compatible with the InputPort in parameter.
         +/ 
        bool isCompatible( InputPort );
        
        @property{
            /++
             + Returns the maximum number of connections.
             +/ 
            int maxConnections();
            /++
             + Returns the name of this port.
             +/ 
            string name();
            /++
             + Returns this port's sub-ports if composite.
             +/ 
            OutputPort[] subPorts();
            /++
             + 
             +/
            DataTypeInfo dataType() pure;
          
            
            void dataRef( DataRef value );        
            DataRef dataRef();        
            //in{ if( dataType !is null && value !is null ) assert( data.type is dataType ); } 
            
        } //properties
    } //abstract
      
    
    @property{
        Node node(){ return _node; }
        
        Data data()
        { 
            if(dataRef is null ) return null;
            return dataRef.data;
        }
        
        void data( Data val )
        {
            if(dataRef is null)
                dataRef = new BasicDataRef( val );
            else
                dataRef.data = val;
        }

        InputPort[] connections(){ return _connections; }
        PortFlags flags(){ return _flags; }        
        bool isOptional(){ return _flags & OPTIONAL; }        
    }

    /++
     + Connects this port to an InputPort.
     +/ 
    bool connect(InputPort port)
    {
        mixin( logFunction!"OutputPort.connect" );
        if(port is null)
            return false;

        return port.connect(this);
    }


    final bool opBinary(string op)(InputPort port) if (op == ">>")
    {
        return connect( port );
    }

    /++
     + disconnect this port from an InputPort.
     +/ 
    bool disconnect(InputPort port)
    {
        if(port is null)
            return false;
        
        return port.disconnect(this);
    }

    void disconnectAll()
    {
        for(int i = 0; i < connections.length; ++i)
            this.disconnect(connections[i]);

        foreach( p ; subPorts )
            p.disconnectAll();
    }
    
    bool isConnectedTo(InputPort port)
    {
        return indexOf(port) != -1;
    }

    bool isConnected()
    {
        return connections.length > 0;
    }

    void allocateData()
    {
        if( data is null ){
            data = dataType.newInstance();                 // TODO ! unsafe if dataType is null
        }
    }
protected:

    @property void connections(InputPort[] value)
    {
        _connections = value;
    }
    /++
     + Returns the index of an output port in connections, or -1 if not found.
     +/ 
    int indexOf(InputPort port)
    {
        for(int i = 0; i < connections.length; ++i){
            if( connections[i] is port )
                return i;
        }
        return -1;
    }

    
    void _setFlags(PortFlags value){ _flags = value; }
    void _setNode(Node value){ _node =  value; }
        
private:
    PortFlags    _flags;
    InputPort[]  _connections;
    Node         _node;
} // class OutputPort





interface NodeListener
{
    void inputPortConnected(InputPort myPort, OutputPort otherPort);
    void inputPortDisconnected(InputPort myPort, OutputPort otherPort);
    void inputPortAdded(InputPort addedPort);
    void inputPortRemoved(InputPort removedPort);
    void outputPortConnected(OutputPort myPort, InputPort otherPort);
    void outputPortDisconnected(OutputPort myPort, InputPort otherPort);
    void outputPortAdded(OutputPort addedPort);
    void outputPortRemoved(OutputPort removedPort);
    void nodeChanged();
    void detachNode();
}

