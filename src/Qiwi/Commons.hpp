#ifndef COMMONS_HPP
#define COMMONS_HPP


namespace Qiwi{

    enum{ READER = 0x1
        , WRITER = 0x2
        , INPUT = 0x4
        , OUTPUT = 0x8
    };

    enum{  READER_INPUT = READER | INPUT
         , READER_OUTPUT = READER | OUTPUT
         , WRITER_INPUT = WRITER | INPUT
         , WRITER_OUTPUT = WRITER | OUTPUT
         , INPUT_OUTPUT_MASK = INPUT | OUTPUT
         , READER_WRITER_MASK = READER | WRITER
    };

}

#endif // COMMONS_HPP

