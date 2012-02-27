module kiwi.core.datafactory;

import kiwi.core.commons;

interface DataFactory
{
    Object instanciateData( DataTypeID type );
    bool contains( DataTypeID type );
}

version(unittest)
{
    class Foo { }
    class Bar { }
}

unittest
{
    import kiwi.utils.testing;
    import std.stdio;
    
    auto unit = TestSuite("kiwi.core.datafactory");
     
}
