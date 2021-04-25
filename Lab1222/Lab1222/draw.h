#pragma once
#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <cmath>

void draw_Axis() {
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);     // Red X axis
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);     // Green Y axis
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);     // Blue Z axis
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);

	glEnd();
}

void draw_Pyramid() {
	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	   // Front
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -2.0f, 1.0f);
	glVertex3f(1.0f, -2.0f, 1.0f);

	// Right
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -2.0f, 1.0f);
	glVertex3f(1.0f, -2.0f, -1.0f);

	// Back
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -2.0f, -1.0f);
	glVertex3f(-1.0f, -2.0f, -1.0f);

	// Left
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -2.0f, -1.0f);
	glVertex3f(-1.0f, -2.0f, 1.0f);

	glColor3f(0, 1, 0); glVertex3f(-1.0f, -2.0f, 1.0f);
	glColor3f(0, 0, 1); glVertex3f(1.0f, -2.0f, 1.0f);
	glColor3f(1, 0, 0); glVertex3f(1.0f, -2.0f, -1.0f);


	glColor3f(0, 0, 1); glVertex3f(-1.0f, -2.0f, 1.0f);
	glColor3f(0, 1, 0); glVertex3f(1.0f, -2.0f, -1.0f);
	glColor3f(1, 0, 0); glVertex3f(-1.0f, -2.0f, -1.0f);

	glEnd();   // Done drawing the pyramid (triangle part)
}

void draw_Click(float clickX, float clickY, float clickZ, float radius) {
	//Set Drawing Color - Will Remain this color until otherwise specified

	glColor3f(0.2f, 0.3f, 0.5f);  //Some type of blue

	//Draw Circle
	glBegin(GL_POLYGON);
	//Change the 6 to 12 to increase the steps (number of drawn points) for a smoother circle
	//Note that anything above 24 will have little affect on the circles appearance
	//Play with the numbers till you find the result you are looking for
	//Value 1.5 - Draws Triangle
	//Value 2 - Draws Square
	//Value 3 - Draws Hexagon
	//Value 4 - Draws Octagon
	//Value 5 - Draws Decagon
	//Notice the correlation between the value and the number of sides
	//The number of sides is always twice the value given this range
	for (double i = 0; i < 2 * M_PI; i += M_PI / 24) //<-- Change this Value
		glVertex3f( (float)(clickX + (cos(i) * radius)), (float)(clickY + (sin(i) * radius)), 0.0f);
	glEnd();
	//Draw Circle

	//Draw Line
	glBegin(GL_LINES);
	glVertex3f(clickX, clickY, clickZ);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
}