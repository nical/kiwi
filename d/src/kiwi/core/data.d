module kiwi.core.data;
//
import kiwi.core.commons;
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
    this(string name, DataTypeInfo[] subData, string[] subDataNames, bool serializable, NewDataFunction instanciator)
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









class DataTypeManager
{

    static DataTypeInfo Register( _Type )()
    out(result)
    { 
        assert( result !is null );
        assert( _dataTypes[result.name] is result ); 
    }
    body
    {
        mixin( logFunction!"DataTypeManager.Register" );

        static if ( __traits(compiles, name = _Type.Name) )
            string name = _Type.Name;
        else 
            string name = _Type.stringof;
        
        DataTypeInfo result;
        if ( Contains(name) )
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
                    DataTypeInfo temp = Register!subType;
                    subTypes ~= temp;                                    }
            }

            string[] subNames;

            // if the a name is provided for sub data types, use it
            static if( __traits(compiles, _type.SubDataNames) )
            {
                subNames = _type.SubDataNames;
            }
            else // if no name provided, use the sub type names by default
            {
                subNames.length = subTypes.length;
                for(int i = 0; i < subNames.length; ++i )
                {
                    subNames[i] = subTypes[i].name;
                }
            }
            
            static if( __traits(compiles, _Type.NewInstance) )
            {
                NewDataFunction instanciator = &_Type.NewInstance;
            }
            else
            {
                NewDataFunction instanciator = function Data()pure{ return new _Type; };
            }
            result = new DataTypeInfo(name, subTypes, subNames, false, instanciator);
            _dataTypes[name] = result;
            return result;
        }   
    }

    static Data Create( string key )
    {
        auto info = Get( key );
        if ( info !is null )
        {
           return info.newInstance(); 
        }
        else 
        {
            // TODO: return an exception instead
            return null;
        }
    }

    static bool Contains( string key )
    {
        foreach( existing ; _dataTypes.byKey )
          if ( existing == key )
            return true;
        return false;
    }

    static auto Keys()
    {
        return _dataTypes.keys;
    }


    static DataTypeInfo Get(string key)
    {
        return opIndex( key );
    }

    static DataTypeInfo opIndex( string key )
    {
        if( Contains(key) ) 
            return _dataTypes[key];
        else
            return null;
    }
    
private: 
    this(){ mixin( logFunction!"DataTypeManager.constructor"); }
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

//            #####   #####    ####   #####    ####
//              #     #       #         #     #
//              #     ###      ###      #      ###
//              #     #           #     #         #
//              #     #####   ####      #     ####




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
            _typeInfo = DataTypeManager.Register!DataTest;
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
    
    foreach( registeredKey ; DataTypeManager.Keys )
    {
        log.writeln(registeredKey);
    }
    assert ( DataTypeManager["DataTest"] !is null );
    assert ( DataTypeManager["DataTestSub"] !is null );
    assert ( DataTypeManager["unregistered"] is null );
}
