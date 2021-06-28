#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <algorithm>    // std::swap
#include <cmath>        // abs
#include "objloader.h"

float getSin(float);
float getCos(float);

class Config {
public:
    Config() {

        //obj_vec.push_back(ObjLoader("Android_Droid_Robot.obj"));
        obj_vec.push_back(ObjLoader("gourd.obj"));
        obj_vec.push_back(ObjLoader("lamp.obj"));
        obj_vec.push_back(ObjLoader("octahedron.obj"));
        obj_vec.push_back(ObjLoader("teapot.obj"));

        setObj_Draw(3);
        //Set_Render_Mode(2);
    }
    /*~Config() {
        delete[] translateMatrix;
        delete[] rotMatrix_X;
        delete[] rotMatrix_Y;
        delete[] rotMatrix_Z;
    }*/


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
        //obj_vec[obj_draw].Draw();
    }

    void setObj_Draw(int which) {
        obj_draw = which - 1;
        SetObjectXYZ(&obj_vec[obj_draw]);
    }

    void Set_Render_Mode(int mode) {
        render_Mode = mode;
    }

    void Set_Bounding_Box(bool OnOrOff) {
        obj_vec[obj_draw].draw_BoundingBox = OnOrOff;
    }

    void Set_Random_Color(bool b) {
        obj_vec[obj_draw].random_Color = b;
    }

    float midX, midY, midZ;

    float lengthX, lengthY, lengthZ;
private:

    int render_Mode;
    int obj_draw;
    std::vector <ObjLoader> obj_vec;
};
