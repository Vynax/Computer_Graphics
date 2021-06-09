#pragma once
#include <vector>
#include <iostream>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

class ObjLoader
{
public:
	struct vertex
	{
		float x;
		float y;
		float z;
	};
	ObjLoader(std::string filename);//讀取函數
	ObjLoader() {}
	void Draw();//繪製函數

	float minX, maxX, minY, maxY, minZ, maxZ;
	float midX, midY, midZ;

	float lengthX, lengthY, lengthZ;
	bool draw_BoundingBox;
	bool random_Color;
private:
	std::vector<std::vector<GLfloat>> v;//存放頂點(x,y,z)座標
	std::vector<std::vector<GLint>> f;//存放面的三個頂點索引
};