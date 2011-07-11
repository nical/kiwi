module kiwi.core.data;
import std.typecons;

//import kiwi.mpl.Tuple;

//------------------------------------------------------------------------------
class AbstractContainer{
public:
  static immutable string className = "AbstractContainer";
  static int classId = 0;   
  alias Object BaseClass;
  alias Tuple!() SubContainerClasses;
}

//------------------------------------------------------------------------------


struct ContainerInfo{
  string name;
  int baseClassId;
  int[] subContainerClassesId;
}


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
