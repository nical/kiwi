module kiwi.core.container;

import kiwi.core.commons;
import kiwi.core.node;
import kiwi.core.data;
import kiwi.core.datastrategy;



class Container(dataType) : Data {
    alias dataType DataType;
    alias _data this;
    alias dataType IsContainerWrapper;
    

    static this(){
        _typeInfo = new DataTypeInfo("ContainerWrapper"
            , [], []
            , false, function Data(){ return new Container!dataType; }
        );
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
