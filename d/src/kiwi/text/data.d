module kiwi.text.data;

import kiwi.core.all;


Data NewPlainTextContainer(){ return new PlainTextContainer; }

class PlainTextContainer : kiwi.core.base.Data
{
    static this(){
        _typeInfo = DataTypeManager.Register!PlainTextContainer();
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
        @property kiwi.core.base.Data[] subData(){ return []; }
        
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
