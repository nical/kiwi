module kiwi.core.port;

import kiwi.core.data;
import kiwi.core.container;
import kiwi.core.node;
import kiwi.core.commons;
import kiwi.core.datastrategy;

class OutputPort
{
    this(string name, Node n, DataStrategy dataStrategy )
    {
        _node = n;
        _parent = null;
        _name = name;
        _setDataStrategy(dataStrategy); 
    }
    
    @property
    {
        Node node()
        {
            return _node;
        }

        bool hasDataStrategy() const
        {
            return _dataStrategy !is null;
        }
        
        bool isComposite() const // TODO
        {
            return false;
        }

        bool isSubPort()
        {
            return _parent !is null;
        }

        DataTypeInfo dataType()
        {
            if ( this.hasDataStrategy() ) return _dataStrategy.dataType;
            else return null;
        }

        Data data()
        {
            if ( hasDataStrategy ) return _dataStrategy.data;
            else return null;
        }

        DataAccessFlag accessFlags() const
        {
            if ( hasDataStrategy ) return _dataStrategy.accessFlags;
            else return 0;
        }

        string name() const
        {
            return _name;
        }

        InputPort[] connections()
        {
            return _connections;
        }

        void disconnectAll()
        {
            for(int i = 0; i < _connections.length; ++i)
                this.disconnect(_connections[i]);
        }

        bool isConnected()
        {
            return _connections.length != 0;
        }
        
    } // properties

    T dataAs(T)()
    {
        Data x;
        static if ( __traits(compiles, x = new T ) )
            return cast(T)data;
        else
            return ( (cast(Container!T)data).value );
    }
    
    bool isCompatible( InputPort port )
    {
        return port.isCompatible(this);
    }

    bool isConnectedTo( InputPort port ) const
    {
        foreach( p ; _connections)
        {
            if( p is port) return true;
        }
        return false;
    }   

    bool connect(InputPort port)
    {
        if ( port is null )
            return false;
        return port.connect(this);
    }

    bool disconnect( InputPort port )
    {
        if(port is null)
                return false;
            
        return port.disconnect(this);
    }

    final bool opBinary(string op)(InputPort port) if (op == ">>")
    {
        return connect( port );
    }

    
protected:
    /++
     + Returns the index of an output port in connections, or -1 if not found.
     +/ 
    protected int indexOf(InputPort port)
    {
        for(int i = 0; i < connections.length; ++i){
            if( connections[i] is port )
                return i;
        }
        return -1;
    }

    void _setDataStrategy(DataStrategy component)
    {
        mixin( logFunction!"OutputPort._setDataStrategy" );
        if ( component is _dataStrategy ) return;

        _dataStrategy = component;
    }
private:

    Node    _node;
    string  _name;
    InputPort[] _connections;
    OutputPort _parent; // deprecated
    
    // components
package DataStrategy _dataStrategy;
    //PortInfoStrategy   _portInfoStrategy;
    
}




class InputPort
{
    this(string portName, Node n, CompatibilityStrategy comp
        , DataAccessFlag flags = READ, bool optional = false)
    {
        _name = portName;
        _node = n;
        _compatibilityStrategy = comp;
        _accessFlags = flags;
        _optional = optional;
    }
    
    @property
    {

        Node node()
        {
            return _node;
        }

        string name()
        {
            return _name;
        }   

        Data data()
        {
            if (isConnected) return _connection.data;
            return null; 
        }
            
        DataAccessFlag accessFlags() const
        {
            return _accessFlags;
        }

        OutputPort connection()
        {
            return _connection;
        }

        bool isConnected() const
        {
            return _connection !is null;
        }

        bool isOptional() const
        {
            return true;
        }
        
        bool hasCompatibilityStrategy() const
        {
            return _compatibilityStrategy !is null;
        }

        bool isOptional()
        {
            return _optional;
        }
    }

    bool isCompatible( OutputPort port )
    {
        mixin( logFunction!"InputPort.isCompatible" );
        if ( !( accessFlags & port.accessFlags) && accessFlags != 0 )
        {
            log.writeDebug(3,"incompatible flags ", accessFlags, " ", port.accessFlags, "\n" );
            return false;
        }
        if ( hasCompatibilityStrategy )
            return _compatibilityStrategy.isCompatible(this, port);
        return true;
    }

    T dataAs(T)()
    {
        static if ( __traits(compiles, cast(T)data ) )
            return cast(T)data;
        else
            return ( (cast(ContainerWrapper!T)data).value );
    }

    bool isConnectedTo( OutputPort port ) const
    {
        return _connection is port;
    }

    bool connect(OutputPort port)
    {
        mixin( logFunction!"InputPort.connect" );
        
        if (port is null)
            return false;

        if ( !isCompatible(port) )
            return false;

        if( this.isConnected ) disconnect();
        
        this._connection = port;
        port._connections ~= this;
        log.writeDebug(0,"connected");
        return true;
    }

    /++
     + Disconnect this port from an OutputPort if they are conected.
     +/ 
    bool disconnect( OutputPort port = null)
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
    bool _optional;
    OutputPort _connection;
    // components
    CompatibilityStrategy  _compatibilityStrategy;
    //PortInfoStrategy       _portInfoStrategy;
}



// ---------------------------


interface DataStrategy
{
    enum{ USER = 0, ENGINE = 1 };
    @property
    {
        Data data();
        DataTypeInfo dataType();
        DataAccessFlag accessFlags() const;
        int componentFlags() const;
        final string StrategyType() const { return "DataStrategy"; }
    }
        
}



interface CompatibilityStrategy
{
    bool isCompatible(InputPort self, OutputPort port);
    final string StrategyType() { return "CompatibilityStrategy"; }
}


class DataTypeCompatibility : CompatibilityStrategy
{
	this(DataTypeInfo[] compatibleTypes)
	{
		_compatibleTypes = compatibleTypes;
	}
	
	this(DataTypeInfo compatibleType)
	{
		_compatibleTypes ~= compatibleType;
	}

	override bool isCompatible(InputPort self, OutputPort port)
	in
	{
		assert ( port !is null);
	}
	body
	{	
		foreach ( typeInfo ; _compatibleTypes )
		{
			if (port.dataType is typeInfo)
				return true;
		}
		return false;
	}

private:
	DataTypeInfo[] _compatibleTypes;
}


/**
 * Runtime compatibility policy for kiwi.dynamic.InputPort objects, always compatible.
 */
class AlwaysCompatible : CompatibilityStrategy
{
	override bool isCompatible(InputPort self, OutputPort port)
	in
	{
		assert ( port !is null);
	}
	body
	{
        mixin( logFunction!"AlwaysCompatible.isCompatible" );
		return true;
	}
}

/**
 * Runtime compatibility policy for kiwi.dynamic.InputPort objects, never compatible.
 */
class NeverCompatible : CompatibilityStrategy
{
	override bool isCompatible(InputPort self, OutputPort port)
	in
	{
		assert ( port !is null);
	}
	body
	{
		return false;
	}
}




//            #####   #####    ####   #####    ####
//              #     #       #         #     #
//              #     ###      ###      #      ###
//              #     #           #     #         #
//              #     #####   ####      #     ####



version(unittest)
{
    import kiwi.core.datastrategy;

    Data NewContainerTest()
    {
        return new ContainerTest();
    }

    class SubContainerTest : Data
    {
        static this()
        {
            mixin( logFunction!"SubContainerTest.static_constructor" );
            _typeInfo = DataTypeManager.Register!SubContainerTest;
            assert( _typeInfo !is null );
            assert( DataTypeManager["kiwi.core.port.SubContainerTest"] !is null);
            assert( DataTypeManager["kiwi.core.port.SubContainerTest"] is _typeInfo );
        }
       
        override DataTypeInfo type(){ return _typeInfo; }
        static DataTypeInfo Type(){ return _typeInfo; }
        override @property Data[] subData(){ return []; }
        private static DataTypeInfo _typeInfo;
       
    } 

    class ContainerTest : Data
    {
        mixin DeclareSubDataTypes!(SubContainerTest,SubContainerTest);

        
        invariant()
        {
            assert( _subData.length == 2 );   
        }

        this()
        {
            _subData ~= new SubContainerTest();
            _subData ~= new SubContainerTest();
        }

        static this()
        {
            mixin( logFunction!"ContainerTest.static_constructor" );
            _typeInfo = DataTypeManager.Register!ContainerTest;
            assert( _typeInfo !is null );
            assert( DataTypeManager["kiwi.core.port.ContainerTest"] !is null);
            assert( DataTypeManager["kiwi.core.port.ContainerTest"] is _typeInfo );
            assert( _typeInfo.name == "kiwi.core.port.ContainerTest");
            assert( _typeInfo.subData.length == 2);
        }

        //override bool serialize( DataStream stream ){ return false; }
        //override bool deSerialize( const DataStream stream ){ return false; }
        override DataTypeInfo type(){ return _typeInfo; }
        static DataTypeInfo Type(){ return _typeInfo; }
        override @property Data[] subData(){ return _subData; }
        
    private Data[] _subData;
    private static DataTypeInfo _typeInfo; 
    }
}



unittest
{
    mixin(logTest!"kiwi.core.port");
    
    log.writeln( "ContainerTest.Type.name: ", ContainerTest.Type.name );
    assert( ContainerTest.Type.subData.length == 2 );
    assert( ContainerTest.Type.subData[0].name == "kiwi.core.port.SubContainerTest" );

    auto op_1 = new OutputPort( "op_1", null, new UserAllocatedDataStrategy( new ContainerTest, READ ) );
    auto ip_1 = new InputPort(  "ip_1", null, new AlwaysCompatible );

    auto op_2 = new OutputPort( "op_1", null, new UserAllocatedDataStrategy( new ContainerTest, READ ) );
    auto ip_2 = new InputPort(  "ip_2", null, new AlwaysCompatible );

    // simply trying every connection/disconnection cases.

    assert( !(op_1 is null) && !(ip_1 is null) );
    assert( !op_1.isConnectedTo(ip_1) );
    assert( !ip_1.isConnectedTo(op_1) );
    //assert( op_1.isComposite() ); // TODO
    assert( op_1.connect(ip_1) );
    assert( ip_1.isConnectedTo(op_1) );
    assert( op_1.isConnectedTo(ip_1) );
    assert( op_1.isConnected() );
    assert( ip_1.isConnected() );

    assert( op_1.disconnect(ip_1) );
    assert( !op_1.disconnect(ip_1) ); // should fail and return false without crash
    assert( !ip_1.disconnect(op_1) ); // should fail and return false without crash

    assert( !op_1.isConnectedTo(ip_1) );
    assert( !ip_1.isConnectedTo(op_1) );

    assert( ip_1.connect(op_1) );
    assert( op_1.isConnectedTo(ip_1) );
    assert( ip_1.isConnectedTo(op_1) );

    assert( ip_1.disconnect(op_1) );
    assert( !op_1.isConnectedTo(ip_1) );
    assert( !ip_1.isConnectedTo(op_1) );

    // multiple connections
    assert( op_1.connect(ip_1) );
    assert( op_2.connect(ip_1) );

    assert( op_2.isConnectedTo(ip_1) );
    assert( !op_1.isConnectedTo(ip_1) );

    assert( op_2.disconnect(ip_1) );

    assert( !op_2.isConnectedTo(ip_1) );
    assert( !op_1.isConnectedTo(ip_1) );

    assert( ip_1.connect(op_2) );

    assert( op_2.isConnectedTo(ip_1) );
    assert( !op_1.isConnectedTo(ip_1) );
}


