//一個cube可以任意軸旋轉，軸由滑鼠點決定

//一個cube可以任意軸旋轉，軸由滑鼠點決定
#include <stdio.h> 
#include <stdlib.h>

//#include <freeglut.h>

#include<GL/glut.h>
#include<math.h>
#define PI 3.14159265
void ChangeSize(int, int);
void RenderScene(void);
void buildPopupMenu();
void myKeyboard(unsigned char, int, int);
void mySpecialKey(int, int, int);
void myMouse(int, int, int, int);
void RotateMatrix(float, GLfloat, GLfloat, GLfloat);

bool mouseLeftDown;
float tx = 0;
float ty = 0;
float tz = 0;
float thetaX = 0;
float thetaY = 0;
float thetaZ = 0;
float thetaA = 0;

int XX, YY;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(600, 80);
	glutCreateWindow(" Cuuuuuuuuuuuuuuube");

	buildPopupMenu();
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKey);
	glutMouseFunc(myMouse);

	void initGL();

	glutMainLoop();
	return 0;
}

void menuSelect(int option)
{
	switch (option)
	{
	case 0:
		glShadeModel(GL_FLAT);
		glutPostRedisplay();
		break;
	case 1:
		glShadeModel(GL_SMOOTH);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void buildPopupMenu()
{
	int menu_id;
	menu_id = glutCreateMenu(menuSelect);
	glutAddMenuEntry("Flat", 0);
	glutAddMenuEntry("Smooth", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ChangeSize(int w, int h)
{
	printf("Window Size= %d X %d\n", w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300, 300, -300, 300, -300, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(0, 0, 5.0f, 0, 0, 0, 0, 1, 0);

	glBegin(GL_LINES);
	// draw line for x axis
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10000, 0.0, 0.0);
	// draw line for y axis
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10000.0, 0.0);
	// draw line for Z axis
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10000.0);
	glEnd();

	GLfloat AA = XX * XX + YY * YY;
	GLfloat A1 = cos(thetaA * PI / 180.0) + (1 - cos(thetaA * PI / 180.0)) * XX * XX / AA;
	GLfloat A2 = (1 - cos(thetaA * PI / 180.0)) * XX * YY / AA;
	GLfloat A3 = (sin(thetaA * PI / 180.0)) * YY / sqrt(AA);
	GLfloat A4 = (1 - cos(thetaA * PI / 180.0)) * YY * XX / AA;
	GLfloat A5 = cos(thetaA * PI / 180.0) + (1 - cos(thetaA * PI / 180.0)) * YY * YY / AA;
	GLfloat A6 = -(sin(thetaA * PI / 180.0)) * XX / sqrt(AA);
	GLfloat A7 = -(sin(thetaA * PI / 180.0)) * YY / sqrt(AA);
	GLfloat A8 = sin(thetaA * PI / 180.0) * XX / sqrt(AA);
	GLfloat A9 = cos(thetaA * PI / 180.0);

	GLfloat RotateMatrix[] =
	{
		A1, A2, A3, 0.0,
		A4, A5, A6, 0.0,
		A7, A8, A9, 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	GLfloat translateMatrix[] =
	{
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	tx,  ty,  tz,  1.0
	};
	GLfloat rotMatrixX[] =
	{
	1.0, 0.0, 0.0, 0.0,
	0.0, cos(thetaX * PI / 180.0), -sin(thetaX * PI / 180.0), 0.0,
	0.0, sin(thetaX * PI / 180.0), cos(thetaX * PI / 180.0), 0.0,
	0.0, 0.0, 0.0, 1.0
	};
	GLfloat rotMatrixY[] =
	{
	cos(thetaY * PI / 180.0), 0.0, sin(thetaY * PI / 180.0), 0.0,
	0.0, 1.0, 0.0, 0.0,
	-sin(thetaY * PI / 180.0), 0.0, cos(thetaY * PI / 180.0), 0.0,
	0.0, 0.0, 0.0, 1.0
	};
	GLfloat rotMatrixZ[] =
	{
	cos(thetaZ * PI / 180.0), -sin(thetaZ * PI / 180.0), 0.0, 0.0,
	sin(thetaZ * PI / 180.0), cos(thetaZ * PI / 180.0), 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
	};

	glMultMatrixf(RotateMatrix);
	glMultMatrixf(translateMatrix);
	glMultMatrixf(rotMatrixX);
	glMultMatrixf(rotMatrixY);
	glMultMatrixf(rotMatrixZ);

	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(50);

	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(XX, YY, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(XX, YY, 0.0);
	glEnd();

	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		thetaX = 0;
		thetaY = 0;
		thetaZ = 0;
		thetaA = 0;
		tx = 0;
		ty = 0;
		tz = 0;
		break;
	case 'q':
		thetaX += 3;
		break;
	case 'w':
		thetaX -= 3;
		break;
	case 'a':
		thetaY += 3;
		break;
	case 's':
		thetaY -= 3;
		break;
	case 'z':
		thetaZ += 3;
		break;
	case 'x':
		thetaZ -= 3;
		break;

	case 'n':
		thetaA += 3;
		break;
	case 'm':
		thetaA -= 3;
		break;

	}
	glutPostRedisplay();
}

void mySpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		tx -= 10;
		break;
	case GLUT_KEY_RIGHT:
		tx += 10;
		break;
	case GLUT_KEY_UP:
		ty += 10;
		break;
	case GLUT_KEY_DOWN:
		ty -= 10;
		break;
	}
	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseLeftDown = true;
		XX = x - 300;
		YY = 300 - y;
	}
}
