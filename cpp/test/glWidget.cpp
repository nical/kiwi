#include <cassert>
#include <cmath>
#include <vector>

#include "GL/glut.h"

//size of selection buffer
#define BUFSIZE 512

static int width, height;
static bool ctrl_down = false;
static bool alt_down = false;
static bool shift_down = false;

static int mx = 0; //mouse position x
static int my = 0; //mouse position y



void motion(int x, int y)
{
	x = x/2 - width/4;
	y = (height-y-1)/2 - height/4;

	//TODO: This function is called when the mouse is moved.
	//      Handle translation, rotation and scaling of the
	//      selected component here.

	//save mouse position for later
	mx = x; my = y;	

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	ctrl_down = (glutGetModifiers() & GLUT_ACTIVE_CTRL) != 0;
	alt_down = (glutGetModifiers() & GLUT_ACTIVE_ALT) != 0;
	shift_down = (glutGetModifiers() & GLUT_ACTIVE_SHIFT) != 0;

	
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	
	glutPostRedisplay();
} 

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

    // stuff

    glutSwapBuffers();
}

void reshape(int w, int h)
{
	glClearColor(1.f,1.f,1.f,0.f);
	glColor3f(0.f, 0.f, 0.f);
	glLineWidth(2.f);

	width = w; height = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/4, w/4, -h/4, h/4);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 27:
		  exit(0);
		  break;
	}

	glutPostRedisplay();
}

void menu(int c)
{
	// called whenever te c'th menu is clicked
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	
	//setup glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutCreateMenu(menu);
	glutAddMenuEntry("New capacitor..",0); 
	glutAddMenuEntry("New resistor..",1); 
	glutAddMenuEntry("New transistor",2); 
	glutAttachMenu(GLUT_RIGHT_BUTTON); 
	glutReshapeFunc(reshape);
	glutDisplayFunc(display); 
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0; 
}
