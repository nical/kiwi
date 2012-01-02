
#include "kiwi/core/DataHeader.hpp"
#include "kiwi/core/Context.hpp"

namespace kiwi{
namespace core{

// --------------------------------------------------------------------- DataRef

/*

DataRef::DataRef( DataHeader * header )
:_ptr(header), _refCount(0)
{
    if( header ) header->increaseRefcount();
}

DataRef::DataRef( DataHeader & header )
:_ptr(&header), _refCount(0)
{
    header.increaseRefcount();
}

DataRef::DataRef( const DataRef& toCopy )
: _ptr( toCopy._ptr ), _refCount(0)
{
    if ( _ptr ) _ptr->increaseRefcount();
}

DataRef::~DataRef()
{
    if ( _ptr ) _ptr->decreaseRefCount( _refCount + 1 );
}

DataRef& DataRef::operator=( DataRef& ref )
{
    if ( &ref != this )
    {
        auto temp = _ptr;
        _ptr = ref._ptr;
        if ( _ptr ) _ptr->increaseRefcount( _refCount + 1 );
        if ( temp ) temp->decreaseRefCount( _refCount + 1 );
    }
    return *this;
}
*/

// ------------------------------------------------------------------ DataHeader

void DataHeader::increaseRefCount( uint16 nb )
{
    _refCount += nb;
}

void DataHeader::decreaseRefCount( uint16 nb )
{
    _refCount -= nb;
    if(_refCount == 0)
        context()->markNotUsed( this );
    assert( _refCount >= 0 );
}



}//namespace
}//namespace
