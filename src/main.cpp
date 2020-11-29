
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

int frame = 0; //stores current frame count

/* 
========================
Scenes Global Variables
========================
 */

//SCENE 1
double scene1_fadeEffect = -16.0;
int scene1_fade = 0;
double scene1_scrollX = 0;
double scene1_rotationX = 0;

//SCENE 2
double scene2_translateX = 0;
double scene2_scrollX;

/* 
========================
Scenes Global Variables
========================
 */

/* 
========================
Drawing tools
========================
 */
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

void renderSpacedBitmapString(float x, float y, void *font, char *string)
{
	char *c;
	int x1 = x;
	for (c = string; *c != '\0'; c++)
	{
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c);
	}
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

	/* //WIRES//
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
	line(x + 20, y + 85, 320.0, -60.0); */

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

void spotlight(double x, double y, double top_width, double bottom_width)
{
	glColor4ub(255, 248, 220, 128);
	glBegin(GL_POLYGON);
	glVertex2d(x - bottom_width / 2, 0);
	glVertex2d(x + bottom_width / 2, 0);
	glVertex2d(x + top_width / 2, SCREEN_HEIGHT);
	glVertex2d(x - top_width / 2, SCREEN_HEIGHT);
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

void ghost(double x, double y, int R, int G, int B, int direction)
{
	// draw ghost tail
	glColor4ub(0, G, B, 128);
	glBegin(GL_POLYGON);
	glVertex2d(x + direction * 150, y - 80);
	glVertex2d(x + direction * 200, y - 80);
	glVertex2d(x + direction * 175, y - 80 + 15);
	glEnd();
	//draw ghost body
	glColor4ub(0, G, B, 128);
	EllipsePoly(x + direction * 150, y - 20, 30, 100, 1.5, 2.0);
	//draw ghost eyes
	glColor3ub(0, 0, 0);
	EllipsePoly(x + direction * 125, y, 15.0, 100, 2.0, 1.5);
	glColor3ub(255, 255, 255);
	EllipsePoly(x + direction * 125, y, 13.0, 100, 2.0, 1.5);
	//draw ghost outer halo
	glColor3ub(255, 255, 0);
	EllipsePoly(x + direction * 150, y + 70, 10.0, 200.0, 4.0, 1.5);
	//draw ghost inner halo
	glColor3ub(0, 0, 0);
	EllipsePoly(x + direction * 150, y + 70, 8.0, 200.0, 4.0, 1.5);
}

void imposter(double x, double y)
{

	//RED crewmate
	//draw  body
	glColor3ub(255, 0, 0);
	EllipsePoly(x, SCREEN_HEIGHT / 2 - 100 + y, 45, 100, 1.5, 2.0);
	//draw face
	glColor3ub(255, 255, 255);
	EllipsePoly(x, SCREEN_HEIGHT / 2 - 60 + y, 10.0, 20.0, 4.5, 2.0);
	//draw left leg
	glColor3ub(255, 0, 0);
	EllipsePoly(x - 25, SCREEN_HEIGHT / 2 - 185 + y, 15, 20, 1.5, 2.0);
	//draw right leg
	glColor3ub(255, 0, 0);
	EllipsePoly(x + 25, SCREEN_HEIGHT / 2 - 185 + y, 15, 20, 1.5, 2.0);
}

void crew(double x, double y, int R, int G, int B, int anim, int front)
{
	//draw right leg
	if (anim == 1)
	{
		glPushMatrix();
		glTranslated(10, -30, 0);
		glRotated(45 * sin(0.1 * frame), 0, 0, 1);
		glColor4ub(R, G, B, 224);
		rectangle(-10, 0, 30, -40);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glTranslated(x, y, 0);
		glColor4ub(R, G, B, 224);
		rectangle(0, -30, 30, -40);
	}
	if (front == 1)
	{
		//draw body
		glColor3ub(R, G, B);
		EllipsePoly(0, 0, 30, 100, 1.5, 2.0);
		//draw eyes
		glColor3ub(0, 0, 0);
		EllipsePoly(25, 15, 15.0, 100, 2.0, 1.5);
		glColor3ub(255, 255, 255);
		EllipsePoly(25, 15, 13.0, 100, 2.0, 1.5);
	}
	else
	{
		//draw eyes
		glColor3ub(0, 0, 0);
		EllipsePoly(25, 15, 15.0, 100, 2.0, 1.5);
		glColor3ub(255, 255, 255);
		EllipsePoly(25, 15, 13.0, 100, 2.0, 1.5);
		//draw body
		glColor3ub(R, G, B);
		EllipsePoly(0, 0, 30, 100, 1.5, 2.0);
	}

	//draw left leg
	if (anim == 1)
	{
		glPushMatrix();
		glTranslated(-30, -30, 0);
		glRotated(-45 * sin(0.1 * frame), 0, 0, 1);
		glColor3ub(R, G, B);
		rectangle(-10, 0, 30, -40);
		glPopMatrix();
	}
	else
	{
		glColor3ub(R, G, B);
		rectangle(-40, -30, 30, -40);
	}
	glPopMatrix();
}

void deadBody(double x, double y, double w)
{

	double h = w * (2.0 / 3.0);

	//blood
	glColor3ub(230, 0, 0);
	EllipsePoly(x + 100, y - 80, 32.0, 100.0, 2, 3);

	// draw body of dead blue
	glColor3ub(0, 0, 230);
	rectangle(x, y, w * 1.8, h * 2.0); //w & h are the sizes for the rectangle
	glColor3ub(0, 0, 230);
	nGon(x, y - 32, 33.0, 100.0);
	glColor3ub(230, 0, 0);
	nGon(x, y - 32, 20.0, 100.0);
	glColor3ub(255, 255, 255);
	rectangle(x - 70, y + 60, w * 0.7, h * 0.4); //w & h are the sizes for the rectangle

	// draw bone triangle
	glColor3ub(255, 255, 255);
	glBegin(GL_POLYGON);
	glVertex2d(x - 55, y + 72);
	glVertex2d(x - 95, y + 96);
	glVertex2d(x - 95, y + 48);
	glEnd();

	//bloody rectangle
	glColor3ub(230, 0, 0);
	rectangle(x + 5, y, w * 0.22, h * 1.0); //w& h are the sizes for the rectangle
}

void stars()
{

	glBegin(GL_POINTS);
	glColor3ub(255, 255, 255);
	glVertex2i(150, 600);
	glVertex2i(300, 450);
	glVertex2i(450, 550);
	glVertex2i(600, 150);
	glVertex2i(750, 250);
	glVertex2i(900, 500);
	glVertex2i(-30, 300);
	glVertex2i(1000, 400);
	glVertex2i(-20, 250);
	glVertex2i(-40, 480);
	glVertex2i(-20, 640);
	glEnd();
}

void spaceship(double x, double y)
{
	glPushMatrix();
	glTranslated(x, y, 0);
	glBegin(GL_POLYGON);
	glColor3ub(91, 106, 109);
	glVertex2d(0, 0);
	glVertex2d(150, 0);
	glVertex2d(150, -100);
	glVertex2d(350, -30);
	glVertex2d(400, 50);
	glVertex2d(300, 100);
	glVertex2d(150, 100);
	glVertex2d(100, 50);
	glVertex2d(0, 50);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(175, 179, 142);
	glVertex2d(250, 50);
	glVertex2d(385, 50);
	glVertex2d(300, 90);
	glVertex2d(250, 90);

	glEnd();
	glPopMatrix();
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

void scene_1()
{

	//stars
	glPushMatrix();
	glTranslated(scene1_scrollX, 0, 0);
	stars();
	glPopMatrix();

	//RED
	glPushMatrix();
	glTranslated(SCREEN_WIDTH - 500 - scene1_scrollX, 350 + scene1_scrollX, 0);
	glRotated(-scene1_rotationX, 0, 0, 1.0);
	crew(0, 0, 197, 17, 17, 0, 1);
	glPopMatrix();

	//GREEN
	glPushMatrix();
	glTranslated(250 + scene1_scrollX, 400, 0);
	glRotated(scene1_rotationX, 0, 0, 1.0);
	crew(0, 0, 17, 127, 45, 0, 1);
	glPopMatrix();

	//BLUE
	glPushMatrix();
	glTranslated(640 - scene1_scrollX, 350 + scene1_scrollX, 0);
	glRotated(scene1_rotationX, 0, 0, 1.0);
	crew(0, 0, 19, 46, 209, 0, 1);
	glPopMatrix();

	//YELLOW
	glPushMatrix();
	glTranslated(0 + 3 * scene1_scrollX, scene1_scrollX, 0);
	glRotated(scene1_rotationX, 0, 0, 1.0);
	crew(0, 0, 245, 245, 87, 0, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(SCREEN_WIDTH / 2, 360, 0);
	glScaled(1 + 0.01 * (scene1_scrollX), 1 + 0.01 * (scene1_scrollX), 0);
	glColor3ub(255, 0, 0);
	renderSpacedBitmapString(-65, 0, GLUT_BITMAP_HELVETICA_18, "\"BETWEEN US\"");
	glPopMatrix();
	glColor3ub(255, 255, 255);
	renderSpacedBitmapString(SCREEN_WIDTH / 12, 130, GLUT_BITMAP_HELVETICA_18, "Created By:");
	renderSpacedBitmapString(SCREEN_WIDTH / 12, 110, GLUT_BITMAP_HELVETICA_18, "GROUP 17");
	glColor4ub(0, 0, 0, 256 - scene1_fade);
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	scene1_scrollX++;
	scene1_fadeEffect += 0.1;
	scene1_fade = -(scene1_fadeEffect * scene1_fadeEffect) + 256;
	scene1_rotationX += 5;
}

void scene_2()
{

	if (frame < 420)
	{
		//stars
		glPushMatrix();
		glTranslated(scene2_scrollX, 0, 0);
		stars();
		glPopMatrix();

		//ship
		glPushMatrix();
		glTranslated(scene2_translateX, 0, 0);
		spaceship(640, 360);
		glPopMatrix();

		scene2_scrollX++;
		scene2_translateX += 0.5;

		renderSpacedBitmapString(SCREEN_WIDTH / 2 - 100, 360, GLUT_BITMAP_HELVETICA_18, "Spaceship -->");
		renderSpacedBitmapString(SCREEN_WIDTH / 12, 130, GLUT_BITMAP_HELVETICA_18, "10 thousand chromosomes in the future");
	}
	else if (frame == 420)
	{
		scene2_scrollX = 0;
	}
	else
	{

		glPushMatrix();
		glTranslated(-scene2_scrollX, 0, 0);
		//Background
		glColor3ub(91, 106, 109);
		rectangle(0, 0, SCREEN_WIDTH + 200, SCREEN_HEIGHT);

		//floor
		glColor3ub(121, 136, 139);
		rectangle(0, 0, SCREEN_WIDTH + 200, 100);

		//door
		glColor3ub(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2d(850, 100);
		glVertex2d(1100, 100);
		glVertex2d(1100, 300);
		glVertex2d(850, 300);
		glEnd();

		//artwork
		glColor3ub(188, 121, 57);
		rectangle(450, 300, 300, 200); //frame
		glColor3ub(83, 148, 192);
		rectangle(460, 310, 280, 180); //sky
		glColor3ub(126, 203, 44);
		rectangle(460, 310, 280, 120); //grass
		glColor3ub(29, 34, 40);
		rectangle(460, 320, 280, 20);
		glColor3ub(128, 128, 128); //moutain
		glBegin(GL_POLYGON);
		glVertex2d(500, 400);
		glVertex2d(600, 400);
		glVertex2d(550, 450);
		glEnd();
		glColor3ub(128, 128, 128); //moutain
		glBegin(GL_POLYGON);
		glVertex2d(550, 400);
		glVertex2d(650, 400);
		glVertex2d(600, 450);
		glEnd();
		glColor3ub(255, 255, 255);
		nGon(600, 475, 10, 32);
		glPopMatrix();

		//BLUE
		glPushMatrix();
		glTranslated(5 * scene2_scrollX, 150, 0);
		crew(0, 0, 19, 46, 209, 1, 1);
		glPopMatrix();
		scene2_scrollX++;

		glPushMatrix();
		glTranslated(-scene2_scrollX, 0, 0);
		if (frame < 500 || rand() < RAND_MAX / 10)
		{
			spotlight(2 * SCREEN_WIDTH / 5 - 200, SCREEN_HEIGHT, 100, 200);
			spotlight(3 * SCREEN_WIDTH / 5, SCREEN_HEIGHT, 100, 200);
			spotlight(4 * SCREEN_WIDTH / 5 + 200, SCREEN_HEIGHT, 100, 200);
		}
		glPopMatrix();
	}
}
void scene_3()
{

	glPushMatrix();
	glTranslated(-scene2_scrollX, 0, 0);
	//Background
	glColor3ub(91, 106, 109);
	rectangle(0, 0, SCREEN_WIDTH + 200, SCREEN_HEIGHT);

	//floor
	glColor3ub(121, 136, 139);
	rectangle(0, 0, SCREEN_WIDTH + 200, 100);

	//door
	glColor3ub(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(850, 100);
	glVertex2d(1100, 100);
	glVertex2d(1100, 300);
	glVertex2d(850, 300);
	glEnd();

	//artwork
	glColor3ub(188, 121, 57);
	rectangle(450, 300, 300, 200); //frame
	glColor3ub(83, 148, 192);
	rectangle(460, 310, 280, 180); //sky
	glColor3ub(126, 203, 44);
	rectangle(460, 310, 280, 120); //grass
	glColor3ub(29, 34, 40);
	rectangle(460, 320, 280, 20);
	glColor3ub(128, 128, 128); //moutain
	glBegin(GL_POLYGON);
	glVertex2d(500, 400);
	glVertex2d(600, 400);
	glVertex2d(550, 450);
	glEnd();
	glColor3ub(128, 128, 128); //moutain
	glBegin(GL_POLYGON);
	glVertex2d(550, 400);
	glVertex2d(650, 400);
	glVertex2d(600, 450);
	glEnd();
	glColor3ub(255, 255, 255);
	nGon(600, 475, 10, 32);

	glPopMatrix();
	/* glBegin(GL_POLYGON);
		glVertex2d(850,100);
		glVertex2d(1100,100);
		glVertex2d(1100,300);
		glVertex2d(850,300);
		glEnd(); */

	//BLUE
	glPushMatrix();
	glTranslated(5 * scene2_scrollX, 150, 0);
	crew(0, 0, 19, 46, 209, 0, 1);
	glPopMatrix();

	//dark
	glColor4ub(0, 0, 0, 128);
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (frame < 700)
	{
		glColor3ub(255, 255, 255);
		renderSpacedBitmapString(1000, 350, GLUT_BITMAP_HELVETICA_18, "???");
	}
	if (frame >= 701 && frame < 850)
	{
		glColor3ub(255, 255, 255);
		renderSpacedBitmapString(1000, 350, GLUT_BITMAP_HELVETICA_18, "Ah shoot, electric is down...");
	}
}
void scene_4()
{
	electricalBox(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100);
	//BLUE
	glPushMatrix();
	if (frame < 960)
	{
		glTranslated(0 + 1 * frame - 900, 150, 0);
	}
	glScaled(10, 10, 0);
	crew(0, 0, 19, 46, 209, 0, 0);
	glPopMatrix();

	if (frame >= 960 && frame < 1020)
	{

		glColor3ub(255, 255, 255);
		renderSpacedBitmapString(350, 640, GLUT_BITMAP_HELVETICA_18, "Hmm strange");
	}
	if (frame >= 1020 && frame < 1080)
	{

		glColor3ub(255, 255, 255);
		renderSpacedBitmapString(350, 640, GLUT_BITMAP_HELVETICA_18, "Should be a quick fix");
	}

	if (frame >= 1080 && frame < 1140)
	{

		//WIRES//
		// draw red wire
		glColor3ub(204, 0, 0);
		rectangle(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 200, (frame - 1080) / 30 * 100 * 3.1, 100 * (0.8 / 9.0));
		// draw yellow wire
		glColor3ub(255, 204, 0);
		rectangle(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 140, (frame - 1080) / 30 * 100 * 3.1, 100 * (0.8 / 9.0));

		//draw pink wire
		glColor3ub(240, 21, 124);
		glLineWidth(6.0);
		line(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 20, (frame - 1080) / 20 * 320.0, (frame - 1080) / 30 * 65.0);

		//draw blue wire
		glColor3ub(0, 102, 255);
		glLineWidth(6.0);
		line(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 90, (frame - 1080) / 20 * 320.0, (frame - 1080) / 30 * -60.0);
	}
	if (frame >= 1140)
	{

		//WIRES//
		// draw red wire
		glColor3ub(204, 0, 0);
		rectangle(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 200, 100 * 3.1, 100 * (0.8 / 9.0));
		// draw yellow wire
		glColor3ub(255, 204, 0);
		rectangle(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 140, 100 * 3.1, 100 * (0.8 / 9.0));

		//draw pink wire
		glColor3ub(240, 21, 124);
		glLineWidth(6.0);
		line(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 20, 320.0, 65.0);

		//draw blue wire
		glColor3ub(0, 102, 255);
		glLineWidth(6.0);
		line(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 90, 320.0, -60.0);

		if (frame < 1200)
		{
			//red
			glPushMatrix();
			glTranslated(1000, 150, 0);
			glScaled(-5, 5, 0);
			crew(0, 0, (frame - 1140) / 60 * 197, (frame - 1140) / 60 * 17, (frame - 1140) / 60 * 17, 0, 1);
			glPopMatrix();
		}
		else
		{
			//red
			glPushMatrix();
			glTranslated(1000, 150, 0);
			glScaled(-5, 5, 0);
			crew(0, 0, 197, 17, 17, 0, 1);
			glPopMatrix();

			glColor3ub(255, 255, 255);
			if (frame < 1260)
			{
				
			renderSpacedBitmapString(350, 640, GLUT_BITMAP_HELVETICA_18, "Oh hi Red");
			}
			

			if (frame > 1260)
			{
				//red
				glPushMatrix();
				glTranslated(1000-(frame-1260), 150, 0);
				glScaled(-10, 10, 0);
				crew(0, 0, 197, 17, 17, 0, 1);
				glColor3ub(128,128,128);
				glBegin(GL_POLYGON);
				glVertex2d(5+10*sin(frame*0.5),10);
				glVertex2d(-45+10*sin(frame*0.5),10);
				glVertex2d(-45+10*sin(frame*0.5),30);
				glEnd();
				glPopMatrix();

				glColor3ub(255, 255, 255);
				renderSpacedBitmapString(350, 640, GLUT_BITMAP_HELVETICA_18, "HEY WHAT U DOIN?!");

				glColor4ub(255,0,0,255*(frame-1260)/240);
				rectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
			}
		}
	}
}
void scene_5()
{
	glPushMatrix();
	glTranslated(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,0);
	deadBody(0, 0, 100);
	glPopMatrix();

	ghost(3*SCREEN_WIDTH/4, SCREEN_HEIGHT/2 + 200, 19, 46, 209, 1);
}
void scene_6()
{
}
void scene_7()
{
}
void scene_8()
{
}
void scene_9()
{

	table(SCREEN_WIDTH / 2, 50, 300);
	spotlight(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 300, 500);
	// draw floor
	glColor3ub(155, 155, 155);
	rectangle(0, 0, SCREEN_WIDTH, 50);
}
void scene_10()
{
}
void scene_11()
{

	imposter(SCREEN_WIDTH / 2, 50);
	spotlight(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 300, 500);
	//ghost(SCREEN_WIDTH / 2, 0);
	// draw floor
	glColor3ub(155, 155, 155);
	rectangle(0, 0, SCREEN_WIDTH, 50);
}

/* 
========================
Scenes
========================
 */

void display()
{
	frame++;
	std::cout << frame << std::endl; //print frame number
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);

	if (frame <= 300) //5 seconds scene 1
	{
		scene_1();
	}
	else if (frame > 300 && frame <= 600) //5 seconds scene 2
	{
		scene_2();
	}
	else if (frame > 600 && frame <= 900) //5 seconds scene 3
	{
		scene_3();
	}
	else if (frame > 900 && frame <= 1500) //10 seconds scene 4
	{
		scene_4();
	}
	else if (frame > 1500 && frame <= 1800) //5 seconds scene 5
	{
		scene_5();
	}
	else if (frame > 1800 && frame <= 2100) //5 seconds scene 6
	{
		scene_6();
	}
	else if (frame > 2100 && frame <= 2400) //5 seconds scene 7
	{
		scene_7();
	}
	else if (frame > 2400 && frame <= 2700) //5 seconds scene 8
	{
		scene_8();
	}
	else if (frame > 2700 && frame <= 3300) //10 seconds scene 9
	{
		scene_9();
	}
	else if (frame > 3300 && frame <= 3600) //5 seconds scene 10
	{
		scene_10();
	}
	else if (frame > 3600 && frame <= 3900) //5 seconds scene 11
	{
		scene_11();
	}

	glFlush();
	glutSwapBuffers();
}

void initGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //set background to black
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}

void Timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, Timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);							 //initialise glut library
	glutInitDisplayMode(GLUT_DOUBLE);				 //set displaymode to double buffered window
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //set window size
	glutCreateWindow("our program \u262d");			 //set window name
	glutDisplayFunc(display);						 //callback function, redraw when window is updated
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutTimerFunc(0, Timer, 0); //execute function every frame
	initGL();
	glutMainLoop();
}