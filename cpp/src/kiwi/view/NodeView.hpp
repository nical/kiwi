
#pragma once
#ifndef KIWI_VIEW_NODEVIEW_HPP
#define KIWI_VIEW_NODEVIEW_HPP

#include "kiwi/view/Box.hpp"

namespace kiwi{
namespace view{

class NodeDisplay;

class NodeView
{
public:
    enum{ NORMAL=0, DRAG=1, PORT_SELECTED=2 };
    typedef int NodeId; 

    NodeView(NodeId nodeID, float nx, float ny )
    : _nodeId(nodeID), _state(NORMAL)
    {
        _box.x = nx;
        _box.y = ny;
        _box.w = 30.f;
        _box.h = 50.f;
    }
    
    int state() const
    {
        return _state;
    }

    void display() const;
    bool cursorClick(float mx, float my, int button, int state);
    bool cursorDrag(float mx, float my, int button, int state);

    Box boundingBox() const
    {
        return _box;
    }

private:
    NodeId _nodeId;
    int _state;
    Box _box;
    NodeDisplay* _display;
};

}//namespace
}//namespace
#endif
