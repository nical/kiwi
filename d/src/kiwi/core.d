module kiwi.core;
// kiwi imports
import kiwi.commons;
import kiwi.data;
// external imports
import std.string;
import std.conv;



alias int PortFlags;

enum{ 
    OPTIONAL = 1
    , READ = 2
    , WRITE = 4
    , READ_WRITE = READ | WRITE };

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

    // TODO: temporary, will be replaced by a more generic "serialize"
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




class InputPort
{
public:
    this(Node n, PortFlags f = 0)
    {
        _node = n;
        _flags = f;
    }

    abstract{
        @property{
             /++
             + Returns the name of this port.
             +/ 
            string name();
            /++
             +
             +/ 
            int maxConnections();    
                             
        }
        bool isCompatible( OutputPort );
    }
    
    @property{
        Node node() { return _node; }
        OutputPort[] connections() { return _connections; }
        PortFlags flags() { return _flags; }
        bool isOptional(){ return _flags & OPTIONAL; }
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
            
        if ( this.maxConnections >= 0 && this.connections.length >= this.maxConnections )
            return false;

        if ( port.maxConnections >= 0 && port.connections.length >= port.maxConnections )
            return false;
        
        if ( !this.isCompatible(port) || !port.isCompatible(this) )
            return false;

        this._connections ~= port;
        port._connections ~= this;

        return true;       
    }

    /++
     + Disconnect this port from an OutputPort if they are conected.
     +/ 
    bool disconnect( OutputPort port )
    out
    {
        assert( !port.isConnectedTo(this), "disconnection failed." ); 
        assert( !this.isConnectedTo(port), "disconnection failed." ); 
    }
    body
    {
        mixin( logFunction!"InputPort.disconnect" );
        if ( port is null )
            return false;

        int i1 = this.indexOf(port);
        int i2 = port.indexOf(this);

        if ( i1 < 0 )
            return false;

        // proceed with the disconnection
        this._connections[i1] = this.connections[$-1];
        this._connections.length -= 1;
        port._connections[i2] = port.connections[$-1];
        port._connections.length -= 1;

        return true;
    }

    void disconnectAll()
    {
        for(int i = 0; i < connections.length; ++i)
            this.disconnect(connections[i]);
    }

    /++
     + Returns true if this port is connected to the one passed in parameter.
     +/ 
    bool isConnectedTo( OutputPort port )
    {
        return ( indexOf(port) >= 0 );
    }

    /++
     + Returns true if the port is connected.
     +/ 
    bool isConnected()
    {
        return ( connections.length > 0 );
    }
protected:

    /++
     + Checks that the state of the connection between this and the port is reciproqual.
     +
     + In other words, if this.connections contains port then port.connections must contain this, etc. 
     + Should return true in any case. intended for debug.
     +/
    bool isConnectionReciproqual(OutputPort port)
    {
        uint i1 = this.indexOf(port);
        uint i2 = port.indexOf(this);
        if (i1 < 0 && i2 < 0) return true;
        if (i1 >= 0 && i2 >= 0) return true;
        return false;
    }

    @property void connections(OutputPort[] value)
    {
        _connections = value;
    }
    
    /++
     + Returns the index of an output port in connections, or -1 if not found.
     +/ 
    int indexOf(OutputPort port)
    {
        for(int i = 0; i < connections.length; ++i){
            if( connections[i] is port )
                return i;
        }
        return -1;
    }

private:
    PortFlags    _flags;
    OutputPort[] _connections;
    Node         _node;
} // class InputPort








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
            /++
             +
             +/
            Data data();
            
            void data( kiwi.core.Data value );        
            //in{ if( dataType !is null && value !is null ) assert( data.type is dataType ); } 
            
        } //properties
    } //abstract
      
    
    @property{
        Node node(){ return _node; }
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
            data = dataType.newInstance();   
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
    
    @property{
        void flags(PortFlags value){ _flags = value; }
        void node(Node value){ _node =  value; }
    }
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

