module kiwi.dynamic.DynamicObject;

import kiwi.core.commons;

alias DynamicObject function(DynamicObject, DynamicObject[]) FunctionPointer;
    

class DynamicObject
{
   
    auto opAssign(Object o)
    {
        _type = typeid(o).name;
        _object = o;
        _function = null;
        return this;
    }
    string type(){ return _type; }

    DynamicObject opCall(DynamicObject[] args = null)
    {
        if(_function is null)
            throw new Exception("DynamicObject "~_type~"is called but is not a function.");
        return _function(null, args);
    }
    
    DynamicObject opIndex(string name)
    {
        return _properties[name];
    }

    void opIndexAssign( DynamicObject obj, string name )
    {
        _properties[name] = obj;
    }

    DynamicObject opDispatch(string name)(DynamicObject[] args = null)
    {
        auto symbol = _properties[name];
        if(symbol._function !is null)
            return symbol._function( this, args );
        return symbol; 
    }
    
protected:
    string _type;
    DynamicObject[string] _properties;
    FunctionPointer _function;
    Object _object;
}

class Integer
{
    alias value this;
    int value;
}

class ObjWrapper(T)
{
    this(T val){ value = val; }
    alias T ValueType;
    alias value this;
    T value;

    bool opEqual( T val )
    {
        return value == val;
    }
}

DynamicObject Function( FunctionPointer fptr )
{
    auto result = new DynamicObject();
    result._type = "Function";
    result._function = fptr;
    result._object = null;
    return result;
}

DynamicObject Wrapper(T)(T value)
{
    auto result = new DynamicObject();
    result._type = T.stringof;
    result._function = null;
    result._object = new ObjWrapper!T(value);
    return result;
}

DynamicObject NewObject()
{
    auto result = new DynamicObject();
    result._type = "Object";
    result._function = null;
    result._object = null;
    return result;
}




DynamicObject f1(DynamicObject self, DynamicObject[] args)
{
    return Wrapper!int(42);
}

unittest
{    
    auto func = Function( &f1 );
    auto obj = NewObject();
    obj["method"] = func;
    obj["attribute"] = Wrapper!int(0);

    log.writeln("obj.type: ", obj.type);
    log.writeln("func().type: ", func().type);
    log.writeln("obj.method.type: ", obj.method.type);
    log.writeln("obj.method().type: ", obj.method().type);
    log.writeln("obj.attribute.type: ", obj.attribute.type);
    
    assert( func.type == "Function" );
    assert( obj["method"].type == "Function" ); 
    assert( obj["method"]().type == "int" ); 
    assert( obj.method.type == "int" );
    assert( obj.attribute.type == "int" );
    assert( obj.method(null).type == Wrapper!int(42).type );

    // T_T
    //
    //assert( obj.attribute == 0 );
    //obj.attribute++;
    //assert( obj.attribute == 1 );

}
