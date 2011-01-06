#include "Commons.hpp"

namespace Qiwi{

QString printNodeType( PortTypeEnum type)
{
    QString result;
    if( type & READER ) result += QString("reader ");
    if( type & WRITER ) result += QString("writer ");
    if( type & INPUT ) result += QString("input");
    if( type & OUTPUT ) result += QString("output");

    return result;
}


}//namespace
