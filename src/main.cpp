
#include <stdlib.h>
#include <iostream>
#include <math.h>
#ifdef _WIN32 //windows header location
#include <gl/freeglut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#endif
#ifdef linux //linux header location
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif
#include <time.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PI 3.1415926535897932384626433832795
#define FPS 60

double X = 0;
double Y = 0;
double dx = 2.5;
double dy = 3.0;

int frame = 0; //stores current frame count

void nGon(int x, int y, int r, int n) {
	double inc = (2 * PI) / n;
	glBegin(GL_POLYGON);
		for (double theta = 0.0; theta <= 2 * PI; theta += inc) {
			glVertex2d(r * cos(theta) + x, r * sin(theta) + y);
		}
	glEnd();
}

void rectangle(double x, double y, double w, double h) {
	glBegin(GL_POLYGON);
		glVertex2d(x, y);
		glVertex2d(x+w, y);
		glVertex2d(x+w, y+h);
		glVertex2d(x, y+h);
	glEnd();
}

void house(double x, double y, double w) {

	double h = w * (2.0 / 3.0);

	// draw body
	glColor3ub(200, 50, 0);
	rectangle(x, y, w, h);

	// draw door
	glColor3ub(255, 250, 0);
	rectangle(x+w/2 - w * 0.1, y, w * 0.2, w * (2.0 / 6.0));

	// draw left window
	glColor3ub(50, 250, 255);
	rectangle(x + w * 0.125, y + w * (2.0 / 6.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	// draw right window
	glColor3ub(50, 250, 255);
	rectangle(x + w - (w * 0.125) - w * (2.0 / 9.0), y + w * (2.0 / 6.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	// draw roof
	glColor3ub(0, 250, 15);
	glBegin(GL_POLYGON);
		glVertex2d(x-(w/6.0), y+h);
		glVertex2d(x + w + (w / 6.0), y+h);
		glVertex2d(x + w, y + h + (h/3.0));
		glVertex2d(x, y + h + (h / 3.0));
	glEnd();

}

void scene_1(){

	X += dx;
	Y += dy;

	if (X<0 || X > SCREEN_WIDTH) dx *= -1;
	if (Y<0 || Y > SCREEN_HEIGHT) dy *= -1;
	house(X, Y, 100);

}

void scene_2(){
	
}
void scene_3(){

}
void scene_4(){

}
void scene_5(){

}
void scene_6(){

}
void scene_7(){

}
void scene_8(){

}
void scene_9(){

}
void scene_10(){

}
void scene_11(){

}

void display() {
	frame++;
	std::cout << frame << std::endl; //print frame number
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);

	if(frame <= 300 ) //5 seconds scene 1
	{
		scene_1();
	}
	else if(frame > 300 && frame <= 600 ) //5 seconds scene 2
	{
		scene_2();
	}
	else if(frame > 600 && frame <= 900 ) //5 seconds scene 3
	{
		scene_3();
	}
	else if(frame > 900 && frame <= 1500 ) //10 seconds scene 4
	{
		scene_4();
	}
	else if(frame > 1500 && frame <= 1800 ) //5 seconds scene 5
	{
		scene_5();
	}
	else if(frame > 1800 && frame <= 2100 ) //5 seconds scene 6
	{
		scene_6();
	}
	else if(frame > 2100 && frame <= 2400 ) //5 seconds scene 7
	{
		scene_7();
	}
	else if(frame > 2400 && frame <= 2700 ) //5 seconds scene 8
	{
		scene_8();
	}
	else if(frame > 2700 && frame <= 3300 ) //10 seconds scene 9
	{
		scene_9();
	}
	else if(frame > 3300 && frame <= 3600 ) //5 seconds scene 10
	{
		scene_10();
	}
	else if(frame > 3600 && frame <= 3900 ) //5 seconds scene 11
	{
		scene_11();
	}

	glFlush();
	glutSwapBuffers();
}

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);//set background to black
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
}

void Timer(int){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, Timer, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);//initialise glut library
	glutInitDisplayMode(GLUT_DOUBLE);//set displaymode to double buffered window
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);//set window size
	glutCreateWindow("our program \u262d");//set window name
	glutDisplayFunc(display);//callback function, redraw when window is updated
	glutTimerFunc(0, Timer, 0);//execute function every frame
	initGL();
	glutMainLoop();
}
#ifdef linux
double GetTickCount(void);
#endif