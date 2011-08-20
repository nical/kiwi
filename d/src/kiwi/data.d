module kiwi.data;
//
import kiwi.commons;
//
import std.typecons;




interface Data
{
    @property 
    {
        DataTypeInfo type();
        Data[] subData();
        //
        final bool isComposite(){ return subData.length != 0; } 
    }
    bool serialize( DataStream stream );
    bool deSerialize( const DataStream stream );
}

/++
 + Real time type information for kiwi data classes.
 +/ 
class DataTypeInfo
{
public:
  this(string name, const(DataTypeInfo)[] defaultSubData, bool serializable)
  {
    mixin(logFunction!"DataTypeInfo.constructor");
    _name = name;
    _subData = defaultSubData;
  }

  @property const string name()
  {
    return _name;
  }

  @property const(DataTypeInfo[]) subData()
  {
    return _subData;
  }

  bool isSerializable()
  {
    return _serializable;
  }

  bool isComposite()
  {
    if( _subData is null ){
      return false;
    }else{
      return _subData.length != 0;
    }
  }
  
private:
  string                 _name;
  const(DataTypeInfo)[]  _subData;
  bool                   _serializable;
}


class ContainerWrapper(dataType) : Data {
    alias dataType DataType;
    alias _data this;

    static this(){
        _typeInfo = new DataTypeInfo("ContainerWrapper", [], false);
    }

    override{
        //bool isSerializable(){ return false; }
        bool serialize( DataStream stream ){ return false; }
        bool deSerialize( const DataStream stream ){ return false; }
        @property Data[] subData(){ return []; }
        @property DataTypeInfo type(){ return _typeInfo; }        
    }
    @property static DataTypeInfo Type(){ return _typeInfo; }
    private DataType _data;
    private static DataTypeInfo _typeInfo;
}
