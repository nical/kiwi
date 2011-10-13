#include "kiwi/core/OpConnect.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"


namespace kiwi{
namespace core{
    
bool operator >> (OutputPort& output, InputPort& input )
{
    return input.connect( output );
}

}// namespace
}// namespace
