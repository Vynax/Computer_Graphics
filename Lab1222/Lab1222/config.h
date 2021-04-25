#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <algorithm>    // std::swap

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
	}
	/*~Config() {
		delete[] translateMatrix;
		delete[] rotMatrix_X;
		delete[] rotMatrix_Y;
		delete[] rotMatrix_Z;
	}*/

	GLfloat *getTranslateMatrix(float tx, float ty, float tz) {
		translateMatrix[12] = tx;
		translateMatrix[13] = ty;
		translateMatrix[14] = tz;
		return translateMatrix;
	}

	GLfloat *getRotateX(float Cos, float Sin) {
		rotMatrix_X[5] = Cos;
		rotMatrix_X[6] = Sin;
		rotMatrix_X[9] = -Sin;
		rotMatrix_X[10] = Cos;
		return rotMatrix_X;
	}

	void transPose(GLfloat *matrix) {
		std::swap(matrix[1], matrix[4]);
		std::swap(matrix[2], matrix[8]);
		std::swap(matrix[3], matrix[12]);
		std::swap(matrix[6], matrix[9]);
		std::swap(matrix[7], matrix[13]);
		std::swap(matrix[11], matrix[14]);
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
private:
	GLfloat *translateMatrix;
	GLfloat *rotMatrix_X;
	GLfloat *rotMatrix_Y;
	GLfloat *rotMatrix_Z;
};