module kiwi.dynamic.port;

import kiwi.core.commons;
import kiwi.core.all;





interface PortCompatibility
{
    bool isCompatible( OutputPort port ) pure;
}





class DynamicInputPort : InputPort
{
    this(Node n, PortCompatibility compatibility, int pflags = 0, string myName = "input")
    in
    {
        assert (compatibility !is null);
    }
    body
    {
        _node  = n;
        _flags = pflags;    
        _name  = myName;
        _compatibility = compatibility;
    }

    override{
        @property{           
            string name(){ return _name; }

            public PortFlags flags(){ return _flags; }
            protected void flags(PortFlags value){ _flags = value; }
            
            public Node node(){ return _node; } 
            protected void node(Node n){ _node = n; }

            public OutputPort connection() { return _connection; }
            protected void connection(OutputPort value) { _connection = value; }
    
        }
        
        bool isCompatible( OutputPort port )                
        {   
            mixin( logFunction!"DynamicInputPort.isCompatible" );
            return _compatibility.isCompatible( port ); 
        }
    }
    
private:
    PortFlags _flags;
    Node _node;
    string _name;    
    PortCompatibility _compatibility;
    OutputPort   _connection;
}






class DynamicOutputPort : OutputPort
{
    this(Node n
        , DynamicOutputPort parent
        , DataTypeInfo dataTypeInfo
        , PortFlags pflags
        , string myName = "output"
        , DataRef dataref = null )
    {
        mixin( logFunction!"DynamicOutputPort.constructor" );        
        _node       = n;
        _flags      = pflags;
        _name       = myName;
        _parentPort = parent;
        _dataType   = null;
        _subPorts   = [];

        if( dataref is null ) _dataRef = new BasicDataRef(null);
        else _dataRef = dataref;
        
        _setDataType( dataTypeInfo );
    }
    override{
        @property{
            /**
             * Returns the maximum amount of connections, or -1 if unlimited.
             */ 
            int maxConnections() { return -1; }

            /**
             * Returns this port's name
             */ 
            string name() { return _name; }
            /**
             * Returns an array containing references to this port's sub ports.
             */ 
            OutputPort[] subPorts() 
            {
                return _subPorts;
            }
            /**
             * returns a reference to this port's data type info.
             */ 
            DataTypeInfo dataType() pure { return _dataType; }

            public PortFlags flags(){ return _flags; }
            protected void flags(PortFlags value){ _flags = value; }
            
            public Node node(){ return _node; } 
            protected void node(Node n){ _node = n; }
        }

        protected ref InputPort[] refConnections()
        {
            return _connections;
        }
    
        /**
         * Returns true if this port is composite.
         */ 
        bool isComposite() 
        { 
            if(_dataType is null)
                return false;
            return _dataType.isComposite; 
        }

        /**
         * Returns true if port is compatible with this.
         */ 
        bool isCompatible( InputPort port ){ return (port !is null); }       // TODO: perform flag check   
                   
    }
    
    @property void dataRef( DataRef value ){ _dataRef = value; }
    @property DataRef dataRef(){ return _dataRef; }

protected:
    
    void _setDataType(DataTypeInfo dataTypeInfo)
    {
        if ( dataTypeInfo is _dataType ) return;

        foreach( p ; _subPorts)
            p.disconnectAll();

        _subPorts = [];
        _dataType = dataTypeInfo;
        if ( (dataTypeInfo !is null) && (dataTypeInfo.subData !is null) )
        {
            log.writeln(dataTypeInfo.name);
            log.writeln(dataTypeInfo.subData.length);
            
            foreach( subTypeInfo ; dataTypeInfo.subData )
            {
                log.writeDebug(0, subTypeInfo.name );
                _subPorts ~= new DynamicOutputPort( node, this, subTypeInfo, 0, "" );
            }
        }
    }
    
    void _setName(string newName){ _name = newName; }

    
private:
    Node                _node;
    PortFlags           _flags;
    string              _name;
    DataRef             _dataRef;  
    DataTypeInfo        _dataType;  
    DynamicOutputPort[] _subPorts;
    DynamicOutputPort   _parentPort;
    InputPort[]         _connections;
}









//              #######   #####    ####   #####    ####
//                 #      #       #         #     #   
//                 #      ###      ###      #      ### 
//                 #      #           #     #         #
//                 #      #####   ####      #     #### 





version(unittest)
{
    import kiwi.dynamic.compatibility;

    Data NewContainerTest()
    {
        return new ContainerTest();
    }

    class SubContainerTest : kiwi.core.base.Data
    {
        static this()
        {
            mixin( logFunction!"SubContainerTest.static_constructor" );
            _typeInfo = DataTypeManager.Register!SubContainerTest;
            assert( _typeInfo !is null );
            assert( DataTypeManager["SubContainerTest"] !is null);
            assert( DataTypeManager["SubContainerTest"] is _typeInfo );
        }
        override DataTypeInfo type(){ return _typeInfo; }
        static DataTypeInfo Type(){ return _typeInfo; }
        override @property Data[] subData(){ return []; }
        private static DataTypeInfo _typeInfo;
    } 

    class ContainerTest : kiwi.core.base.Data
    {
        mixin DeclareSubDataTypes!(SubContainerTest,SubContainerTest);

        static this()
        {
            mixin( logFunction!"ContainerTest.static_constructor" );
            _typeInfo = DataTypeManager.Register!ContainerTest;
            assert( _typeInfo !is null );
            assert( DataTypeManager["ContainerTest"] !is null);
            assert( DataTypeManager["ContainerTest"] is _typeInfo );
            assert( _typeInfo.name == "ContainerTest");
            assert( _typeInfo.subData.length == 2);
        }

        //override bool serialize( DataStream stream ){ return false; }
        //override bool deSerialize( const DataStream stream ){ return false; }
        override DataTypeInfo type(){ return _typeInfo; }
        static DataTypeInfo Type(){ return _typeInfo; }
        override @property Data[] subData(){ return []; }

    private static DataTypeInfo _typeInfo; 
    }
}



unittest
{
    mixin(logTest!"kiwi.dynamic.port");
    //beginTesting("kiwi.core");
    log.writeln( "ContainerTest.Type.name: ", ContainerTest.Type.name );
    assert( ContainerTest.Type.subData.length == 2 );
    assert( ContainerTest.Type.subData[0].name == "SubContainerTest" );

    auto op_1 = new DynamicOutputPort( null, null, ContainerTest.Type, 0 );
    auto ip_1 = new DynamicInputPort(  null, new AlwaysCompatible );

    auto op_2 = new DynamicOutputPort( null, null, ContainerTest.Type, 0 );
    auto ip_2 = new DynamicInputPort(  null, new AlwaysCompatible );

    // simply trying every connection/disconnection cases.

    assert( !(op_1 is null) && !(ip_1 is null) );
    assert( !op_1.isConnectedTo(ip_1) );
    assert( !ip_1.isConnectedTo(op_1) );
    assert( op_1.isComposite() );
    assert( op_1.connect(ip_1) );
    assert( op_1.isConnectedTo(ip_1) );
    assert( ip_1.isConnectedTo(op_1) );

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



