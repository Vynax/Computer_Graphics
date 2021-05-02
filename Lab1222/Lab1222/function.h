#pragma once

#define angleX 0
#define angleY -30
#define angleZ 0
#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include "global.h"

float getSin(float theta) {
	return (float)sin(theta * M_PI / 180.0);
}

float getCos(float theta) {
	return (float)cos(theta * M_PI / 180.0);
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
		tx -= 0.2f;
		break;
	case GLUT_KEY_RIGHT:
		tx += 0.2f;
		break;
	case GLUT_KEY_UP:
		ty += 0.2f;
		break;
	case GLUT_KEY_DOWN:
		ty -= 0.2f;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void mouseClicks(int button, int state, int x, int y) {     //當按下滑鼠左鍵時會執行裡面
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//do something
		// if (Click == false) {


		if (x > glutGet(GLUT_WINDOW_WIDTH) / 2)
			clickX = (float)(x - glutGet(GLUT_WINDOW_WIDTH) / 2);
		else
			clickX = (float)(-(glutGet(GLUT_WINDOW_WIDTH) / 2 - x));

		if (y > glutGet(GLUT_WINDOW_HEIGHT) / 2)
			clickY = (float)(-(y - glutGet(GLUT_WINDOW_HEIGHT) / 2));
		else
			clickY = (float)(glutGet(GLUT_WINDOW_HEIGHT) / 2 - y);

		clickX = clickX / glutGet(GLUT_WINDOW_WIDTH) * range;
		clickY = clickY / glutGet(GLUT_WINDOW_HEIGHT) *range;

		std::cout << "Width:" << glutGet(GLUT_WINDOW_WIDTH) << "Height:" << glutGet(GLUT_WINDOW_HEIGHT) << "x:" << x << "y:" << y;
		std::cout << "ClickX:" << clickX << "ClickY:" << clickY << std::endl;


		//Click = true;
	//}
	}
}
