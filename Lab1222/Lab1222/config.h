#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h

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

	GLfloat *translateMatrix;
	GLfloat *rotMatrix_X;
	GLfloat *rotMatrix_Y;
	GLfloat *rotMatrix_Z;
};