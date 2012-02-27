module kiwi.core.runtimetype;

import std.c.string;
import kiwi.core.commons;

private template maxSize(T...)
{
    static if (T.length == 1)
    {
        enum size_t maxSize = T[0].sizeof;
    }
    else
    {
        enum size_t maxSize = T[0].sizeof >= maxSize!(T[1 .. $])
            ? T[0].sizeof : maxSize!(T[1 .. $]);
    }
}

class RuntimeTypeException : Exception
{
    this(string s) 
    {
        super(s);
    }
}

struct RuntimeType 
{

    this(T)(T value)
    {
        static if (is(T==TypeInfo) || is(T==const(TypeInfo)) )
        {
            type = cast(TypeInfo) value;
            //log.writeln("RuntimeType.this(TypeInfo)");
        }
        else
        {
            opAssign(value);
            //log.writeln("RuntimeType.this!T(T)");
        }
    }
    
    RuntimeType opAssign(T)(T value) if( !is(T == RuntimeType) )
    {
        static assert ( T.sizeof <= BUF_SIZE, "Object too big, use reference or pointer instead." );
        if ( !_dataType )
            _dataType = typeid(T);
        if ( typeid(T) == _dataType )
        {
            ptr[0] = *(cast(void**) &value);
            return this;
        }
        throw new RuntimeTypeException("uncompatible types.");
    }
    
    RuntimeType opAssign(T)(T value) if( is(T == RuntimeType) )
    {
        if ( _dataType is null )
            _dataType = value._dataType;
        if ( _dataType == value._dataType )
        {
            //ptr[0] = *value.peek!void; // todo memcpy instead 
            memcpy( &ptr[0], value.peek!void, BUF_SIZE );
            assert(memcmp(value.peek!void, peek!void, BUF_SIZE) == 0);
            return this;
        }
        throw new RuntimeTypeException("uncompatible types.");
    }
    
    bool opEquals(T)(T rhs) const
    {
        static if (is(T == RuntimeType))
        {
            if ( !this.hasType  || !rhs.hasType )
                return false;
            return (_dataType == rhs._dataType) 
                && (memcmp(rhs.peek!void, peek!void, BUF_SIZE) == 0);
        }
        else
        {
            return isA!T && (rhs == get!T);
        }
    }
    
    /++
     + For now only the kiwi.core package can change the type.
     +/ 
    package void clear()
    {
         for(int i = 0; i < BUF_SIZE; ++i) buf[i] = 0;
         //ptr[0] = cast(void*)null;
         _dataType = null;
    }
    
    @property
    {
        ref inout(T) get(T)() inout
        {
            if ( typeid(T) == _dataType )
            {
                return *(cast(inout(T)*) &buf[0]);
            }
            throw new RuntimeTypeException("uncompatible types.");
        }

        inout(T)* peek(T)() inout  
        {
            static if ( is(T == void) )
            {
                return (cast(inout(T)*) &buf[0]);
            }
            else
            {
                if ( typeid(T) == _dataType )
                {
                    return (cast(inout(T)*) &buf[0]);
                }
                return null;
            }
        }
        
        bool isA(T)() const
        {
            return _dataType == typeid(T);
        }
        
        bool hasType() const pure
        {
            return _dataType !is null;
        }

        const(TypeInfo) type() const
        {
            return _dataType;
        }

        /++
         + For now only the kiwi.core package can change the type.
         +/ 
        package void type( const TypeInfo t )
        {
            if (_dataType != t)
            {
                clear();
                _dataType = cast(TypeInfo)t;
            }
        }
    }// properties

private:
    enum BUF_SIZE = maxSize!(maxSize!(void*,creal, char[], void delegate()));
    
    TypeInfo _dataType; // const
    union {
        ubyte[BUF_SIZE] buf;
        //void* ptr[BUF_SIZE / sizeof(void*)];
        void* ptr[BUF_SIZE / (void*).sizeof];
    }
    
}


unittest
{
    import kiwi.utils.testing;
    
    auto unit = TestSuite("kiwi.core.RuntimeType");
    
    RuntimeType a;
    RuntimeType b;
    

    
    unit.test( a.type is null );
    unit.test( b.type is null );
    
    b = cast(float) 3.14;
    unit.test( b.isA!float );
    
    a.type = typeid(int);
    unit.test( a.type == typeid(int) );
    
    a = cast(int) 10;
    
    try{ b = 10; unit.test(false); } catch( RuntimeTypeException e ){ }
    
    b.clear();
    
    b = a;
    unit.test( a.type == b.type );
    unit.test( a.get!int == b.get!int );
    unit.test( b == a );
    
    unit.test( a._dataType == typeid(int) );
    unit.test( a.isA!int );
    
    unit.test( a.get!int == 10 );
    unit.test( a == cast(int)10 );
    unit.test( a != cast(int)20 );
    unit.test( a != 12.5 );

    a.get!int++;
    unit.test( a.get!int == 11 );
    
    a.type = typeid(float*);
    
    unit.test( a.get!(float*) == null );
    unit.test( a.isA!(float*) );
    
    unit.test( a.peek!char == null );
    unit.test( a.peek!(float*) != null );
    unit.test( a.peek!void != null );
        
}
