module kiwi.core.port;

import kiwi.core.data;
import kiwi.core.base;
import kiwi.core.commons;

alias int DataAccessFlag;

class OutPort
{
    this(Node n, string name, DataComponent dataComponent = null)
    {
        _node = n;
        _parent = null;
        _name = name;
        _setDataComponent(dataComponent); 
    }

    this(Node n, OutPort parent, string name, DataComponent dataComponent)
    {
        _node = n;
        _parent = parent;
        _name = name;
        _setDataComponent(dataComponent);
    }
    
    @property
    {
        Node node()
        {
            return _node;
        }

        bool hasDataComponent()
        {
            return _dataComponent !is null;
        }
        
        bool isComposite()
        {
            return _subPorts.length > 0;
        }

        bool isSubPort()
        {
            return _parent !is null;
        }

        DataTypeInfo dataType()
        {
            if ( this.hasDataComponent() ) return _dataComponent.dataType;
            else return null;
        }

        Data data()
        {
            if ( hasDataComponent ) return _dataComponent.data;
            else return null;
        }

        DataAccessFlag accessFlags()
        {
            if ( hasDataComponent ) return _dataComponent.accessFlags;
            else return 0;
        }

        

//        bool hasInfoComponent()
//        {
//            return _portInfoComponent !is null;
//        }

        string name()
        {
            return _name;
        }

        OutputPortModifier modify()
        {
            return _modifier;
        }

        bool isAlterable()
        {
            return _modifier !is null;
        }

        InPort[] connections()
        {
            return _connections;
        }

        OutPort[] subPorts()
        {
            return _subPorts;
        }

        void disconnectAll()
        {
            for(int i = 0; i < _connections.length; ++i)
                this.disconnect(_connections[i]);

            foreach( p ; subPorts )
                p.disconnectAll();
        }
        
    } // properties

    OutPort subPort(uint i)
    {
        return _subPorts[i];
    }
    
    OutPort subPort(string byName)
    {
        foreach( sp ; _subPorts )
            if(sp.name == byName)
                return sp;
        return null;
    }

    bool isCompatible( InPort port )
    {
        return port.isCompatible(this);
    }

    bool isConnectedTo( InPort port )
    {
        foreach( p ; _subPorts)
            if( p is port)
                return true;
        return false;
    }   

    bool connect(InPort port)
    {
        if ( port is null )
            return false;
        return port.connect(this);
    }

    bool disconnect( InPort port )
    {
        if(port is null)
                return false;
            
        return port.disconnect(this);
    }

    final bool opBinary(string op)(InPort port) if (op == ">>")
    {
        return connect( port );
    }

    
protected:
    /++
     + Returns the index of an output port in connections, or -1 if not found.
     +/ 
    protected int indexOf(InPort port)
    {
        for(int i = 0; i < connections.length; ++i){
            if( connections[i] is port )
                return i;
        }
        return -1;
    }

    void _setDataComponent(DataComponent component)
    {
        if ( component is _dataComponent ) return;

        foreach( p ; _subPorts)
            p.disconnectAll();

        _subPorts = [];
        _dataComponent = component;
        if ( (dataType !is null) && (dataType.subData !is null) )
        {
            log.writeln(dataType.name);
            log.writeln(dataType.subData.length);
            
            foreach( subTypeInfo ; dataType.subData )
            {
                log.writeDebug(0, subTypeInfo.name );
                _subPorts ~= new OutPort( node, this, "sub"
                    , component.newSubDataComponent(_subPorts.length-1) );
            }
        }
    }
private:

    Node    _node;
    string  _name;
    InPort[] _connections;
    OutputPortModifier _modifier;
    OutPort[] _subPorts;
    OutPort _parent;
    
    // components
    DataComponent _dataComponent;
    //PortInfoComponent   _portInfoComponent;
    
}




class InPort
{
    @property
    {

        Node node()
        {
            return _node;
        }
            
        DataAccessFlag accessFlags()
        {
            return _accessFlags;
        }

        OutPort connection()
        {
            return _connection;
        }

        bool isConnected()
        {
            return _connection !is null;
        }
        
        bool hasCompatibilityComponent()
        {
            return _compatibilityComponent !is null;
        }

    }

    bool isCompatible( OutPort port )
    {
        if ( !( accessFlags & port.accessFlags ) )
            return false;
        if ( hasCompatibilityComponent )
            return _compatibilityComponent.isCompatible(this, port);
        return true;
    }

    bool isConnectedTo( OutPort port )
    {
        return _connection is port;
    }

    bool connect(OutPort port)
    {
        if (port is null)
            return false;

        if (! isCompatible(port) )
            return false;

        if( this.isConnected ) disconnect();

        this._connection = port;
        port._connections ~= this;

        return true;       
    }

    /++
     + Disconnect this port from an OutputPort if they are conected.
     +/ 
    bool disconnect( OutPort port = null)
    out
    {
        if(port !is null) assert( !port.isConnectedTo(this), "disconnection failed." ); 
        assert( !this.isConnectedTo(port), "disconnection failed." ); 
    }
    body
    {
        mixin( logFunction!"InputPort.disconnect" );

        if ( port !is null && _connection !is port ) return false;
        else
        {
            if ( _connection is null ) return false;
            port = this._connection;
        }
        
        int i2 = port.indexOf(this);
        
        // proceed with the disconnection
        this._connection = null;
        port._connections[i2] = port._connections[$-1];
        port._connections.length -= 1;
        return true;
    }
    
private:
    Node _node;
    DataAccessFlag _accessFlags;
    string _name;
    OutPort _connection;
    InputPortModifier _modifier;
    // components
    CompatibilityComponent  _compatibilityComponent;
    //PortInfoComponent       _portInfoComponent;
}




// -----------------------------------------------------------------------------




interface PortInfoComponent
{
    @property
    {
        string name();
    }
}

interface CompatibilityComponent
{
    bool isCompatible(InPort self, OutPort port);
    final string ComponentType() { return "CompatibilityComponent"; }
}

interface DataComponent
{
    enum{ USER = 0, ENGINE = 1 };
    @property
    {
        Data data();
        DataTypeInfo dataType();
        DataAccessFlag accessFlags();
        int ComponentFlags();
        DataComponent newSubDataComponent(int index);
        final string ComponentType() { return "DataComponent"; }
    }
}

class InputPortModifier
{
    this(InPort port)
    {
        _port = port;
    }
    
    bool rename(string newName)
    {
        if(_port._modifier !is this) return false;
        _port._name = newName;
        return true;
    }
    
    private InPort _port;
}

class OutputPortModifier
{
    this(OutPort port)
    {
        _port = port;
    }
    
    bool rename(string newName)
    {
        if(_port._modifier !is this) return false;
        _port._name = newName;
        return true;
    }
    private OutPort _port;
}
