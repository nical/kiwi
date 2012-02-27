module kiwi.utils.hstring;

uint StrHashFunction(string str) pure
{
    uint hash = 0;
    foreach(c;str)
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}

uint StrHashFunction2(string str) pure
{
    uint hash = 0;
    foreach(c;str)
    {
        hash ^= c;
        hash *= 0x93;
    }
    return hash;
}

alias HString StrHash;

template CompileHash(string str)
{
    enum { HString CompileHash = HString( str ) };
}

struct HString
{
    this( string str )
    {
        hash = StrHashFunction(str);
        debug{ debug_str = str; }

    }
    
    HString opAssign( string str )
    {
        HString s;
        s.hash = StrHashFunction(str);
        debug{ s.debug_str = str; }
        
        return s;
    }
    
    bool opEquals( HString s ) const pure
    {
        return hash == s.hash;
    }
    
    bool opEquals( string s ) const
    {
        return hash == HString(s).hash;
    }

    uint hash;
    
    debug{ string debug_str; }
}

unittest
{
    import kiwi.utils.testing;
    import kiwi.core.commons;

    auto unit = TestSuite("kiwi.utils.strhash");
    
    HString hs = "foo";
    unit.test( hs == HString("foo") );
    
    unit.test( StrHash("Int") != StrHash("UInt") );
    unit.test( StrHash("Int") != StrHash("int") );
    
    unit.test( StrHash("Int") == "Int" );
    unit.test( StrHash("Foo") == CompileHash!"Foo" );
}
