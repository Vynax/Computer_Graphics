#include "TGATexture.h"
#include <string>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include "shared/math3d.h"    // 3D Math Library

#define GL_CLAMP_TO_EDGE 0x812F

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return GL_TRUE;
}

void display()
{
    M3DVector3f vNormal;
    M3DVector3f vCorners[5] = { { 0.0f, .80f, 0.0f },     // Top           0
                              { -0.5f, 0.0f, -.50f },    // Back left     1
                              { 0.5f, 0.0f, -0.50f },    // Back right    2
                              { 0.5f, 0.0f, 0.5f },      // Front right   3
                              { -0.5f, 0.0f, 0.5f } };    // Front left    4
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //glTranslatef(0.0f, 0.0f, -5.0f);
    //glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    //glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    //glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    // Move object back and do in place rotation
    glTranslatef(0.0f, -0.25f, -4.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, texture[0].texID);

    //glBegin(GL_QUADS);
    //// Front Face
    //// Bottom Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 0.0f);
    //glVertex3f(-1.0f, -1.0f, 1.0f);
    //// Bottom Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 0.0f);
    //glVertex3f(1.0f, -1.0f, 1.0f);
    //// Top Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 1.0f);
    //glVertex3f(1.0f, 1.0f, 1.0f);
    //// Top Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 1.0f);
    //glVertex3f(-1.0f, 1.0f, 1.0f);
    //glEnd();

    //glBindTexture(GL_TEXTURE_2D, texture[0].texID);
    //glBegin(GL_QUADS);
    //// Back Face
    //// Bottom Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 0.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //// Top Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 1.0f);
    //glVertex3f(-1.0f, 1.0f, -1.0f);
    //// Top Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 1.0f);
    //glVertex3f(1.0f, 1.0f, -1.0f);
    //// Bottom Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 0.0f);
    //glVertex3f(1.0f, -1.0f, -1.0f);
    //glEnd();

    //glBindTexture(GL_TEXTURE_2D, texture[0].texID);
    //glBegin(GL_QUADS);
    //// Top Face
    //// Top Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 1.0f);
    //glVertex3f(-1.0f, 1.0f, -1.0f);
    //// Bottom Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 0.0f);
    //glVertex3f(-1.0f, 1.0f, 1.0f);
    //// Bottom Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 0.0f);
    //glVertex3f(1.0f, 1.0f, 1.0f);
    //// Top Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 1.0f);
    //glVertex3f(1.0f, 1.0f, -1.0f);
    //glEnd();

    //glBindTexture(GL_TEXTURE_2D, texture[0].texID);
    //glBegin(GL_QUADS);
    //// Bottom Face
    //// Top Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //// Top Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 1.0f);
    //glVertex3f(1.0f, -1.0f, -1.0f);
    //// Bottom Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 0.0f);
    //glVertex3f(1.0f, -1.0f, 1.0f);
    //// Bottom Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 0.0f);
    //glVertex3f(-1.0f, -1.0f, 1.0f);
    //glEnd();

    //glBindTexture(GL_TEXTURE_2D, texture[0].texID);
    //glBegin(GL_QUADS);
    //// Right face
    //// Bottom Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 0.0f);
    //glVertex3f(1.0f, -1.0f, -1.0f);
    //// Top Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 1.0f);
    //glVertex3f(1.0f, 1.0f, -1.0f);
    //// Top Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 1.0f);
    //glVertex3f(1.0f, 1.0f, 1.0f);
    //// Bottom Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 0.0f);
    //glVertex3f(1.0f, -1.0f, 1.0f);
    //glEnd();

    //glBindTexture(GL_TEXTURE_2D, texture[0].texID);
    //glBegin(GL_QUADS);
    //// Left Face
    //// Bottom Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 0.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //// Bottom Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 0.0f);
    //glVertex3f(-1.0f, -1.0f, 1.0f);
    //// Top Right Of The Texture and Quad
    //glTexCoord2f(1.0f, 1.0f);
    //glVertex3f(-1.0f, 1.0f, 1.0f);
    //// Top Left Of The Texture and Quad
    //glTexCoord2f(0.0f, 1.0f);
    //glVertex3f(-1.0f, 1.0f, -1.0f);
    //glEnd();

    // Draw the Pyramid
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    // Bottom section - two triangles
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(vCorners[2]);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(vCorners[4]);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(vCorners[1]);


    glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(vCorners[2]);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(vCorners[3]);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(vCorners[4]);

    // Front Face
    m3dFindNormal(vNormal, vCorners[0], vCorners[4], vCorners[3]);
    glNormal3fv(vNormal);
    glTexCoord2f(0.5f, 1.0f);
    glVertex3fv(vCorners[0]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(vCorners[4]);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(vCorners[3]);

    // Left Face
    m3dFindNormal(vNormal, vCorners[0], vCorners[1], vCorners[4]);
    glNormal3fv(vNormal);
    glTexCoord2f(0.5f, 1.0f);
    glVertex3fv(vCorners[0]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(vCorners[1]);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(vCorners[4]);

    // Back Face
    m3dFindNormal(vNormal, vCorners[0], vCorners[2], vCorners[1]);
    glNormal3fv(vNormal);
    glTexCoord2f(0.5f, 1.0f);
    glVertex3fv(vCorners[0]);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(vCorners[2]);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(vCorners[1]);

    // Right Face
    m3dFindNormal(vNormal, vCorners[0], vCorners[3], vCorners[2]);
    glNormal3fv(vNormal);
    glTexCoord2f(0.5f, 1.0f);
    glVertex3fv(vCorners[0]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(vCorners[3]);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(vCorners[2]);
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
    gluPerspective(35.0f, (GLfloat)w / (GLfloat)h, 1, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
        xRot += 1.0f;
        break;
    case 'y':
        yRot += 1.0f;
        break;
    case 'z':
        zRot += 1.0f;
        break;
    default:
        break;
    }

    // Refresh the Window
    glutPostRedisplay();
}
// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

    // Refresh the Window
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Texture Map");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMainLoop();
    return 0;
}
