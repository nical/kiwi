module kiwi.core.container;

import kiwi.core.commons;
import kiwi.core.node;
import kiwi.core.data;
import kiwi.core.datastrategy;



class Container(dataType) : Data {
    alias dataType DataType;
    alias value this;

    enum { _Name = dataType.stringof~"Container" };
    mixin DeclareName!_Name;
    

    static this()
    {
        log.writeDebug(3, dataType.stringof~"Container" );
        _typeInfo = DataTypeManager.Register!(Container!DataType);
    }

    this(){}
    this( DataType initvalue )
    {
        value = initvalue;
    }

    override{
        //bool isSerializable(){ return false; }
        //bool serialize( DataStream stream ){ return false; }
        //bool deSerialize( const DataStream stream ){ return false; }
        @property Data[] subData(){ return []; }
        @property DataTypeInfo type(){ return _typeInfo; }        
    }
    
    @property static DataTypeInfo Type(){ return _typeInfo; }

    public DataType value;

    private static DataTypeInfo _typeInfo;
}

NodeTypeInfo RegisterContainerNode( const DataTypeInfo dataType )
{
    return NodeTypeManager.Register(dataType.name,"Processing",NodeTypeInfo.CONTAINER
        , delegate(){ return NewContainerNode( dataType ); }
        , null );
}

Node NewContainerNode( const DataTypeInfo dataType, DataAccessFlag accessFlags = READ_WRITE )
in{ assert( dataType !is null ); }
body
{
    auto typeInfo = NodeTypeManager[dataType.name, NodeTypeInfo.CONTAINER];
    return new Node
    (
        typeInfo, // 
        [ ],
        [ DeclareOutput("data", new UserAllocatedDataStrategy(
            dataType.newInstance(), accessFlags)) ],
        null
    );
}

Node NewContainerNode( Data data, DataAccessFlag accessFlags = READ_WRITE )
in{ assert( data !is null ); }
body
{
    auto typeInfo = NodeTypeManager[data.type.name, NodeTypeInfo.CONTAINER];
    return new Node
    (
        typeInfo, // 
        [ ],
        [ DeclareOutput("data", new UserAllocatedDataStrategy(data, accessFlags)) ],
        null
    );
}
