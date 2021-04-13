/*
 * OGL01Shape3D.cpp: 3D Shapes
 */

#define angleX 0
#define angleY -30
#define angleZ 0
#define _USE_MATH_DEFINES

#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <cmath>

 /* Global variables */
char title[] = "Lab 05 Arbitrary Rotation";
float tx = 0, ty = 0, tz = 0;
float thetaX = angleX, thetaY = angleY, thetaZ = angleZ;
float range = 15;
float clickX = 0, clickY = 0, clickZ = 0;
float radius = 0.2;
bool Click = false;

GLfloat translateMatrix[] = {
1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };

GLfloat rotMatrix_X[] = {
1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };

GLfloat rotMatrix_Y[] = {
1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };

GLfloat rotMatrix_Z[] = {
1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };

float getSin(float);
float getCos(float);

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


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

void draw_Click() {
	//Set Drawing Color - Will Remain this color until otherwise specified

	glColor3f(0.2, 0.3, 0.5);  //Some type of blue

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
		glVertex3f(clickX + (cos(i) * radius), clickY + (sin(i) * radius), 0.0);
	glEnd();
	//Draw Circle

	//Draw Line
	glBegin(GL_LINES);
	glVertex3f(clickX, clickY, clickZ);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	// Render a pyramid consists of 4 triangles
	glLoadIdentity();                  // Reset the model-view matrix
	gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, 1, 0);
	//glRotatef(-30, 0, 1, 0);
	//glRotatef(15, 1, 0, 0);



	draw_Axis();
	if (Click)
		draw_Click();

	glLoadIdentity();                  // Reset the model-view matrix
	gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, 1, 0);
	//glTranslatef(tx, ty, tz);  // Move left and into the screen

	translateMatrix[12] = tx;
	translateMatrix[13] = ty;
	translateMatrix[14] = tz;
	glMultMatrixf(translateMatrix);
	//glRotatef(thetaX, 1, 0, 0);
	rotMatrix_X[5] = getCos(thetaX);
	rotMatrix_X[6] = getSin(thetaX);
	rotMatrix_X[9] = -getSin(thetaX);
	rotMatrix_X[10] = getCos(thetaX);
	glMultMatrixf(rotMatrix_X);

	rotMatrix_Y[0] = getCos(thetaY);
	rotMatrix_Y[2] = -getSin(thetaY);
	rotMatrix_Y[8] = getSin(thetaY);
	rotMatrix_Y[10] = getCos(thetaY);
	glMultMatrixf(rotMatrix_Y);
	//glRotatef(thetaY, 0, 1, 0);


	rotMatrix_Z[0] = getCos(thetaZ);
	rotMatrix_Z[1] = getSin(thetaZ);
	rotMatrix_Z[4] = -getSin(thetaZ);
	rotMatrix_Z[5] = getCos(thetaZ);
	glMultMatrixf(rotMatrix_Z);
	//glRotatef(thetaZ, 0, 0, 1);


	draw_Pyramid();


	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

float getSin(float theta) {
	return sin(theta * M_PI / 180.0);
}

float getCos(float theta) {
	return cos(theta * M_PI / 180.0);
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

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		Click = false;
		clickX = 0;
		clickY = 0;
		clickZ = 0;

		thetaX = angleX;
		thetaY = angleY;
		thetaZ = angleZ;
		tx = 0;
		ty = 0;
		tz = 0;
		break;
	case 'a':
		thetaY -= 3;
		break;
	case 'd':
		thetaY += 3;
		break;
	case 'w':
		thetaX -= 3;
		break;
	case 's':
		thetaX += 3;
		break;
	case 'z':
		thetaZ += 3;
		break;
	case 'x':
		thetaZ -= 3;
		break;
	default:
		break;
	}

	// std::cout << "thetaX:" << thetaX << std::endl;
	glutPostRedisplay();
}

void mySpecialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		tx -= 0.2;
		break;
	case GLUT_KEY_RIGHT:
		tx += 0.2;
		break;
	case GLUT_KEY_UP:
		ty += 0.2;
		break;
	case GLUT_KEY_DOWN:
		ty -= 0.2;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void mouseClicks(int button, int state, int x, int y) {     //當按下滑鼠左鍵時會執行裡面
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//do something
		if (Click == false) {


			if (x > glutGet(GLUT_WINDOW_WIDTH) / 2)
				clickX = x - glutGet(GLUT_WINDOW_WIDTH) / 2;
			else
				clickX = -(glutGet(GLUT_WINDOW_WIDTH) / 2 - x);

			if (y > glutGet(GLUT_WINDOW_HEIGHT) / 2)
				clickY = -(y - glutGet(GLUT_WINDOW_HEIGHT) / 2);
			else
				clickY = glutGet(GLUT_WINDOW_HEIGHT) / 2 - y;

			clickX = clickX / glutGet(GLUT_WINDOW_WIDTH) * range;
			clickY = clickY / glutGet(GLUT_WINDOW_HEIGHT) *range;

			std::cout << "Width:" << glutGet(GLUT_WINDOW_WIDTH) << "Height:" << glutGet(GLUT_WINDOW_HEIGHT) << "x:" << x << "y:" << y;
			std::cout << "ClickX:" << clickX << "ClickY:" << clickY << std::endl;


			Click = true;
		}
	}
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
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