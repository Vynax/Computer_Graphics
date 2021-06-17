﻿#include "TGATexture.h"
#include <string>

TextureImage texture[1];

GLfloat xRot, yRot, zRot; //control cube's rotation

int init()
{
	std::string str = "stone.tga";
	char * filename = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), filename);
	filename[str.size()] = '\0'; // don't forget the terminating 0

	if (!LoadTGA(&texture[0], filename))
		return GL_FALSE;
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return GL_TRUE;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);

	glBegin(GL_QUADS);
	// Front Face
	// Bottom Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	// Top Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Back Face
	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	// Top Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Top Face
	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	// Bottom Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	// Top Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Bottom Face
	// Top Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	// Bottom Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Right face
	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	// Bottom Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Left Face
	// Bottom Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	// Top Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	if (0 == h)
		h = 1;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		xRot += 1.0f;
		glutPostRedisplay();
		break;
	case 'y':
		yRot += 1.0f;
		glutPostRedisplay();
		break;
	case 'z':
		zRot += 1.0f;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Texture Map");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
