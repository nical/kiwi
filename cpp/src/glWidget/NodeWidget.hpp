
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

namespace glWidget{


void DrawCircle(GLenum style = GL_POLYGON, int step = 32);
void DrawSquare(GLenum style);


class NodeWidget
{
public:
    enum{ NORMAL=0, DRAG=1, PORT_SELECTED=2 };

    float x;
    float y;
    float w;
    float h;
    
    NodeWidget(kiwi::core::Node* n, float nx, float ny, float nw, float nh )
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
