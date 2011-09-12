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
        super(n, pflags);    
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

protected:
    void setFlags(int pflags)
    {
        
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
        _dataType   = null;
        _subPorts   = [];
        _dataRef = new DataRef(null);
        
        setDataTypeInfo( dataTypeInfo );
    }
    override{
        @property{
            int maxConnections() { return -1; }
            string name() { return _name; }
            OutputPort[] subPorts() 
            {
                return _subPorts;
            }
            DataTypeInfo dataType() pure { return _dataType; }            
        }

        bool isComposite() 
        { 
            if(_dataType is null)
                return false;
            return _dataType.isComposite; 
        }
        bool isCompatible( InputPort port ){ return (port !is null); }         
                   
    }
    @property void dataRef( DataRef value ){ _dataRef = value; }
    @property DataRef dataRef(){ return _dataRef; }

protected:

    void setDataTypeInfo(DataTypeInfo dataTypeInfo)
    {
        if ( dataTypeInfo is _dataType ) return;
        _subPorts = [];
        _dataType = dataTypeInfo;
        if ( (dataTypeInfo !is null) && (dataTypeInfo.subData !is null) )
        {
            log.writeln(dataTypeInfo.name);
            log.writeln(dataTypeInfo.subData.length);
            
            foreach( subTypeInfo ; dataTypeInfo.subData )
            {
                log.writeDebug(0, subTypeInfo.name );
                _subPorts ~= new DynamicOutputPort( node, this, subTypeInfo, "" );
            }
        }
    }
private:
    string              _name;
    DataRef             _dataRef;  
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

    auto op_1 = new DynamicOutputPort( null, null, ContainerTest.Type );
    auto ip_1 = new DynamicInputPort(  null, new AlwaysCompatible );

    auto op_2 = new DynamicOutputPort( null, null, ContainerTest.Type );
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



