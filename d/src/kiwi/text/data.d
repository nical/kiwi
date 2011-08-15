module kiwi.text.data;

import kiwi.core.commons;
import kiwi.core.interfaces;
import kiwi.core.data;

class PlainTextContainer : DataInterface
{
    static this(){
        _typeInfo = new DataTypeInfo("PlainText",null,true);        
    }

    this(){
        textData = [];
    }

    this(string init){
        textData = init;
    }

    override{
        bool isSerializable(){ return true; }
        bool serialize(DataStream stream){ return false; }
        bool deSerialize(const DataStream stream){ return false; }
        @property const(DataInterface[]) subData(){ return []; }
        
        DataTypeInfo typeInfo(){ return _typeInfo; }
    }
    
    DataTypeInfo TypeInfo(){
        return _typeInfo;
    }

    alias textData this;
    string textData;
private:
    
    static DataTypeInfo _typeInfo;
}
