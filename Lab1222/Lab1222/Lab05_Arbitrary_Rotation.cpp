/*
 * OGL01Shape3D.cpp: 3D Shapes
 */

#define _USE_MATH_DEFINES

#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <cmath>
#include "function.h"
 // #include <functional> //without .h
#include "draw.h"
#include "global.h"
#include "config.h"

Config config;

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	// Render a pyramid consists of 4 triangles
	glLoadIdentity();                  // Reset the model-view matrix
	gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, 1, 0);
	// glRotatef(-30, 0, 1, 0);
	//glRotatef(15, 1, 0, 0);

	draw_Axis();
	if (Click)
		draw_Click(clickX, clickY, clickZ, radius);

	glLoadIdentity();                  // Reset the model-view matrix
	gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, 1, 0);
	//glTranslatef(tx, ty, tz);  // Move left and into the screen

	glMultMatrixf(config.getTranslateMatrix(tx, ty, tz));


	glMultMatrixf(config.getRotateX(thetaX));
	//glRotatef(thetaX, 1, 0, 0);

	glMultMatrixf(config.getRotateY(thetaY));
	//glRotatef(thetaY, 0, 1, 0);

	glMultMatrixf(config.getRotateZ(thetaZ));
	//glRotatef(thetaZ, 0, 0, 1);

	draw_Pyramid();

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

void arbitrary_Rotate() {

}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	config = Config();
	// auto func = std::bind(&Config::mySpecialKey, &config);
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(640, 480);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKey);
	glutMouseFunc(mouseClicks);
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}
