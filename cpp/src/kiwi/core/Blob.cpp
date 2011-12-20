#include "kiwi/core/Blob.hpp"

namespace kiwi{
namespace core{

BasicBlob::BasicBlob( uint32 bufferSize, uint32 btype, uint32 bflags )
{
    if ( bufferSize == 0 )
    {
        _buffer = 0;
        return;
    }

    allocate( bufferSize, btype, bflags );
}

BasicBlob::~BasicBlob()
{
    if ( isAllocated() )
    {
        deallocate();
    }
}

void BasicBlob::allocate( uint32 bufferSize, uint32 btype, uint32 bflags)
{
    //allocate at least 4 bytes
    if(bufferSize < 4 )
        bufferSize = 4;

    _buffer = (BlobHeader*) new uint8[ sizeof(BlobHeader) + bufferSize ];
    header()->_type = btype;
    header()->_flags = bflags;
    header()->_size = bufferSize;
}

void BasicBlob::deallocate()
{
    if ( _buffer )
        delete[] _buffer;
}

}//namespace
}//namespace
