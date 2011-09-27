
#include "glWidget/NodeWidget.hpp"
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

void DrawSquare(GLenum style)
{
    glBegin(style);
        glVertex2f( 0, 0 );
        glVertex2f( 1, 0 );
        glVertex2f( 1, 1 );
        glVertex2f( 0, 1 );
    glEnd();
}

}//namespace
}//namespace
