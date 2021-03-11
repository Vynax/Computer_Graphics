/***C/C++  http://bbs.csdn.net/topics/100091584***/
#include <stdio.h> 
#include <stdlib.h>
/***freeglut***/
#include <GL/freeglut.h>

void ChangeSize(int, int);
void RenderScene(void);
void buildPopupMenu();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(600, 80);
	glutCreateWindow("Simple Cube");

	buildPopupMenu();
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
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
	glOrtho(-4, 4, -4, 4, -4, 4);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void RenderScene(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);
	// gluLookAt(0, 0, 1.0f, 0, 0, 0, 0, 1, 0);
	glRotatef(30.0f, 1.0, 0.0, 0.0);
	glRotatef(60.0f, 0.0, 1.0, 0.0);
	glRotatef(30.0f, 0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLES);

	// red
	glColor3f(1, 0, 0); glVertex3f(4, 4, 0);
	glColor3f(1, 0, 0); glVertex3f(-4, 4, 0);
	glColor3f(1, 0, 0); glVertex3f(-4, -4, 0);

	glColor3f(1, 0, 0); glVertex3f(-4, -4, 0);
	glColor3f(1, 0, 0); glVertex3f(4, -4, 0);
	glColor3f(1, 0, 0); glVertex3f(4, 4, 0);

	// green
	glColor3f(0, 1, 0); glVertex3f(-4, 4, -4);
	glColor3f(0, 1, 0); glVertex3f(-4, 4, 0);
	glColor3f(0, 1, 0); glVertex3f(-4, -4, 0);


	glColor3f(0, 1, 0); glVertex3f(-4, 4, -4);
	glColor3f(0, 1, 0); glVertex3f(-4, -4, 0);
	glColor3f(0, 1, 0); glVertex3f(-4, -4, -4);

	// blue
	glColor3f(0, 0, 1); glVertex3f(4, 4, 0);
	glColor3f(0, 0, 1); glVertex3f(4, 4, -4);
	glColor3f(0, 0, 1); glVertex3f(-4, 4, -4);

	glColor3f(0, 0, 1); glVertex3f(4, 4, 0);
	glColor3f(0, 0, 1); glVertex3f(-4, 4, -4);
	glColor3f(0, 0, 1); glVertex3f(-4, 4, 0);





	glEnd();
	glutSwapBuffers();

}