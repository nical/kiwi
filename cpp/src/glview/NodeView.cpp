
#include "glWidget/NodeView.hpp"
#include "GL/glut.h"
#include <math.h>

namespace kiwi{
namespace glWidget{

void DrawCircle(GLenum style, int step)
{
    glBegin(style);
        for(int i = 0; i < step; ++i)
        {
            float teta = (float)i/(float)step;
            glVertex2f( cos(teta), sin(teta) );
        }
    glEnd();
}


void DrawSquare(float x, float y, float w, float h, GLenum style)
{
    glBegin(style);
        glVertex2f( x, y );
        glVertex2f( x+w, y );
        glVertex2f( x+w, y+h );
        glVertex2f( x, y+h );
    glEnd();
}


void NodeView::display()
{
    glColor4f(0.0, 0.0, 0.0, 0.7);
    DrawSquare(x,y,w,h);
    
}

}//namespace
}//namespace
