
#include "kiwi/core/Context.hpp"



namespace kiwi{
namespace core{

static Context * s_defaultContext = 0;

Context * Context::Default()
{
    if( s_defaultContext == 0)
        s_defaultContext = new Context;

    return s_defaultContext;
}



}//namespace
}//namespace
