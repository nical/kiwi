
#pragma once
#ifndef KIWI_VIEW_NODEVIEW_HPP
#define KIWI_VIEW_NODEVIEW_HPP

#include "kiwi/view/Box.hpp"
#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{
    class Node;
    class InputPort;
    class OutputPort;
}
}

namespace kiwi{
namespace view{

class NodeDisplay;

class NodeView
{
public:
    NodeView( core::Node * n )
    : _node( n )
    {
        
    }

    virtual void nodeUpdated( int updateState ){}
    
    core::Node * node() const
    {
        return _node;
    }

    void setNode( core::Node * n )
    {
        _node = n;
    }

private:
    core::Node * _node;
};

}//namespace
}//namespace
#endif
