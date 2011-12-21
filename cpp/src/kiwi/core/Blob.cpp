#include "kiwi/core/Blob.hpp"

namespace kiwi{
namespace core{

Blob::Blob( uint32 bufferSize, uint32 btype, uint32 bflags )
{
    if ( bufferSize == 0 )
    {
        _buffer = 0;
        return;
    }

    allocate( bufferSize, btype, bflags );
}

Blob::~Blob()
{
    if ( isAllocated() )
    {
        deallocate();
    }
}

void Blob::allocate( uint32 bufferSize, uint32 btype, uint32 bflags)
{
    //allocate at least 4 bytes
    if(bufferSize < 4 )
        bufferSize = 4;

    _buffer = (BlobHeader*) new uint8[ sizeof(BlobHeader) + bufferSize ];
    header()->_type = btype;
    header()->_flags = bflags;
    header()->_size = bufferSize;
}

void Blob::deallocate()
{
    if ( _buffer )
        delete[] _buffer;
}

}//namespace
}//namespace
