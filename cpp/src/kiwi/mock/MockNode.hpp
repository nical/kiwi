
#pragma once
#ifndef KIWI_MOCK_MOCKNODE_HPP
#define KIWI_MOCK_MOCKNODE_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{
    namespace core
    {
        class Node;
    }
namespace mock{

void DelcareMockNode( uint32 nbInputs, uint32 nbOutputs );

core::Node* NewMockNode();


}//namespace
}//namespace


#endif 
