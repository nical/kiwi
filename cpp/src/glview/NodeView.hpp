
#pragma once
#ifndef KIWI_GLWIDGET_NODEWIDGET_HPP
#define KIWI_GLWIDGET_NODEWIDGET_HPP

#include "GL/glut.h"

namespace kiwi{

namespace core
{
    class Node;
    class Port;
}    

namespace glview{


void DrawCircle(GLenum style = GL_POLYGON, int step = 32);
void DrawSquare(float x, float y, float w, float h, GLenum style = GL_POLYGON);


class NodeView
{
public:
    enum{ NORMAL=0, DRAG=1, PORT_SELECTED=2 };

    NodeView(float nx, float ny, float nw = 30.0, float nh = 40.0)
    : x(nx), y(ny), w(nw), h(nh)
    {
    }

    float x;
    float y;
    float w;
    float h;
    
    NodeView(kiwi::core::Node* n, float nx, float ny, float nw, float nh )
    : x(nx), y(ny), w(nw), h(nh),_node(n), _state(NORMAL)
    {
        
    }
    
    kiwi::core::Node* node() { return _node; }
    int state() { return _state; }

    void display();
    bool cursorClick(float mx, float my, int button, int state);
    bool cursorDrag(float mx, float my, int button, int state);


private:
    kiwi::core::Node* _node;
    int _state;
};

}//namespace
}//namespace
#endif
