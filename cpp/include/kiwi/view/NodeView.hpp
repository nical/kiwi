
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

    virtual void outputConnected(core::OutputPort* port, core::InputPort* to){}
    virtual void inputConnected(core::InputPort* port, core::OutputPort* to){}
    virtual void outputDisconnected(core::OutputPort* port, core::InputPort* from){}
    virtual void inputDisconnected(core::InputPort* port, core::OutputPort* from){}
    
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
