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
	draw_Click(config.clickX, config.clickY, config.clickZ, radius);

	glLoadIdentity();                  // Reset the model-view matrix
	gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, 1, 0);
	//glTranslatef(tx, ty, tz);  // Move left and into the screen

	//arbitrary_Rotate(clickX, clickY, clickZ);


	//glMultMatrixf(config.getTranslateMatrix(tx, ty, tz));


	//glMultMatrixf(config.getRotateX(thetaX));
	//glRotatef(thetaX, 1, 0, 0);

	//glMultMatrixf(config.getRotateY(thetaY));
	//glRotatef(thetaY, 0, 1, 0);

	//glMultMatrixf(config.getRotateZ(thetaZ));
	//glRotatef(thetaZ, 0, 0, 1);

	//draw_Pyramid();

	//glLoadIdentity();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	config.Draw();

	//lamp.Draw();
	//config.Draw();

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
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
	float lengthX = config.lengthX;
	float lengthY = config.lengthY;
	float lengthZ = config.lengthZ;

	auto max_array = { lengthX,lengthY,lengthZ };
	float max = *std::max_element(max_array.begin(), max_array.end());

	std::cout << "max:" << max << std::endl;

	config.Set_Ortho_Width_Height(300, 300, 300);
	//config.Set_Grid_Width_Height();

	glOrtho(-config.orthoX, config.orthoX, -config.orthoY, config.orthoY, -config.orthoZ, config.orthoZ);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {

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

	config.Set_Grid_Amount(25);

	// 建立右建選單
	buildPopupMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	initGL();                       // Our own OpenGL initialization


	glutMainLoop();                 // Enter the infinite event-processing loop


	return 0;
}
