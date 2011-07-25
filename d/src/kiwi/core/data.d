module kiwi.core.data;

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
  
  struct DefaultPortLayout{
      
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
  
  struct CustomVariable{
    int type;
    float value;    
  }
  
  @property const(CustomVariable)[string] variables(){
    return _variables;
  }
  
private:
  string                 _name;
  const(DataTypeInfo)[]  _subData;
  bool                   _serializable;
  CustomVariable[string] _variables;
}
