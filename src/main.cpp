
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
#define FPS 30

double X = 0;
double Y = 0;
double dx = 2.5;
double dy = 3.0;

void nGon(int x, int y, int r, int n) {
	double inc = (2 * PI) / n;
	glBegin(GL_POLYGON);
		for (double theta = 0.0; theta <= 2 * PI; theta += inc) {
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



void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);

	//glColor3ub(0, 200, 255);
	//nGon(X, Y, 30, 100);
	house(X, Y, 100);

	glFlush();
	glutSwapBuffers();
}

void idle() {
	
	unsigned int start = GetTickCount();
	while (GetTickCount() - start < 1000 / FPS) {}; //start shows undefined in intellisense but we have already defined it above, ignore it.


	X += dx;
	Y += dy;

	if (X<0 || X > SCREEN_WIDTH) dx *= -1;
	if (Y<0 || Y > SCREEN_HEIGHT) dy *= -1;

	glutPostRedisplay();
}

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
}

int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("our program \u262d");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	initGL();
	glutMainLoop();
}
#ifdef linux
double GetTickCount(void);
#endif