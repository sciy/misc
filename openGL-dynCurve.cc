// plot a moving sin curve with OpenGL.
// gcc x.cc -o x -lGL -lGLU -lglut
// By M.W.

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/freeglut.h> // freeglut.h for all
using namespace std;

const float freq = 1;// plot sin(freq*x+delta), where delta is changing.
float delta = 0, deltaStep = 0.01;

void myDisplay(void)
{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_LINE_STRIP); // draw the sin curve, with a dynamic delta
				for(float x = -M_PI; x < M_PI; x += 0.01) glVertex2f(x, sin(freq*x+delta));
		glEnd();

		glFlush();
		glutSwapBuffers();
}

void myAnimate(void) // update delta and redraw
{
		delta += deltaStep;
		glutPostRedisplay();
}

int main(int argc, char ** argv)
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

		glutCreateWindow("hello, dynamic curve"); // create the window frame
		glutDisplayFunc(myDisplay);// register the display function
		glutIdleFunc(myAnimate);//register the update function

		glutMainLoop();
		return(0);
}
