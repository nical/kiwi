
#include "kiwi/core/DynamicNodeUpdater.hpp" 

#include "kiwi/core/Node.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/DebugStream.hpp"

namespace kiwi{
namespace core{


bool DynamicNodeUpdater::update(const Node& n)
{
    SCOPEDBLOCK("DynamicNodeUpdater::update");
    if ( _fptr == 0 )
    {
        // TODO throw an error
        return false;
    }
    DataArray inputs( n.inputs().size() );
    DataArray outputs( n.outputs().size() );

    for( uint32 i = 0; i < n.inputs().size(); ++i )
    {
        if ( n.inputs()[i]->isConnected() )
            inputs[i] = n.inputs()[i]->connection()->data();
        else
        {
            if( !n.input(i).isOptional() )
                return false;
            inputs[i] = 0;
        }
    }
    
    for( uint32 i = 0; i < n.outputs().size(); ++i )
    {
        outputs[i] = n.outputs()[i]->data();
    }

    return _fptr(inputs, outputs);
}


}//namespace
}//namespace
