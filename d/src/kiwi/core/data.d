module kiwi.core.data;

import kiwi.core.interfaces;
import kiwi.core.commons;

import std.typecons;


/++
 + Real time type information for kiwi data classes.
 +/ 
class DataTypeInfo{
public:
  this(string name, const(DataTypeInfo)[] defaultSubData, bool serializable){
    mixin(logFunction!"DataTypeInfo.constructor");
    _name = name;
    _subData = defaultSubData;
  }
  
  @property const string name(){
    return _name;
  }
  
  @property const(const(DataTypeInfo)[]) subData(){
    return _subData;
  }
  
  bool isSerializable(){
    return _serializable;
  }
  
  bool isComposite(){
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


class ContainerWrapper(dataType) : DataInterface {
    alias dataType DataType;
    alias _data this;

    static this(){
        _typeInfo = new DataTypeInfo("ContainerWrapper", [], false);
    }

    override{
        bool isSerializable(){ return false; }
        bool serialize( DataStream stream ){ return false; }
        bool deSerialize( const DataStream stream ){ return false; }
        @property const(DataInterface[]) subData(){ return []; }
        DataTypeInfo typeInfo(){ return _typeInfo; }
    }
    private DataType _data;
    private static DataTypeInfo _typeInfo;
}
