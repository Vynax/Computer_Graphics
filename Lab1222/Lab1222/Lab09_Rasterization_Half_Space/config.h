#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <algorithm>    // std::swap std::sort
#include <cmath>        // abs
#include "function.h"
#include <vector>
#include <cstdlib> // for abs
#include "coordinate.h"
#include <iostream>
#include "line.h"
//#include "objloader.h"

float getSin(float);
float getCos(float);
void int_swap(int *a, int*b);
bool compare_angle(Coordinate a, Coordinate b);


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

        int x, y;
        glColor3f(1.0f, 1.0f, 1.0f); // White (RGB)
        for (unsigned int i = 0; i < coor_vec.size(); i++) {

            x = coor_vec[i].x;
            y = coor_vec[i].y;
            //x = (int)((click_vec[i].x - gridWidth / 2) / gridWidth);
            //y = (int)((click_vec[i].y - gridHeight / 2) / gridHeight);

            glPolygonMode(GL_FRONT, GL_FILL);
            glBegin(GL_POLYGON);

            //if (click_vec[i].x > gridWidth / 2)
            //  x = x + 1;
            //if (click_vec[i].y > gridHeight / 2)
            //  y = y + 1;

            glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);

            glEnd();
            //std::cout << "grid x:" << x << " grid y:" << y << std::endl;
        }

        if (click_vec.size() >= 2) {
            Draw_Line_Target_Cube();
        }


        glColor3f(1.0f, 0.0f, 0.0f); // Red (RGB)
        for (unsigned int i = 0; i < click_coor_vec.size(); i++) {
            x = click_coor_vec[i].x;
            y = click_coor_vec[i].y;
            //x = (int)((click_vec[i].x - gridWidth / 2) / gridWidth);
            //y = (int)((click_vec[i].y - gridHeight / 2) / gridHeight);

            glPolygonMode(GL_FRONT, GL_FILL);
            glBegin(GL_POLYGON);

            //if (click_vec[i].x > gridWidth / 2)
            //  x = x + 1;
            //if (click_vec[i].y > gridHeight / 2)
            //  y = y + 1;

            glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);

            glEnd();
        }

    }

    void Draw_Line_Target_Cube() {
        int x1, y1, x2, y2;
        int size;
        size = click_vec.size();

        glColor3f(1.0f, 0.5f, 0.0f);//Orange
        //glColor3f(0.2f, 0.3f, 0.5f);  //Some type of blue

        //改成畫三條線
        for (int i = 0; i < size; i++) {


            x1 = coor_vec[i].x;
            y1 = coor_vec[i].y;

            x2 = coor_vec[(i + 1) % size].x;
            y2 = coor_vec[(i + 1) % size].y;
            glBegin(GL_LINES);
            glVertex3f(x1 * gridWidth, y1 * gridHeight, 0);
            glVertex3f(x2 * gridWidth, y2 * gridHeight, 0);
            glEnd();
        }
    }

    void Add_New_Click(int x, int y) {
        //重置三角形
        if (which_to_pop != -1 && click_vec.size() == 3) {
            click_vec.clear();
            coor_vec.clear();
        }
        Coordinate temp(x, y);
        click_vec.push_back(temp);
        if (which_to_pop == -1)
            which_to_pop = 0;

        coor_vec.clear();
        // 借用 x 跟 y
        // 轉換座標
        for (unsigned int i = 0; i < click_vec.size(); i++) {

            x = (int)((click_vec[i].x - gridWidth / 2) / gridWidth);
            y = (int)((click_vec[i].y - gridHeight / 2) / gridHeight);

            if (click_vec[i].x > gridWidth / 2)
                x = x + 1;
            if (click_vec[i].y > gridHeight / 2)
                y = y + 1;

            Coordinate temp2(x, y);
            coor_vec.push_back(temp2);
        }

        click_coor_vec = coor_vec;

        if (coor_vec.size() == 3)
            fillTriangle();
        //setLine(coor_vec[0].x, coor_vec[0].y, coor_vec[1].x, coor_vec[1].y, false);
    }
    // (x2 - x1) (y - y1) = (y2 - y1) (x - x1)
    void fillTriangle() {
        //int e1 = lineEq();
        int centerx = 0, centery = 0, xMin, xMax, yMin, yMax;

        xMin = coor_vec[0].x; //給他們第一個點的數值
        xMax = coor_vec[0].x;
        yMin = coor_vec[0].y;
        yMax = coor_vec[0].y;
        for (unsigned int i = 0; i < coor_vec.size(); i++) {
            if (xMin > coor_vec[i].x)   //找最大最小值
                xMin = coor_vec[i].x;
            if (xMax < coor_vec[i].x)
                xMax = coor_vec[i].x;
            if (yMin > coor_vec[i].y)
                yMin = coor_vec[i].y;
            if (yMax < coor_vec[i].y)
                yMax = coor_vec[i].y;

            centerx = centerx + coor_vec[i].x;  //計算三角形的中心點
            centery = centery + coor_vec[i].y;
        }
        centerx = centerx / 3;
        centery = centery / 3;
        Coordinate center(centerx, centery);
        //std::cout << 
        for (unsigned int i = 0; i < coor_vec.size(); i++) {
            coor_vec[i].angle = GetAngle(center, coor_vec[i]);
            std::cout << "角度:" << coor_vec[i].angle << std::endl;
        }
        std::sort(coor_vec.begin(), coor_vec.begin() + 3, compare_angle); //逆時針排序，用角度排
        for (unsigned int i = 0; i < coor_vec.size(); i++) {
            std::cout << "排序後角度:" << coor_vec[i].angle << std::endl;
        }

        Line L1, L2, L3;

        int e1 = lineEq(&L1, coor_vec[0], coor_vec[1], xMin, yMin);
        int e2 = lineEq(&L2, coor_vec[1], coor_vec[2], xMin, yMin);
        int e3 = lineEq(&L3, coor_vec[2], coor_vec[0], xMin, yMin);
        int xDim = xMax - xMin + 1;
        std::cout << "xDim: " << xDim << std::endl;
        std::cout << "L1 = " << L1.a << "x + " << L1.b << "y + " << L1.c << " e1: " << e1 << std::endl;
        std::cout << "L2 = " << L2.a << "x + " << L2.b << "y + " << L2.c << " e2: " << e2 << std::endl;
        std::cout << "L3 = " << L3.a << "x + " << L3.b << "y + " << L3.c << " e3: " << e3 << std::endl;
        std::cout << "xMin : " << xMin << " xMax : " << xMax << " yMin : " << yMin << " yMax : " << yMax << std::endl;
        for (int y = yMin; y <= yMax; y++) {
            for (int x = xMin; x <= xMax; x++) {
                if (e1 < 0 && e2 < 0 && e3 < 0) {
                    Add_Coor_to_Vec(&coor_vec, x, y);
                    //std::cout << "Add ( " << x << ", " << y << " ) into vector" << " e1: " << e1 << " e2: " << e2 << " e3: " << e3 << std::endl;

                }
                e1 += L1.a;
                e2 += L2.a;
                e3 += L3.a;
            }
            e1 = e1 - xDim * L1.a + L1.b;
            e2 = e2 - xDim * L2.a + L2.b;
            e3 = e3 - xDim * L3.a + L3.b;
        }
    }

    float GetAngle(Coordinate a, Coordinate b)
    {
        // 這邊需要過濾掉位置相同的問題
        if (a.x == b.x && a.y >= b.y) return 0;

        b.x -= a.x;
        b.y -= a.y;
        Coordinate c(0, -1);

        int d1 = (c.x * b.x) + (c.y * b.y);
        float d2 = c.magnitude() * b.magnitude();
        float angle = acos(d1 / d2) * (180 / M_PI);

        if (b.x < 0) angle *= -1;

        if (angle < 0)
            angle = angle + 360;
        return angle;
    }

    int lineEq(Line *l, Coordinate dot_1, Coordinate dot_2, int x, int y) {
        int a = dot_2.y - dot_1.y;
        int b = -(dot_2.x - dot_1.x);
        int c = -dot_1.x *(dot_2.y - dot_1.y) + dot_1.y*(dot_2.x - dot_1.x);
        l->a = a;
        l->b = b;
        l->c = c;
        return a * x + b * y + c;
    }

    void Add_Coor_to_Vec(std::vector<Coordinate> *vec, int x, int y) {
        Coordinate temp(x, y);
        vec->push_back(temp);
    }

    //float midX, midY, midZ;

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
    std::vector<Coordinate> click_coor_vec; //儲存轉換後的點擊座標
    int which_to_pop = -1;
};
