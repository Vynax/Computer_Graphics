#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <algorithm>    // std::swap
#include <cmath>		// abs
//#include "objloader.h"

class Config {
public:
	Config() {
		gridWidth = 20.0;
		gridHeight = 20.0;
		orthoX = orthoY = orthoZ = 300;
		//Set_Grid_Amount(9);
		clickX = clickY = clickZ = 0;
	}
	/*~Config() {
		delete[] translateMatrix;
		delete[] rotMatrix_X;
		delete[] rotMatrix_Y;
		delete[] rotMatrix_Z;
	}*/

	void Set_Ortho_Width_Height(GLfloat X, GLfloat Y, GLfloat Z) {
		orthoX = X;
		orthoY = Y;
		orthoZ = Z;
	}

	void Set_Grid_Amount(int amount) {
		// 左右上下是兩倍ortho
		grid_Amount = amount;
		gridWidth = 2 * orthoX / grid_Amount;
		gridHeight = 2 * orthoY / grid_Amount;
	}

	void Draw() {
		Draw_Grid();
		Draw_Target_Cube();
	}

	void Draw_Grid() {
		glColor3f(1.0f, 1.0f, 1.0f); // White (RGB)

		for (float x = -orthoX; x <= orthoX; x += gridWidth)
		{
			glBegin(GL_LINES);
			glVertex3f(x, -orthoY, 0.0f);
			glVertex3f(x, orthoY, 0.0f);
			glEnd();
		}
		for (float y = -orthoY; y <= orthoY; y += gridHeight)
		{
			glBegin(GL_LINES);
			glVertex3f(-orthoX, y, 0.0f);
			glVertex3f(orthoX, y, 0.0f);
			glEnd();
		}
	}

	void Draw_Target_Cube() {
		glColor3f(1.0f, 1.0f, 1.0f); // White (RGB)
		int x = ((clickX - gridWidth / 2) / gridWidth);
		int y = ((clickY - gridHeight / 2) / gridHeight);

		glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);

		if (clickX > gridWidth / 2)
			x = x + 1;
		if (clickY > gridHeight / 2)
			y = y + 1;

		glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
		glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
		glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);
		glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);

		glEnd();
		std::cout << "grid x:" << x << " grid y:" << y << std::endl;
	}

	float midX, midY, midZ;

	float lengthX, lengthY, lengthZ;
	GLfloat orthoX;
	GLfloat orthoY;
	GLfloat orthoZ;

	float clickX, clickY, clickZ;

	int grid_Amount;
private:
	GLfloat gridWidth;
	GLfloat gridHeight;
	//int render_Mode;
	//int obj_draw;
	//std::vector <ObjLoader> obj;
};
