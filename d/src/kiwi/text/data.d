module kiwi.text.data;

import kiwi.core;
import kiwi.commons;
import kiwi.data;


Data NewPlainTextContainer(){ return new PlainTextContainer; }

class PlainTextContainer : kiwi.core.Data
{
    static this(){
        _typeInfo = DataTypeManager.registerDataType!PlainTextContainer();
        //_typeInfo = new DataTypeInfo("PlainText",null,true, &NewPlainTextContainer);        
    }

    this(){
        text = "";
    }

    this(string init){
        text = init;
    }

    override{
        //bool serialize(DataStream stream){ return false; }
        //bool deSerialize(const DataStream stream){ return false; }
        @property kiwi.core.Data[] subData(){ return []; }
        
        DataTypeInfo type(){ return _typeInfo; }
    }
    
    static DataTypeInfo Type(){
        return _typeInfo;
    }

    alias text this;
    string text;
private:
    
    static DataTypeInfo _typeInfo;
}
