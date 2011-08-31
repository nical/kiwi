module kiwi.dynamic.port;

import kiwi.core;
import kiwi.data;
import kiwi.commons;





interface PortCompatibility
{
    bool isCompatible( OutputPort port ) pure;
}





class DynamicInputPort : InputPort
{
    this(Node n, PortCompatibility compatibility, string myName = "input")
    in
    {
        assert (compatibility !is null);
    }
    body
    {
        super(n);    
        _name = myName;
        _compatibility = compatibility;
    }

    override{
        @property{
            int maxConnections(){ return -1; }
            string name(){ return _name; }
        }
        
        bool isCompatible( OutputPort port )                
        {   
            mixin( logFunction!"DynamicInputPort.isCompatible" );
            return _compatibility.isCompatible( port ); 
        }
    }

private:
    string _name;    
    PortCompatibility _compatibility;
}






class DynamicOutputPort : OutputPort
{
    this(Node n, DynamicOutputPort parent, DataTypeInfo dataTypeInfo, string myName = "output")
    {
        mixin( logFunction!"DynamicOutputPort.constructor" );
        super(n);
        _name       = myName;
        _parentPort = parent;
        _dataType   = dataTypeInfo;
        _subPorts   = [];
        
        if ( (dataTypeInfo !is null) && (dataTypeInfo.subData !is null) )
        {
            log.writeln(dataTypeInfo.name);
            log.writeln(dataTypeInfo.subData.length);
            
            foreach( subTypeInfo ; dataTypeInfo.subData )
            {
                log.writeDebug(0, subTypeInfo.name );
                _subPorts ~= new DynamicOutputPort( n, this, subTypeInfo, "" );
            }
        }
    }
    override{
        @property{
            int maxConnections() { return -1; }
            string name() { return _name; }
            OutputPort[] subPorts() { return []; }
            DataTypeInfo dataType() pure { return _dataType; }
            Data data(){ return _data; }
        }

        bool isComposite() { return false; }
        bool isCompatible( InputPort port ){ return (port !is null); }         
                   
    }
    @property void data( kiwi.core.Data value ){ _data = value; }
private:
    string              _name;
    Data                _data;  
    DataTypeInfo        _dataType;  
    DynamicOutputPort[] _subPorts;
    DynamicOutputPort   _parentPort;
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

    class SubContainerTest : kiwi.core.Data
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

    class ContainerTest : kiwi.core.Data
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

    auto op_1 = new kiwi.dynamic.port.DynamicOutputPort( null, null, ContainerTest.Type );
    auto ip_1 = new kiwi.dynamic.port.DynamicInputPort(  null, new AlwaysCompatible );

    auto op_2 = new kiwi.dynamic.port.DynamicOutputPort( null, null, ContainerTest.Type );
    auto ip_2 = new kiwi.dynamic.port.DynamicInputPort(  null, new AlwaysCompatible );

    // simply trying every connection/disconnection cases.

    assert( !(op_1 is null) && !(ip_1 is null) );
    assert( !op_1.isConnectedTo(ip_1) );
    assert( !ip_1.isConnectedTo(op_1) );
    assert( !op_1.isComposite() );
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
    assert( op_1.isConnectedTo(ip_1) );

    assert( op_2.disconnect(ip_1) );

    assert( !op_2.isConnectedTo(ip_1) );
    assert( op_1.isConnectedTo(ip_1) );

    assert( ip_1.connect(op_2) );

    assert( op_2.isConnectedTo(ip_1) );
    assert( op_1.isConnectedTo(ip_1) );
}



