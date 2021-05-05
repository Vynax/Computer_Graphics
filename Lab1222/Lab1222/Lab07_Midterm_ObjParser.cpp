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
#include "menu.h"
#include "objloader.h"

void arbitrary_Rotate(float a, float b, float c);

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

	glLoadIdentity();                  // Reset the model-view matrix
	gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, 1, 0);
	//glTranslatef(tx, ty, tz);  // Move left and into the screen

	draw_Click(clickX, clickY, clickZ, radius);
	//arbitrary_Rotate(clickX, clickY, clickZ);


	glMultMatrixf(config.getTranslateMatrix(tx, ty, tz));


	glMultMatrixf(config.getRotateX(thetaX));
	//glRotatef(thetaX, 1, 0, 0);

	glMultMatrixf(config.getRotateY(thetaY));
	//glRotatef(thetaY, 0, 1, 0);

	glMultMatrixf(config.getRotateZ(thetaZ));
	//glRotatef(thetaZ, 0, 0, 1);

	//draw_Pyramid();
	lamp.Draw();

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

//假設忽略Z軸，任意軸旋轉XY平面上的軸
void arbitrary_Rotate(float a, float b, float c) {
	float sinx = b / sqrt(pow(b, 2) + pow(c, 2));
	float cosx = c / sqrt(pow(b, 2) + pow(c, 2));

	float siny = a / sqrt(pow(a, 2) + pow(c, 2));
	float cosy = (c / sqrt(pow(a, 2) + pow(c, 2)));

	//Rx(theta)
	GLfloat *matrixX = config.getRotateX(sinx, cosx);
	glMultMatrixf(matrixX);
	//Ry(theta)
	GLfloat *matrixY = config.getRotateY(siny, cosy);
	glMultMatrixf(matrixY);
	//Rz
	thetaZ += 3;
	glMultMatrixf(config.getRotateZ(thetaZ));

	//Ry^-1(theta)
	glMultMatrixf(config.getTransPose(matrixY));

	//Rx^-1(theta)
	glMultMatrixf(config.getTransPose(matrixX));

	std::cout << "arbitrary_Rotate" << std::endl;
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
	// gluPerspective(45.0f, aspect, 0.1f, 100.0f);
	glOrtho(-25, 25, -25, 25, -25, 25);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	config = Config();
	lamp = ObjLoader("lamp.obj");
	// auto func = std::bind(&Config::mySpecialKey, &config);
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(800, 800);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKey);
	glutMouseFunc(mouseClicks);

	// 建立右建選單
	buildPopupMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}
