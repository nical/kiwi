module kiwi.utils.datastructures;

import std.stdio;

/**
 * A dynamic array that is piecewise continuous and does not reallocate objects 
 * when resizing.
 */ 
struct PiecewiseVector(T,int ChunkSize)
{
    alias PWVChunk!(T,ChunkSize) Chunk;
    
    this( uint initlen = 0 )
    {
        assert(_first.next is null);
        
        length = initlen; 
    }
    
    ref inout(T) opIndex(int i) inout
    {
        inout(Chunk)* chk = &_first;
        while( i >= ChunkSize )
        {
            i -= ChunkSize;
            chk = chk.next;
        }
        return chk.data[i];
    }
    
    @property{
        
        uint length() const pure
        {
            return _length;
        }
        
        void length(uint newlen)
        {
            int diff = newlen - _length;
            if( diff < 0 )
            {
                _length = newlen;
                _lastChunkLength = newlen % ChunkSize;
            }
            else if( diff > 0 )
            {
                int i = 0;
                Chunk* c = &_first;
                assert( c !is null );
                while( (c.next !is null) && (i*ChunkSize < newlen) )
                {
                    c = c.next;
                    ++i;
                }
                while( i*ChunkSize < newlen )
                {
                    ++i;
                    c.next = new Chunk;                    
                }
                _lastChunkLength = newlen - (i-1)*ChunkSize;
                _length = newlen;
            }
        }
    }
private:
    Chunk    _first;
    uint     _length;
    uint     _lastChunkLength;
}

struct PWVChunk(T,int ChunkSize)
{
    T[ChunkSize] data;
    PWVChunk* next;
}

struct PWVRange(T,ChunkSize)
{
    alias PWVChunk!(T,ChunkSize) Chunk;

    @property bool empty()
    {
        NotImplemented("PVRange.empty");
    }

    @property ref T front()
    {
        return _chunk.data[_index];
    }

    void popFront()
    {
        if ( _index < ChunkSize -1 )
            ++_index;
        else _chunk = _chunk.next;
    }
    
private:
    PiecewiseVector!(T,ChunkSize)* _vector;
    uint   _index;
    Chunk* _chunk;
}



unittest
{
    import kiwi.utils.testing;
    
    auto unit = TestSuite("PiecewiseVector");
    
    
    PiecewiseVector!(int,8) pv1;
    auto pv2 = PiecewiseVector!(int,8)(10);
    
    unit.test( pv1.length == 0, "Empty vector length = 0" );
    unit.test( pv2.length == 10, "Vector initialized with size 10" );
    
    unit.test( pv1._lastChunkLength == 0, "Length of the last fragment of an empty vector" );
    unit.test( pv2._lastChunkLength == 2, "Length of the last fragment of a 10 elements vector" );
    
    pv1.length = 5;
    unit.test( pv1.length == 5, "Container length" );
    
    // lets see if read/writes segfault
    for(uint i = 0; i < pv1.length; ++i)
    {
        pv1[i] = i;
        assert(pv1[i] == i);
    }
    
    pv1.length = 19;
    unit.test( pv1.length == 19, "Container length" );
    unit.test( pv1._lastChunkLength == 3, "Last fragment length" );
    
    // lets see if read/writes segfault
    for(uint i = 0; i < pv1.length; ++i)
    {
        pv1[i] = i;
        assert(pv1[i] == i);
    }
    
    pv1.length = 10;
    unit.test( pv1.length == 10, "Container length" );
    unit.test( pv1._lastChunkLength == 2, "Last fragment length" );

    for(uint i = 0; i < pv1.length; ++i)
    {
        //stdout.writeln(i,":",pv1[i]);
        assert(pv1[i] == i);
    }
    
}

