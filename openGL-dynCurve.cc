// plot a moving sin curve controled by keyboard with OpenGL.
// gcc x.cc -o x -lGL -lGLU -lglut
// By M.W.

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/freeglut.h> // freeglut.h for all
using namespace std;

float freq = 1, freqStep = 0.3, delta = 0, deltaStep = 0.3; // plot sin(freq*x+delta)
int KeyboardState = 0; // state=0: change delta, 1 for freq

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
		glutPostRedisplay();
}

void myKeyboard(unsigned char key,int x, int y)
{
        if (key == 'd' || key == 'D')
        {
            KeyboardState = 0;
            cout << "switch to the delta change mode" << endl;
        }
        else if (key == 'f' || key == 'F')
        {
            KeyboardState = 1;
            cout << "switch to the freq change mode" << endl;
        }
        else if (key == 27)
        {
            cout << "user terminated" << endl;
            exit(0);
        }
        else
        {
            if (KeyboardState == 0 && key == '=')
            {
                delta += deltaStep;
                cout << "increasing delta" << endl;
            }
            else if (KeyboardState == 0 && key == '-')
            {
                delta -= deltaStep;
                cout << "decreasing delta" << endl;
            }
            else if (KeyboardState == 1 && key == '=')
            {
                freq += freqStep;
                cout << "increasing freq" << endl;
            }
            else if (KeyboardState == 1 && key == '-')
            {
                freq -= freqStep;
                cout << "decreasing freq" << endl;
            }
        }
}

int main(int argc, char ** argv)
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

		glutCreateWindow("hello, dynamic curve"); // create the window frame
		glutDisplayFunc(myDisplay); // register the display function
		glutIdleFunc(myAnimate); //register the update function
        glutKeyboardFunc(myKeyboard);

        cout << "Plot a dynamic sin curve.\nPress D/F to switch parameters.\nPress -/= to decrease/increase them.\nPress Esc to quit." << endl;
		glutMainLoop();
		return(0);
}
