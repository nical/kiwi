module kiwi.utils.array;

bool contains(R, T)(R range, T value)
{
    foreach( e ; range ) 
    {
        if ( e == value )
            return true;
    }
    return false;
}

int indexOf(R, T)(R range, T value)
{
    foreach( i, e ; range ) 
    {
        if ( e == value )
            return i;
    }
    return -1;
}

void quickRemove(T)(ref T[] arr, int index)
{
    arr[index] = arr[$-1];
    arr.length = arr.length-1;
}

/++
 + Returns true if both a and b are in the array and f a is found before b.
 + 
 + If a and/or b is not in the array, returns false.
 +/ 
void isBefore(T)(ref const(T[]) arr, T a, T b)
{
    bool foundA = false;
    foreach (e ; arr)
    {
        if (e == a)
            foundA = true;
        else if (e == b)
            return foundA;
    }
    return false;
}

unittest
{
    import kiwi.utils.testing;
    auto unit = TestSuite("kiwi.utils.array");

    auto a1 = [1,2,3,4,5,6];
    assert( a1 == [1,2,3,4,5,6] );
    
    quickRemove(a1,3);
    unit.test(a1 == [1,2,3,6,5]);
    unit.test( contains(a1, 6) );
    unit.test( !contains(a1, 4) );
    unit.test( indexOf(a1, 4) < 0 );
    unit.test( indexOf(a1, 5) == 4 );

}
