// Pyramid.cpp
// Demonstrates Simple Texture Mapping
// OpenGL SuperBible
// Richard S. Wright Jr.

#include <Windows.h>
#include <GL/glut.h>
#include "shared/math3d.h"    // 3D Math Library
#include <stdlib.h>
#include <stdio.h>

#define GL_CLAMP_TO_EDGE                                   0x812F

typedef struct
{
    GLbyte  identsize;              // Size of ID field that follows header (0)
    GLbyte  colorMapType;           // 0 = None, 1 = paletted
    GLbyte  imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
    unsigned short  colorMapStart;          // First colour map entry
    unsigned short  colorMapLength;         // Number of colors
    unsigned char   colorMapBits;   // bits per palette entry
    unsigned short  xstart;                 // image x origin
    unsigned short  ystart;                 // image y origin
    unsigned short  width;                  // width in pixels
    unsigned short  height;                 // height in pixels
    GLbyte  bits;                   // bits per pixel (8 16, 24, 32)
    GLbyte  descriptor;             // image descriptor
} TGAHEADER;


////////////////////////////////////////////////////////////////////
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
    FILE *pFile;            // File pointer
    TGAHEADER tgaHeader;        // TGA file header
    unsigned long lImageSize;       // Size in bytes of image
    short sDepth;           // Pixel depth;
    GLbyte  *pBits = NULL;          // Pointer to bits

    // Default/Failed values
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_BGR_EXT;
    *iComponents = GL_RGB8;

    // Attempt to open the fil
    pFile = fopen(szFileName, "r");
    if (pFile == NULL)
        return NULL;

    // Read in header (binary)
    fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

    // Do byte swap for big vs little endian
#ifdef __APPLE__
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
    LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
    LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
    LITTLE_ENDIAN_WORD(&tgaHeader.width);
    LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif


    // Get width, height, and depth of texture
    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;

    // Put some validity checks here. Very simply, I only understand
    // or care about 8, 24, or 32 bit targa's.
    if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
        return NULL;

    // Calculate size of image buffer
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

    // Allocate memory and check for success
    pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if (pBits == NULL)
        return NULL;

    // Read in the bits
    // Check for read error. This should catch RLE or other 
    // weird formats that I don't want to recognize
    if (fread(pBits, lImageSize, 1, pFile) != 1)
    {
        free(pBits);
        return NULL;
    }

    // Set OpenGL format expected
    switch (sDepth)
    {
    case 3:     // Most likely case
        *eFormat = GL_BGR_EXT;
        *iComponents = GL_RGB8;
        break;
    case 4:
        *eFormat = GL_BGRA_EXT;
        *iComponents = GL_RGBA8;
        break;
    case 1:
        *eFormat = GL_LUMINANCE;
        *iComponents = GL_LUMINANCE8;
        break;
    };


    // Done with File
    fclose(pFile);

    // Return pointer to image data
    return pBits;
}
// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero
    if (h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(35.0f, fAspect, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;

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

    // Black blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Load texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    pBytes = gltLoadTGA("stone2.tga", &iWidth, &iHeight, &iComponents, &eFormat);
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
    free(pBytes);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);
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


// Called to draw scene
void RenderScene(void)
{
    M3DVector3f vNormal;
    M3DVector3f vCorners[5] = { { 0.0f, .80f, 0.0f },     // Top           0
                              { -0.5f, 0.0f, -.50f },    // Back left     1
                              { 0.5f, 0.0f, -0.50f },    // Back right    2
                              { 0.5f, 0.0f, 0.5f },      // Front right   3
                              { -0.5f, 0.0f, 0.5f } };    // Front left    4

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glPushMatrix();
    // Move object back and do in place rotation
    glTranslatef(0.0f, -0.25f, -4.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

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


    // Restore the matrix state
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Textured Pyramid");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
