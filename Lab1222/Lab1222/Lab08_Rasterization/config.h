#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <algorithm>    // std::swap
#include <cmath>		// abs
#include "function.h"
#include <vector>
//#include "objloader.h"

float getSin(float);
float getCos(float);

class Coordinate {
public:
	Coordinate(int x, int y) :X(x), Y(y) {}
	int X;
	int Y;
};

class Config {
public:
	Config() {
		gridWidth = 20.0;
		gridHeight = 20.0;
		orthoX = orthoY = orthoZ = 300;
		//Set_Grid_Amount(9);
		clickX = clickY = clickZ = 0;
		//which_to_pop = -1;
	}

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

	// 畫格線
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
		if (click_vec.size() == 2) {
			Draw_Line_Target_Cube();
		}
		int x, y;

		glColor3f(1.0f, 1.0f, 1.0f); // White (RGB)
		for (unsigned int i = 0; i < coor_vec.size(); i++) {

			x = coor_vec[i].X;
			y = coor_vec[i].Y;
			//x = (int)((click_vec[i].X - gridWidth / 2) / gridWidth);
			//y = (int)((click_vec[i].Y - gridHeight / 2) / gridHeight);

			glPolygonMode(GL_FRONT, GL_FILL);
			glBegin(GL_POLYGON);

			//if (click_vec[i].X > gridWidth / 2)
			//	x = x + 1;
			//if (click_vec[i].Y > gridHeight / 2)
			//	y = y + 1;

			glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
			glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
			glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);
			glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);

			glEnd();
			std::cout << "grid x:" << x << " grid y:" << y << std::endl;
		}
	}

	void Draw_Line_Target_Cube() {
		int x1, y1, x2, y2;
		x1 = coor_vec[0].X;
		y1 = coor_vec[0].Y;

		x2 = coor_vec[1].X;
		y2 = coor_vec[1].Y;

		glColor3f(1.0f, 0.5f, 0.0f);//Orange
		//glColor3f(0.2f, 0.3f, 0.5f);  //Some type of blue
		glBegin(GL_LINES);
		glVertex3f(x1 * gridWidth, y1 * gridHeight, 0);
		glVertex3f(x2 * gridWidth, y2 * gridHeight, 0);
		glEnd();
	}

	void Add_New_Click(int x, int y) {

		if (which_to_pop != -1 && click_vec.size() == 2)
			click_vec.erase(click_vec.begin());
		Coordinate temp(x, y);
		click_vec.push_back(temp);
		if (which_to_pop == -1)
			which_to_pop = 0;

		coor_vec.clear();
		// 借用 x 跟 y
		for (unsigned int i = 0; i < click_vec.size(); i++) {

			x = (int)((click_vec[i].X - gridWidth / 2) / gridWidth);
			y = (int)((click_vec[i].Y - gridHeight / 2) / gridHeight);

			if (click_vec[i].X > gridWidth / 2)
				x = x + 1;
			if (click_vec[i].Y > gridHeight / 2)
				y = y + 1;

			Coordinate temp2(x, y);
			coor_vec.push_back(temp2);
		}
	}

	float midX, midY, midZ;

	float lengthX, lengthY, lengthZ;
	GLfloat orthoX;
	GLfloat orthoY;
	GLfloat orthoZ;

	float clickX, clickY, clickZ;


	int grid_Amount;
private:
	GLfloat *translateMatrix;
	GLfloat *rotMatrix_X;
	GLfloat *rotMatrix_Y;
	GLfloat *rotMatrix_Z;

	GLfloat gridWidth;
	GLfloat gridHeight;

	std::vector<Coordinate> click_vec;
	std::vector<Coordinate> coor_vec; // 轉換後的座標
	int which_to_pop = -1;
};
