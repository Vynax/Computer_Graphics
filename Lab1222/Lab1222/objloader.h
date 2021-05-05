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
	ObjLoader(std::string filename);//Ū�����
	ObjLoader() {}
	void Draw();//ø�s���

	float minX, maxX, minY, maxY, minZ, maxZ;
	float midX, midY, midZ;

	float lengthX, lengthY, lengthZ;
private:
	std::vector<std::vector<GLfloat>> v;//�s���I(x,y,z)�y��
	std::vector<std::vector<GLint>> f;//�s�񭱪��T�ӳ��I����
};