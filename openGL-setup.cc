// http://www.codeproject.com/Articles/182109/Setting-up-an-OpenGL-development-environment-in-Ub
// https://qinmaple.wordpress.com/2011/01/06/openglinstall-opengl-developing-environment-on-64bit-windows7-with-visual-studio-express-c-2008-ubuntu/
//
// It is more convenient to install the developing env. in Ubuntu.
// As you have install the ATI driver, you should got newest openGL the HW supported.
// Just check the GL version
//    glxinfo | grep -i opengl
//  or open the ATI control center to check the openGL version.
//
// You only need to install the glut header and lib files
//    sudo apt-get install build-essential libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev freeglut3-dev
//    gcc yourfile.cpp -lGL -lGLU -lglut -o appname

#include <GL/freeglut.h>
// freeglut includes gl.h, glu.h, as well as the things glut.h includes.

/* display function - code from:
     http://fly.cc.fer.hr/~unreal/theredbook/chapter01.html
This is the actual usage of the OpenGL library. 
The following code is the same for any platform */
void renderFunction()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}

/* Main method - main entry point of application
the freeglut library does the window creation work for us, 
regardless of the platform. */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(renderFunction);
    glutMainLoop();    
    return 0;
}
