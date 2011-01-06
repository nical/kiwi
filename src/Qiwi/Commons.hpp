#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <QString>

namespace Qiwi{
/*
    enum PortTypeEnum{ READER = 0x1
        , WRITER = 0x2
        , INPUT = 0x4
        , OUTPUT = 0x8
    };
*/

    enum PortTypeEnum{
           READER = 0x1
         , WRITER = 0x2
         , INPUT = 0x4
         , OUTPUT = 0x8
         , READER_INPUT = READER | INPUT
         , READER_OUTPUT = READER | OUTPUT
         , WRITER_INPUT = WRITER | INPUT
         , WRITER_OUTPUT = WRITER | OUTPUT
         , INPUT_OUTPUT_MASK = INPUT | OUTPUT
         , READER_WRITER_MASK = READER | WRITER
    };

    inline PortTypeEnum operator&(PortTypeEnum lhs, PortTypeEnum rhs){
        return static_cast<PortTypeEnum>(static_cast<int>(lhs) & static_cast<int>(rhs) );
    }
    inline PortTypeEnum operator|(PortTypeEnum lhs, PortTypeEnum rhs){
        return static_cast<PortTypeEnum>(static_cast<int>(lhs) | static_cast<int>(rhs) );
    }

    QString printNodeType( PortTypeEnum type);

}

#endif // COMMONS_HPP

