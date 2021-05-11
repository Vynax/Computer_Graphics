#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <algorithm>    // std::swap
#include <cmath>		// abs
#include "objloader.h"

float getSin(float);
float getCos(float);

class Config {
public:
	Config() {

		translateMatrix = new GLfloat[16]{
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};

		rotMatrix_X = new GLfloat[16]{
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};

		rotMatrix_Y = new GLfloat[16]{
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};

		rotMatrix_Z = new GLfloat[16]{
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};

		obj.push_back(ObjLoader("gourd.obj"));
		obj.push_back(ObjLoader("lamp.obj"));
		obj.push_back(ObjLoader("octahedron.obj"));
		obj.push_back(ObjLoader("teapot.obj"));

		setObj_Draw(4);
		Set_Render_Mode(2);
	}
	/*~Config() {
		delete[] translateMatrix;
		delete[] rotMatrix_X;
		delete[] rotMatrix_Y;
		delete[] rotMatrix_Z;
	}*/
	// 以下是為了Lab05任意軸旋轉寫的-----------------------------------------
	GLfloat *getTranslateMatrix(float tx, float ty, float tz) {
		translateMatrix[12] = tx;
		translateMatrix[13] = ty;
		translateMatrix[14] = tz;
		return translateMatrix;
	}

	//任意軸旋轉時只要拿到cos跟sin即可
	GLfloat *getRotateX(float Sin, float Cos) {
		rotMatrix_X[5] = Cos;
		rotMatrix_X[6] = Sin;
		rotMatrix_X[9] = -Sin;
		rotMatrix_X[10] = Cos;
		return rotMatrix_X;
	}

	GLfloat *getRotateY(float Sin, float Cos) {
		rotMatrix_Y[0] = Cos;
		rotMatrix_Y[2] = -Sin;
		rotMatrix_Y[8] = Sin;
		rotMatrix_Y[10] = Cos;

		return rotMatrix_Y;
	}

	//轉置矩陣
	GLfloat *getTransPose(GLfloat *matrix) {
		GLfloat tran[16];

		for (int i = 0; i < 16; i++) {
			tran[i] = matrix[i];
		}

		std::swap(tran[1], tran[4]);
		std::swap(tran[2], tran[8]);
		std::swap(tran[3], tran[12]);
		std::swap(tran[6], tran[9]);
		std::swap(tran[7], tran[13]);
		std::swap(tran[11], tran[14]);

		return tran;
	}

	// 0 = translateMatrix; 1 = rotMatrix_X; 2 = rotMatrix_Y; 3 = rotMatrix_Z
	GLfloat *getMatrix(int which) {
		switch (which) {
		case 0:
			return translateMatrix;
			break;
		case 1:
			return rotMatrix_X;
			break;
		case 2:
			return rotMatrix_Y;
			break;
		case 3:
			return rotMatrix_Z;
			break;
		default:
			break;
		}
	}

	// 以下為Lab04以前的Rotate-----------------------------------------
	GLfloat *getRotateX(float thetaX) {
		rotMatrix_X[5] = getCos(thetaX);
		rotMatrix_X[6] = getSin(thetaX);
		rotMatrix_X[9] = -getSin(thetaX);
		rotMatrix_X[10] = getCos(thetaX);
		return rotMatrix_X;
	}

	GLfloat *getRotateY(float thetaY) {
		rotMatrix_Y[0] = getCos(thetaY);
		rotMatrix_Y[2] = -getSin(thetaY);
		rotMatrix_Y[8] = getSin(thetaY);
		rotMatrix_Y[10] = getCos(thetaY);

		return rotMatrix_Y;
	}

	GLfloat *getRotateZ(float thetaZ) {
		rotMatrix_Z[0] = getCos(thetaZ);
		rotMatrix_Z[1] = getSin(thetaZ);
		rotMatrix_Z[4] = -getSin(thetaZ);
		rotMatrix_Z[5] = getCos(thetaZ);

		return rotMatrix_Z;
	}
	// 以上為Lab04以前的Rotate-----------------------------------------

	void SetObjectXYZ(ObjLoader *ol) {

		midX = ol->midX;
		midY = ol->midY;
		midZ = ol->midZ;

		lengthX = ol->lengthX;
		lengthY = ol->lengthY;
		lengthZ = ol->lengthZ;

		std::cout << std::endl;
		std::cout << "config:" << std::endl;
		std::cout << "midX:" << midX << std::endl;
		std::cout << "midY:" << midY << std::endl;
		std::cout << "midZ:" << midZ << std::endl;

		std::cout << "lengthX:" << lengthX << std::endl;
		std::cout << "lengthY:" << lengthY << std::endl;
		std::cout << "lengthZ:" << lengthZ << std::endl;

		auto max_array = { lengthX,lengthY,lengthZ };
		float max = *std::max_element(max_array.begin(), max_array.end());

		std::cout << "max:" << max << std::endl;

		//glLoadIdentity();             // Reset
		glOrtho(-max, max, -max, max, -max, max + 15);
	}

	void Draw() {
		switch (render_Mode) {
		case 1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case 2:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 3:
			glPolygonMode(GL_FRONT, GL_FILL);
			break;
		}
		obj[obj_draw].Draw();
	}

	void setObj_Draw(int which) {
		obj_draw = which - 1;
		SetObjectXYZ(&obj[obj_draw]);
	}

	void Set_Render_Mode(int mode) {
		render_Mode = mode;
	}

	void Set_Bounding_Box(bool OnOrOff) {
		obj[obj_draw].draw_BoundingBox = OnOrOff;
	}

	void Set_Ortho_Width_Height(GLfloat X, GLfloat Y, GLfloat Z) {
		orthoX = X;
		orthoY = Y;
		orthoZ = Z;
	}

	float midX, midY, midZ;

	float lengthX, lengthY, lengthZ;
	GLfloat orthoX;
	GLfloat orthoY;
	GLfloat orthoZ;
private:
	GLfloat *translateMatrix;
	GLfloat *rotMatrix_X;
	GLfloat *rotMatrix_Y;
	GLfloat *rotMatrix_Z;

	int render_Mode;
	int obj_draw;
	std::vector <ObjLoader> obj;
};
