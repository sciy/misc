// By Yan Huang, M.W. revised
// g++ openGL-gif2b.cpp -o oglgif2b -lGL -lGLU -lglut

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/freeglut.h> // freeglut.h includes more things than glut.h includes, and the later in turn includes gl.h and glu.h.
using namespace std;

GLfloat X = 10.0f;
GLfloat Y = 1.0f;
GLfloat Z = 5.0f;

void myDisplay(void)
{
		GLfloat diffuse[] = {0.7, 0.7, 0.0, 1.0};
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
/*绘制立方体*/
		glPushMatrix();
		glRotatef(X, 1.0, 0.0, 0.0);
		glRotatef(Y, 0.0, 1.0, 0.0);
		glRotatef(Z, 0.0, 0.0, 1.0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glutSolidCube(1.0);
		glPopMatrix();
		glFlush();
		glutSwapBuffers();//交换当前窗口使用层的缓存
}
//myDisplay函数中有一个glutSwapBuffers()函数。
//此函数交换当前窗口使用层的缓存，它将后台缓存中的内容交换到前台缓存中，该函数执行的结果直到显示器垂直回行扫描后才看得到。
//必须使用双缓存结构，否则此函数不起任何作用。

void myReshape(int w, int h)
{
		glViewport(0,0,w,h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-1.5, 1.5, -1.5, 1.5);
		if(w <= h)
				glOrtho(-2.25, 2.25, -2.25*h/w, 2.25*h/w, -10.0, 10.0);
		else
				glOrtho(-2.25*w/h, 2.25*w/h, -2.25, 2.25, -10.0, 10.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

void myAnimate(void)
{
		X += 1.0;
		Y += 1.0;
		Z += 1.0;
		glutPostRedisplay();//标记当前窗口需要重新绘制
}
//myAanimate函数中glutPostRedisplay()函数标记当前窗口需要重新绘制。在glutMainLoop函数的事件处理循环的下一个反复中，将调用该窗口的显示回调函数重绘该窗口的图像层。

int main(int argc, char ** argv)
{
/*初始化*/
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

/*创建窗口*/
		glutCreateWindow("hello, OpenGL gif in 2 buffers");

/*绘制与显示*/
		glutReshapeFunc(myReshape);

		glutDisplayFunc(myDisplay);
		glutIdleFunc(myAnimate);//设置全局空闲回调函数

		glutMainLoop();

		return(0);
}
//在main函数中glutInitDisplayMode中为GLUT_DOUBLE，而我们以前的很多例子为GLUT_SINGLE。
//main函数中还调用了glutIdleFunc，此函数设置全局空闲回调函数，从而使GLUT程序可以执行后台任务或连续动画。
