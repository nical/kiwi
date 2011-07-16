module kiwi.core.data;
import std.typecons;


/++
 + Real time type information for kiwi data classes.
 +/ 
class DataTypeInfo{
public:
  this(string name, const(DataTypeInfo)[] defaultSubData, bool serializable){
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
  
private:
  string                _name;
  const(DataTypeInfo)[] _subData;
  bool                  _serializable;
}


//------------------------------------------------------------------------------




/*
class ContainerManager{
public:
  int registerContainer(ContainerType)(){
    static if( is(ContainerType == AbstractContainer) ){
      return 0; // special case;
    }else{
      if( ContainerType.classId != 0 ){
        int baseId;
        static if( is(ContainerType.BaseClass == AbstractContainer) ){
          baseId = 0;
        }else{
          baseId = this.registerContainer!(ContainerType.BaseClass)();
        }
        int[] subContainers;
        foreach( subC ; ContainerType.SubContainerClasses ){
          subContainers ~= registerContainer!(subC)();
        }
        _containerInfo ~= ContainerInfo(
          ContainerType.className, baseId, subContainers );
        ContainerType.classId = _containerInfo.size -1;
      }
      return ContainerType.classId;
    }
  }

private:
  ContainerInfo[] _containerInfo;
protected:
}

*/
