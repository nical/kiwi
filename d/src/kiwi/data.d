module kiwi.data;
//
import kiwi.commons;
//
import std.typecons;
import std.traits;

alias Data function() pure NewDataFunction;

interface Data
{
    @property 
    {
        DataTypeInfo type();
        Data[] subData();
        //
        final bool isComposite(){ return subData.length != 0; } 
    }
    //bool serialize( DataStream stream );
    //bool deSerialize( const DataStream stream );
}

/++
 + Real time type information for kiwi data classes.
 +/
class DataTypeInfo
{
public:
    this(string name, DataTypeInfo[] subData, bool serializable, NewDataFunction instanciator)
    {
        mixin(logFunction!"DataTypeInfo.constructor");
        _name = name;
        _subData = subData;
        _serializable = serializable;
        _newData = instanciator;
    }

    @property{ 
        const string name() pure
        {
            return _name;
        }

        DataTypeInfo[] subData() pure
        {
            return _subData;
        }

        bool isSerializable() pure
        {
            return _serializable;
        }

        bool isComposite() pure
        {
            if( _subData is null ){
                return false;
            }else{
                return _subData.length != 0;
            }
        }
    } // properties

    /++
     + Instanciate an object of this type.
     +/
    Data newInstance() pure
    in{ assert( _newData !is null ); }
    body
    {
        return _newData();
    }
private:
    string                 _name;
    DataTypeInfo[]  _subData;
    bool                   _serializable;
    NewDataFunction        _newData;
}



class ContainerWrapper(dataType) : Data {
    alias dataType DataType;
    alias _data this;
    

    static this(){
        _typeInfo = new DataTypeInfo("ContainerWrapper", [], false);
    }

    override{
        //bool isSerializable(){ return false; }
        //bool serialize( DataStream stream ){ return false; }
        //bool deSerialize( const DataStream stream ){ return false; }
        @property Data[] subData(){ return []; }
        @property DataTypeInfo type(){ return _typeInfo; }        
    }
    @property static DataTypeInfo Type(){ return _typeInfo; }
    private DataType _data;
    private static DataTypeInfo _typeInfo;
}







class DataTypeManager
{

    static DataTypeInfo registerDataType( _Type )()
    out(result)
    { 
        assert( result !is null );
        assert( _dataTypes[result.name] is result ); 
    }
    body
    {
        mixin( logFunction!"DataTypeManager.registerDataType" );

        static if ( __traits(compiles, name = _Type.Name) )
            string name = _Type.Name;
        else 
            string name = _Type.stringof;
        
        log.writeln( name );

        DataTypeInfo result;
        if ( contains(name) )
        {
            log.writeDebug(0,"already registered.");
            return _dataTypes[name];
        }
        else
        {
            DataTypeInfo[] subTypes = [];
            static if( __traits(compiles, _Type.SubDataTypes) )
            {
                log.writeDebug(0,"has sub data type");
                log.writeDebug(0, subTypes.length );
                foreach( subType ; _Type.SubDataTypes ){
                    DataTypeInfo temp = registerDataType!subType;
                    subTypes ~= temp;                                    }
            }            
            
            static if( __traits(compiles, _Type.NewInstance) )
            {
                NewDataFunction instanciator = &_Type.NewInstance;
            }
            else
            {
                NewDataFunction instanciator = function Data()pure{ return new _Type; };
            }
            log.plop;
            log.writeDebug(0,"subTypes: ", subTypes.length);
            if(subTypes.length > 0) log.writeDebug(0,"subTypes[0]: ", subTypes[0].name);
            result = new DataTypeInfo(name, subTypes, false, instanciator);
            if(subTypes.length > 0) log.writeDebug(0,"result.subData[0]: ", result.subData[0].name);
            _dataTypes[name] = result;
            return result;
        }   
    }

    static bool contains( string key )
    {
        foreach( existing ; _dataTypes.byKey )
          if ( existing == key )
            return true;
        return false;
    }

    static auto keys() { return _dataTypes.keys; }

    static DataTypeInfo opIndex( string key )
    {
        if( contains(key) ) 
            return _dataTypes[key];
        else
            return null;
    }
    
private: 
    this(){ mixin( logFunction!"DataTypeManager.constructor");}
    static DataTypeInfo[string] _dataTypes;
}





mixin template DeclareSubDataTypes(T...)
{
    alias T SubDataTypes;
}

mixin template DeclareName(alias name)
{
    alias name Name;
}

mixin template DeclareInstanciator(alias func)
{
    alias func NewInstance;
}

template DefineInstanciator(T) // wont work because mixin evaluated too late
{
    enum{ functionText = "kiwi.Data New"~T.stringof~"(){ return new "~T.stringof~";}" }
    string DefineInstanciator = functionText;
}

/*
             #####   #####    ####   #####    ####
               #     #       #         #     #
               #     ###      ###      #      ###
               #     #           #     #         #
               #     #####   ####      #     ####
*/



version(unittest)
{
    
    Data NewDataTest() pure { return new DataTest; }

    class DataTestSub : Data
    {
        override{
            //bool serialize( DataStream stream ){ return false; }
            //bool deSerialize( const DataStream stream ){ return false; }
            @property Data[] subData(){ return []; }
            @property DataTypeInfo type(){ return null; }        
        }

    }

    class DataTest : Data
    {
        mixin DeclareName!("DataTest");
        mixin DeclareSubDataTypes!(DataTestSub,DataTestSub);
        mixin DeclareInstanciator!(NewDataTest);

        static this()
        {
            mixin( logFunction!"unittest.DataTest.static_constructor" );
            _typeInfo = DataTypeManager.registerDataType!DataTest;
        }

        override{
            //bool serialize( DataStream stream ){ return false; }
            //bool deSerialize( const DataStream stream ){ return false; }
            @property Data[] subData(){ return []; }
            @property DataTypeInfo type(){ return _typeInfo; }        
        }
        @property static DataTypeInfo Type(){ return _typeInfo; }
        private static DataTypeInfo _typeInfo;
    }

}

unittest
{
    mixin( logTest!"kiwi.data" ); 
    
    foreach( registeredKey ; DataTypeManager.keys )
    {
        log.writeln(registeredKey);
    }
    assert ( DataTypeManager["DataTest"] !is null );
    assert ( DataTypeManager["DataTestSub"] !is null );
    assert ( DataTypeManager["unregistered"] is null );
}