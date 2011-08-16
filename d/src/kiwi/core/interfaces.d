module kiwi.core.interfaces;

import kiwi.core.commons;
import kiwi.core.data;

//alias bool delegate(InputPort,OutputPort) PortCompatibilityPolicy;




interface DataInterface{
    final bool isComposite(){
        if( subData is null ){ 
            return false;
        }else{
            return subData.length != 0;
        }
    }
    bool isSerializable();
    bool serialize( DataStream stream );
    bool deSerialize( const DataStream stream );
    @property const(DataInterface[]) subData();
    abstract DataTypeInfo typeInfo();
  
}



// -----------------------------------------------------------------------------


