/*
 * OGL01Shape3D.cpp: 3D Shapes
 */

#define _USE_MATH_DEFINES
#include "TGATexture.h"
#include <string>
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
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */

#include "shared/math3d.h"    // 3D Math Library

#define GL_CLAMP_TO_EDGE 0x812F

// Light and material Data
GLfloat fLightPos[4] = { -100.0f, 100.0f, 50.0f, 1.0f };  // Point source
GLfloat fNoLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat fLowLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat fBrightLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

#define BRICK_TEXTURE   0
//#define GRASS_TEXTURE   1
#define FLOOR_TEXTURE   1
#define WOOD_TEXTURE   2
//#define SPHERE_TEXTURE  2
#define NUM_TEXTURES    3

TextureImage texture[NUM_TEXTURES];

ObjLoader octahedron;
ObjLoader human;

GLfloat angleDiamond = 0.0f;  // Rotational angle for pyramid [NEW]
GLfloat angleHuman = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]

std::string str[] = { "kt_brick2e2.tga", "floor.tga", "wood_123.tga" };
/* Initialize OpenGL Graphics */

int initGL() {
    for (int i = 0; i < NUM_TEXTURES; i++) {
        char * filename = new char[str[i].size() + 1];
        std::copy(str[i].begin(), str[i].end(), filename);
        filename[str[i].size()] = '\0'; // don't forget the terminating 0

        if (!LoadTGA(&texture[i], filename))
            return GL_FALSE;

        delete[] filename;
    }

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);
    //glClearDepth(1.0f);
    //glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

    glEnable(GL_DEPTH_TEST);    // Hidden surface removal
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);     // Do not calculate inside of jet

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    return GL_TRUE;
}

///////////////////////////////////////////////////////////
// Draw the ground as a series of triangle strips
void DrawGround(void)
{
    GLfloat fExtent = 20.0f;
    GLfloat fStep = 1.0f;
    GLfloat y = -0.4f;
    GLfloat iStrip, iRun;
    GLfloat s = 0.0f;
    GLfloat t = 0.0f;
    GLfloat texStep = 1.0f / (fExtent * .075f);

    glBindTexture(GL_TEXTURE_2D, texture[FLOOR_TEXTURE].texID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    for (iStrip = -fExtent; iStrip <= fExtent; iStrip += fStep)
    {
        t = 0.0f;
        glBegin(GL_TRIANGLE_STRIP);

        for (iRun = fExtent; iRun >= -fExtent; iRun -= fStep)
        {
            glTexCoord2f(s, t);
            glNormal3f(0.0f, 1.0f, 0.0f);   // All Point up
            glVertex3f(iStrip, y, iRun);

            glTexCoord2f(s + texStep, t);
            glNormal3f(0.0f, 1.0f, 0.0f);   // All Point up
            glVertex3f(iStrip + fStep, y, iRun);

            t += texStep;
        }
        glEnd();
        s += texStep;
    }
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    glLoadIdentity();                  // Reset the model-view matrix
    gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, 1, 0);

    //draw_Axis();

    glLoadIdentity();                  // Reset the model-view matrix
    gluLookAt(0, 0, tz + 15.0f, 0, 0, 0, 0, 1, 0);

    // Position light before any other transformations
    glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);

    // Draw the ground
    glColor3f(1.0f, 1.0f, 1.0f);
    DrawGround();

    glTranslatef(tx, ty, tz);  // Move left and into the screen

    //glRotatef(thetaX, 1, 0, 0);

    //glRotatef(thetaY, 0, 1, 0);

    //glRotatef(thetaZ, 0, 0, 1);

    //draw_Pyramid();
    //lamp.Draw();
    //config.Draw();
    vertex center;
    center.x = 0.0f;
    center.y = 0.0f;
    center.z = 0.0f;

    glLoadIdentity();                  // Reset the model-view matrix
    gluLookAt(0, 0, tz + 15.0f, 0, 0, 0, 0, 1, 0);

    glRotatef(angleHuman, 0, 1, 0);
    glTranslatef(-0.4, 1, -2);

    human.Draw(center, texture[WOOD_TEXTURE].texID);

    glLoadIdentity();                  // Reset the model-view matrix
    gluLookAt(0, 0, tz + 15.0f, 0, 0, 0, 0, 1, 0);

    glRotatef(angleDiamond, 0, 1, 0);
    glTranslatef(3, 1, 0);

    octahedron.Draw(center, texture[BRICK_TEXTURE].texID);

    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

    angleDiamond += 0.5f;
    angleHuman -= 0.2f;
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
    //float lengthX = config.lengthX;
    //float lengthY = config.lengthY;
    //float lengthZ = config.lengthZ;

    //auto max_array = { lengthX,lengthY,lengthZ };
    //float max = *std::max_element(max_array.begin(), max_array.end());

    //std::cout << "max:" << max << std::endl;

    //glOrtho(-max, max, -max, max, -max, max + 15);
    gluPerspective(35.0f, aspect, 1.0f, 50.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    //lamp = ObjLoader("lamp.obj");
    //config.SetObjectXYZ(&lamp);
    //teapot = ObjLoader("teapot.obj");
    //config.SetObjectXYZ(&teapot);
    octahedron = ObjLoader("octahedron.obj");
    human = ObjLoader("humanoid_quad.obj");

    srand(time(NULL));
    // auto func = std::bind(&Config::mySpecialKey, &config);
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(800, 800);   // Set the window's initial width & height
    glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKey);
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    //glutMouseFunc(mouseClicks);

    // 建立右建選單
    //buildPopupMenu();
    //glutAttachMenu(GLUT_RIGHT_BUTTON);

    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
