#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <algorithm>    // std::swap
#include <cmath>		// abs
//#include "objloader.h"

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

		gridWidth = 20.0;
		gridHeight = 20.0;
		clickX = clickY = clickZ = 0;
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
	GLfloat gridWidth;
	GLfloat gridHeight;

	float clickX, clickY, clickZ;
private:
	GLfloat *translateMatrix;
	GLfloat *rotMatrix_X;
	GLfloat *rotMatrix_Y;
	GLfloat *rotMatrix_Z;

	//int render_Mode;
	//int obj_draw;
	//std::vector <ObjLoader> obj;
};
