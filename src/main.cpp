
#include <stdlib.h>
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

int X = 0;
int Y = 0;
int dx = 50;
int dy = 60;

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

#ifdef linux
double GetTickCount(void)
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
	return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}
#endif

void rectangle(double x, double y, double w, double h)
{
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + w, y);
	glVertex2d(x + w, y + h);
	glVertex2d(x, y + h);
	glEnd();
}
void line(int x, int y, int w, int h)
{
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x + w, y + h);
	glEnd();
}

void victory(double x, double y)
{

	// draw spotlight
	glColor3ub(255, 248, 220);
	glBegin(GL_POLYGON);
	glVertex2d(x - 150, y - 100);
	glVertex2d(x + 150, y - 100);
	glVertex2d(x + 30, SCREEN_HEIGHT);
	glVertex2d(x - 30, SCREEN_HEIGHT);
	glEnd();

	// draw floor
	glColor3ub(155, 155, 155);
	rectangle(x - SCREEN_WIDTH / 2, y, SCREEN_WIDTH, 50);
}

void ghost(double x, double y)
{
	//BLUE GHOST
	// draw ghost tail
	glColor3ub(0, 200, 255);
	glBegin(GL_POLYGON);
	glVertex2d(x-150, SCREEN_HEIGHT/2 - 80);
	glVertex2d(x-200, SCREEN_HEIGHT/2 - 80);
	glVertex2d(x-150, SCREEN_HEIGHT/2 + 50 - 80);
	glEnd();
	//draw ghost body
	glColor3ub(0, 200, 255);
	EllipsePoly(x - 150, SCREEN_HEIGHT/2-20, 30, 100, 1.5, 2.0);
	//draw ghost eyes
	glColor3ub(255, 255, 255);
	EllipsePoly(x - 125, SCREEN_HEIGHT/2, 15.0, 100, 2.0, 1.5);
	//draw ghost outer halo
	glColor3ub(255, 255, 0);
	EllipsePoly(x -150, SCREEN_HEIGHT/2 + 70, 10.0, 200.0, 4.0, 1.5);
	//draw ghost inner halo
	glColor3ub(0, 0, 0);
	EllipsePoly(x -150, SCREEN_HEIGHT/2 + 70, 8.0, 200.0, 4.0, 1.5);
	//make transparent
	glColor4ub(0, 0, 0, 128);
	EllipsePoly(x - 150, SCREEN_HEIGHT/2-20, 60, 100, 1.5, 2.0);

//RED GHOST
	// draw ghost tail
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x+150, SCREEN_HEIGHT/2 - 80);
	glVertex2d(x+200, SCREEN_HEIGHT/2 - 80);
	glVertex2d(x+150, SCREEN_HEIGHT/2 + 50 - 80);
	glEnd();
	//draw ghost body
	glColor3ub(255, 0, 0);
	EllipsePoly(x + 150, SCREEN_HEIGHT/2-20, 30, 100, 1.5, 2.0);
	//draw ghost eyes
	glColor3ub(255, 255, 255);
	EllipsePoly(x + 125, SCREEN_HEIGHT/2, 15.0, 100, 2.0, 1.5);
	//draw ghost outer halo
	glColor3ub(255, 255, 0);
	EllipsePoly(x + 150, SCREEN_HEIGHT/2 + 70, 10.0, 200.0, 4.0, 1.5);
	//draw ghost inner halo
	glColor3ub(0, 0, 0);
	EllipsePoly(x + 150, SCREEN_HEIGHT/2 + 70, 8.0, 200.0, 4.0, 1.5);
	glColor4ub(0, 0, 0, 128);
	EllipsePoly(x + 150, SCREEN_HEIGHT/2-20, 60, 100, 1.5, 2.0);

	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);

	ghost(SCREEN_WIDTH/2, 0);
	victory(SCREEN_WIDTH / 2, 0);

	glFlush();
	glutSwapBuffers();
}

/* void idle()
{

	unsigned int start = GetTickCount();

	X += dx;
	Y += dy;

	if (X < 0 || X > SCREEN_WIDTH)
		dx *= -1;
	if (Y < 0 || Y > SCREEN_HEIGHT)
		dy *= -1;

	//while (GetTickCount() - start < 1000 / FPS) {};
	/*start shows undefined in intellisense but we have already defined it above, ignore it.
	this while function is being used to limit the FPS to the defined FPS value.
	
	glutPostRedisplay();
} */

void initGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //set background to black
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);							 //initialise glut library
	glutInitDisplayMode(GLUT_DOUBLE);				 //set displaymode to double buffered window
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //set window size
	glutCreateWindow("our program \u262d");			 //set window name
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	glutDisplayFunc(display);						 //callback function, redraw when window is updated
	//glutIdleFunc(idle);								 //execute idle function when there is no user input
	initGL();
	glutMainLoop();
}
