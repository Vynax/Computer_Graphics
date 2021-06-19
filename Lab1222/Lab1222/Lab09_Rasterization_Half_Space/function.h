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

void int_swap(int *a, int*b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void myKeyboard(unsigned char key, int x, int y) {
    // std::cout << "key" << std::endl;
    switch (key) {
    case 'r':
        Click = false;
        config.clickX = 0;
        config.clickY = 0;
        config.clickZ = 0;

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
        tx -= 2.0f;
        break;
    case GLUT_KEY_RIGHT:
        tx += 2.0f;
        break;
    case GLUT_KEY_UP:
        ty += 2.0f;
        break;
    case GLUT_KEY_DOWN:
        ty -= 2.0f;
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

        float clickX, clickY;
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        if (x > width / 2)
            clickX = (float)(x - width / 2);
        else
            clickX = (float)(-(width / 2 - x));

        if (y > height / 2)
            clickY = (float)(-(y - height / 2));
        else
            clickY = (float)(height / 2 - y);

        config.Add_New_Click((int)(clickX * config.orthoX * 2 / width), (int)(clickY * config.orthoY * 2 / height));

        //config.clickX = clickX * config.orthoX * 2 / width;
        //config.clickY = clickY * config.orthoY * 2 / height;

        //clickX = clickX / width * range;
        //clickY = clickY / height * range;

        std::cout << "Width:" << width << " Height:" << height << " x:" << x << " y:" << y;
        std::cout << " ClickX:" << config.clickX << " ClickY:" << config.clickY << std::endl;


        //Click = true;
    //}
    }
}
