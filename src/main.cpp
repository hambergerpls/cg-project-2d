
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

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PI 3.14159265
#define FPS 60

double X = 0;
double Y = 0;
double dx = 2.5;
double dy = 3.0;

int frame = 0; //stores current frame count

/* 
========================
Drawing tools
========================
 */
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

void line(int x, int y, int w, int h)
{
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x + w, y + h);
	glEnd();
}

void EllipsePoly(double x, double y, double r, int n, double a, double b)
{
	double inc = (2 * PI) / n;
	glBegin(GL_POLYGON);
	for (double theta = 0.0; theta <= 2 * PI; theta += inc)
	{
		glVertex2d(r * cos(theta) * a + x, r * sin(theta) * b + y);
	}
	glEnd();
}

/* 
========================
Drawing tools
========================
 */

/* 
========================
Objects
========================
 */

void electricalBox(double x, double y, double w)
{

	double h = w * (2.0 / 3.0);
	//
	// draw body (outer rectangle)
	glColor3ub(100, 100, 100);
	rectangle(x - 10, y - 10, w * 3.7, h * 3.8); //w & h are the sizes for the rectangle

	// draw body (inner rectangle)
	glColor3ub(160, 160, 160);
	rectangle(x, y, w * 3.5, h * 3.5); //w & h are the sizes for the rectangle

	//WIRES//
	// draw red wire
	glColor3ub(204, 0, 0);
	rectangle(x + 20, y + 67 + w * (135.0 / 100.0), w * 3.1, w * (0.8 / 9.0));
	// draw yellow wire
	glColor3ub(255, 204, 0);
	rectangle(x + 20, y + 6.8 + w * (135.0 / 100.0), w * 3.1, w * (0.8 / 9.0));

	//draw pink wire
	glColor3ub(240, 21, 124);
	glLineWidth(6.0);
	line(x + 20, y + 25, 320.0, 65.0);

	//draw blue wire
	glColor3ub(0, 102, 255);
	glLineWidth(6.0);
	line(x + 20, y + 85, 320.0, -60.0);

	//LEFT SOCKETS//
	// draw left socket (most bottom)
	glColor3ub(255, 0, 255);
	rectangle(x + w * 0, y + w * (15.0 / 100.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	// draw left socket (2nd most bottom)
	glColor3ub(0, 255, 255);
	rectangle(x + w * 0, y + w * (75.0 / 100.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	// draw left socket (3rd most bottom)
	glColor3ub(255, 255, 0);
	rectangle(x + w * 0, y + w * (135.0 / 100.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	// draw left socket (most top)
	glColor3ub(255, 0, 0);
	rectangle(x + w * 0, y + w * (195.0 / 100.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	//RIGHT SOCKETS//
	// draw right socket (most bottom)
	glColor3ub(0, 255, 255);
	rectangle(x + w * 3.28, y + w * (15.0 / 100.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	// draw right socket (2nd most bottom)
	glColor3ub(255, 0, 255);
	rectangle(x + w * 3.28, y + w * (75.0 / 100.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	// draw right socket (3rd most bottom)
	glColor3ub(255, 255, 0);
	rectangle(x + w * 3.28, y + w * (135.0 / 100.0), w * (2.0 / 9.0), w * (2.0 / 9.0));

	// draw right socket (most top)
	glColor3ub(255, 0, 0);
	rectangle(x + w * 3.28, y + w * (195.0 / 100.0), w * (2.0 / 9.0), w * (2.0 / 9.0));
}

void spotlight(double x, double y)
{
	glColor4ub(255, 248, 220, 128);
	glBegin(GL_POLYGON);
	glVertex2d(x - 150, 0);
	glVertex2d(x + 150, 0);
	glVertex2d(x + 35, SCREEN_HEIGHT);
	glVertex2d(x + -35, SCREEN_HEIGHT);
	glEnd();
}

void table(double x, double y, double w)
{

	//draw left to right table leg
	glColor3ub(155, 83, 13);
	glLineWidth(15.0);
	line(x - 150, y, 300.0, 120.0);

	//draw right to left table leg
	glColor3ub(155, 83, 13);
	glLineWidth(15.0);
	line(x + 150, y, -300.0, 120.0);

	// draw table top
	glColor3ub(205, 133, 63);
	rectangle(x - w / 2, y + 120, w, w * 0.1); //w & h are the sizes for the rectangle

	// draw button
	glColor3ub(255, 0, 0);
	rectangle(x - 25, y + 160, 50, 10); //w & h are the sizes for the rectangle

	// draw button box
	glColor3ub(0, 0, 0);
	rectangle(x - 50, y + 150, 100, 10); //w & h are the sizes for the rectangle

	// draw emergency box
	glColor3ub(255, 170, 0);
	rectangle(x - 50, y + 155, 100, 5); //w & h are the sizes for the rectangle
}

void ghost(double x, double y)
{
	//BLUE GHOST
	// draw ghost tail
	glColor3ub(0, 200, 255);
	glBegin(GL_POLYGON);
	glVertex2d(x - 150, SCREEN_HEIGHT / 2 - 80);
	glVertex2d(x - 200, SCREEN_HEIGHT / 2 - 80);
	glVertex2d(x - 150, SCREEN_HEIGHT / 2 + 50 - 80);
	glEnd();
	//draw ghost body
	glColor3ub(0, 200, 255);
	EllipsePoly(x - 150, SCREEN_HEIGHT / 2 - 20, 30, 100, 1.5, 2.0);
	//draw ghost eyes
	glColor3ub(255, 255, 255);
	EllipsePoly(x - 125, SCREEN_HEIGHT / 2, 15.0, 100, 2.0, 1.5);
	//draw ghost outer halo
	glColor3ub(255, 255, 0);
	EllipsePoly(x - 150, SCREEN_HEIGHT / 2 + 70, 10.0, 200.0, 4.0, 1.5);
	//draw ghost inner halo
	glColor3ub(0, 0, 0);
	EllipsePoly(x - 150, SCREEN_HEIGHT / 2 + 70, 8.0, 200.0, 4.0, 1.5);
	//make transparent
	glColor4ub(0, 0, 0, 128);
	EllipsePoly(x - 150, SCREEN_HEIGHT / 2 - 20, 60, 100, 1.5, 2.0);

	//Yellow GHOST
	// draw ghost tail
	glColor3ub(245, 245, 87);
	glBegin(GL_POLYGON);
	glVertex2d(x + 150, SCREEN_HEIGHT / 2 - 80);
	glVertex2d(x + 200, SCREEN_HEIGHT / 2 - 80);
	glVertex2d(x + 150, SCREEN_HEIGHT / 2 + 50 - 80);
	glEnd();
	//draw ghost body
	glColor3ub(245, 245, 87);
	EllipsePoly(x + 150, SCREEN_HEIGHT / 2 - 20, 30, 100, 1.5, 2.0);
	//draw ghost eyes
	glColor3ub(255, 255, 255);
	EllipsePoly(x + 125, SCREEN_HEIGHT / 2, 15.0, 100, 2.0, 1.5);
	//draw ghost outer halo
	glColor3ub(255, 255, 0);
	EllipsePoly(x + 150, SCREEN_HEIGHT / 2 + 70, 10.0, 200.0, 4.0, 1.5);
	//draw ghost inner halo
	glColor3ub(0, 0, 0);
	EllipsePoly(x + 150, SCREEN_HEIGHT / 2 + 70, 8.0, 200.0, 4.0, 1.5);
	glColor4ub(0, 0, 0, 128);
	EllipsePoly(x + 150, SCREEN_HEIGHT / 2 - 20, 60, 100, 1.5, 2.0);

	//Green GHOST
	// draw ghost tail
	glColor3ub(0, 255, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x + 350, SCREEN_HEIGHT / 2 - 160);
	glVertex2d(x + 400, SCREEN_HEIGHT / 2 - 160);
	glVertex2d(x + 350, SCREEN_HEIGHT / 2 + 50 - 160);
	glEnd();
	//draw ghost body
	glColor3ub(0, 255, 0);
	EllipsePoly(x + 350, SCREEN_HEIGHT / 2 - 100, 30, 100, 1.5, 2.0);
	//draw ghost eyes
	glColor3ub(255, 255, 255);
	EllipsePoly(x + 325, SCREEN_HEIGHT / 2 - 80, 15.0, 100, 2.0, 1.5);
	//draw ghost outer halo
	glColor3ub(255, 255, 0);
	EllipsePoly(x + 350, SCREEN_HEIGHT / 2 - 10, 10.0, 200.0, 4.0, 1.5);
	//draw ghost inner halo
	glColor3ub(0, 0, 0);
	EllipsePoly(x + 350, SCREEN_HEIGHT / 2 - 10, 8.0, 200.0, 4.0, 1.5);
	glColor4ub(0, 0, 0, 128);
	EllipsePoly(x + 350, SCREEN_HEIGHT / 2 - 100, 60, 100, 1.5, 2.0);
}

void imposter(double x, double y)
{

	//RED crewmate
	//draw  body
	glColor3ub(255, 0, 0);
	EllipsePoly(x, SCREEN_HEIGHT/2 - 100 +y, 45, 100, 1.5, 2.0);
	//draw face
	glColor3ub(255, 255, 255);
	EllipsePoly(x, SCREEN_HEIGHT/2 - 60 +y, 10.0, 20.0, 4.5, 2.0);
	//draw left leg
	glColor3ub(255, 0, 0);
	EllipsePoly(x-25, SCREEN_HEIGHT/2 - 185 +y, 15, 20, 1.5, 2.0);
	//draw right leg
	glColor3ub(255, 0, 0);
	EllipsePoly(x+25, SCREEN_HEIGHT/2 - 185 +y, 15, 20, 1.5, 2.0);
}

void crew(double x, double y, int R, int G, int B){
	
	//draw right leg
	glColor4ub(R, G, B, 224);
	rectangle(x + 0, y - 30, 30, -40);
	//draw body
	glColor3ub(R, G, B);
	EllipsePoly(x, y, 30, 100, 1.5, 2.0);
	//draw eyes
	glColor3ub(255, 255, 255);
	EllipsePoly(x+25, y+15, 15.0, 100, 2.0, 1.5);
	//draw left leg
	glColor3ub(R, G, B);
	rectangle(x - 40, y - 30, 30, -40);
}

/* 
========================
Objects
========================
 */

/* 
========================
Scenes
========================
 */

void scene_1(){



	crew(SCREEN_WIDTH/3 + 50, 120, 197, 17, 17);//RED
	crew(SCREEN_WIDTH/3 + 150, 120, 17, 127, 45);//GREEN
	crew(SCREEN_WIDTH/3 + 250, 120, 19, 46, 209);//BLUE
	crew(SCREEN_WIDTH/3 + 350, 120, 245, 245, 87);//YELLOW
	// draw floor
	glColor3ub(155, 155, 155);
	rectangle(0, 0, SCREEN_WIDTH, 50);
	spotlight(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void scene_2(){
	
}
void scene_3(){

}
void scene_4(){
	electricalBox(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, 100);

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

	table(SCREEN_WIDTH / 2, 50, 300);
	spotlight(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	// draw floor
	glColor3ub(155, 155, 155);
	rectangle(0, 0, SCREEN_WIDTH, 50);

}
void scene_10(){

}
void scene_11(){


	imposter(SCREEN_WIDTH/2, 50);
	spotlight(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	ghost(SCREEN_WIDTH / 2, 0);
	// draw floor
	glColor3ub(155, 155, 155);
	rectangle(0, 0, SCREEN_WIDTH, 50);

}

/* 
========================
Scenes
========================
 */

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
	glMatrixMode(GL_MODELVIEW);
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutTimerFunc(0, Timer, 0);//execute function every frame
	initGL();
	glutMainLoop();
}