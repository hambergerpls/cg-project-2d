
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

int X = 200;
int Y = 150;
int dx = 50;
int dy = 60;

void nGon(int x, int y, int r, int n)
{
	double inc = (2 * PI) / n;
	glBegin(GL_POLYGON);
	for (double theta = 0.0; theta <= 2 * PI; theta += inc)
	{
		glVertex2d(r * cos(theta) + x, r * sin(theta) + y);
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
void line(double x, double y, double w, double h)
{
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x + w, y + h);
	glEnd();
}

void table(double x, double y, double w)
{

	double h = w * (2.0 / 3.0);

	// draw spotlight
	glColor3ub(255, 248, 220);
	glBegin(GL_POLYGON);
	glVertex2d(x + 30, y - 120);
	glVertex2d(x + 330, y - 120);
	glVertex2d(x + 200, y + 1000);
	glVertex2d(x + 130, y + 1000);
	glEnd();

	//draw right to left table leg
	glColor3ub(155, 83, 13);
	glLineWidth(15.0);
	line(x + 30, y - 120, 300.0, 120.0);

	//draw left to right table leg
	glColor3ub(155, 83, 13);
	glLineWidth(15.0);
	line(x + 30, y - 0, 300.0, -120.0);

	// draw table top
	glColor3ub(205, 133, 63);
	rectangle(x - 10, y - 10, w * 3.7, h * 0.5); //w & h are the sizes for the rectangle

	// draw button
	glColor3ub(255, 0, 0);
	rectangle(x + 165, y + 30, w * 0.3, h * 0.3); //w & h are the sizes for the rectangle

	// draw button box
	glColor3ub(0, 0, 0);
	rectangle(x + 155, y + 20, w * 0.5, h * 0.2); //w & h are the sizes for the rectangle

	// draw emergency box
	glColor3ub(255, 170, 0);
	rectangle(x + 120, y + 300, w * 2.5, h * 2); //w & h are the sizes for the rectangle

	// draw floor
	glColor3ub(155, 155, 155);
	rectangle(x - 300, y - 148, w * 20, h * 0.55); //w & h are the sizes for the rectangle
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);

	//glColor3ub(0, 200, 255);
	//nGon(X, Y, 30, 100);
	table(X, Y, 100);

	glFlush();
	glutSwapBuffers();
}

/*void idle() {
	DWORD start = GetTickCount();
	while (GetTickCount() - start < 1000 / FPS) {};

	X += dx;
	Y += dy;

	if (X<0 || X > SCREEN_WIDTH) dx *= -1;
	if (Y<0 || Y > SCREEN_HEIGHT) dy *= -1;

	//while (GetTickCount() - start < 1000 / FPS) {}; 
	/*start shows undefined in intellisense but we have already defined it above, ignore it.
	this while function is being used to limit the FPS to the defined FPS value.
	
	glutPostRedisplay();
}*/

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
	glutDisplayFunc(display);						 //callback function, redraw when window is updated
	//glutIdleFunc(idle);//execute idle function when there is no user input
	initGL();
	glutMainLoop();
}
#ifdef linux
double GetTickCount(void);
#endif