module kiwi.core.base;

import kiwi.core.commons;
import kiwi.core.interfaces;
import kiwi.core.data;

import std.string;
import std.conv;



alias int PortFlags;


interface Node{

    @property{
        NodeListener listener();
        void listener(NodeListener listnr);
        InputPort[] inputs();
        OutputPort[] outputs();
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
    }
    
    

    /++
     + Connects this port to an OutputPort if possible.
     +/ 
    bool connect( OutputPort port )
    {
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
    {
        if ( port is null )
            return false;
            
        uint i1 = this.indexOf(port);
        uint i2 = port.indexOf(this);

        // Check that i1 and i2 are of the same sign.
        // (if this has port in its connections, port should have this too, etc.)
        assert ( i1*i2 > 0 );

        if ( i1 < 0 )
            return false;

        // proceed with the disconnection
        this.connections[i1] = this.connections[$];
        this.connections.length -= 1;
        port.connections[i2] = port.connections[$];
        port.connections.length -= 1;

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
        }//properties
    } //abstract
      
    @property{
        Node node(){ return _node; }
        InputPort[] connections(){ return _connections; }
        PortFlags flags(){ return _flags; }
        
        
    }

    /++
     + Connects this port to an InputPort.
     +/ 
    bool connect(InputPort port)
    {
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





interface NodeListener{
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

