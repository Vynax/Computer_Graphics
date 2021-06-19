#pragma once

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <algorithm>    // std::swap
#include <cmath>        // abs
#include "function.h"
#include <vector>
#include <cstdlib> // for abs
//#include "objloader.h"

float getSin(float);
float getCos(float);
void int_swap(int *a, int*b);

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
            //  x = x + 1;
            //if (click_vec[i].Y > gridHeight / 2)
            //  y = y + 1;

            glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth + gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);
            glVertex3f(x*gridWidth - gridWidth / 2, y*gridHeight + gridHeight - gridHeight / 2, 0.0f);

            glEnd();
            std::cout << "grid x:" << x << " grid y:" << y << std::endl;
        }

        if (click_vec.size() >= 2) {
            Draw_Line_Target_Cube();
        }
    }

    void Draw_Line_Target_Cube() {
        int x1, y1, x2, y2, size;

        size = click_vec.size();

        glColor3f(1.0f, 0.5f, 0.0f);//Orange
        //glColor3f(0.2f, 0.3f, 0.5f);  //Some type of blue

        //改成畫三條線
        for (unsigned int i = 0; i < size; i++) {


            x1 = coor_vec[i].X;
            y1 = coor_vec[i].Y;

            x2 = coor_vec[(i + 1) % size].X;
            y2 = coor_vec[(i + 1) % size].Y;
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

            x = (int)((click_vec[i].X - gridWidth / 2) / gridWidth);
            y = (int)((click_vec[i].Y - gridHeight / 2) / gridHeight);

            if (click_vec[i].X > gridWidth / 2)
                x = x + 1;
            if (click_vec[i].Y > gridHeight / 2)
                y = y + 1;

            Coordinate temp2(x, y);
            coor_vec.push_back(temp2);
        }
        //if (coor_vec.size() == 2)
            //setLine(coor_vec[0].X, coor_vec[0].Y, coor_vec[1].X, coor_vec[1].Y, false);
    }

    void setLine(int x0, int y0, int x1, int y1, bool ever_switch) {
        if (x0 > x1)
        {
            setLine(x1, y1, x0, y0, ever_switch);
            return;
        }

        // 看維基百科改來的--------------
        bool steep;
        if (x1 != x0) {

            steep = abs(y1 - y0) > abs(x1 - x0);
            if (steep) {
                std::cout << "Before x0: " << x0 << " y0: " << y0;
                std::cout << " x1: " << x1 << " y1: " << y1 << std::endl;
                int_swap(&x0, &y0);
                int_swap(&x1, &y1);
                std::cout << "After x0: " << x0 << " y0: " << y0;
                std::cout << " x1: " << x1 << " y1: " << y1 << std::endl;
                if (x0 > x1)
                {
                    setLine(x1, y1, x0, y0, true);
                    return;
                }
            }
        }
        int ystep;

        // ----------------------------


        int dx = x1 - x0;
        int dy = y1 - y0;
        float m = (float)dy / (float)dx;
        int d = 2 * dy - dx;
        int delE = 2 * dy;
        int delNE = 2 * (dy - dx);
        // 看維基百科改來的--------------
        if (y0 < y1)
            ystep = 1;

        else {
            ystep = -1;
            d = 2 * -dy - dx;
            delE = 2 * -dy;
            delNE = 2 * (-dy - dx);
        }
        // ----------------------------
        int x = x0;
        int y = y0;
        std::cout << "m: " << m << std::endl;
        // 水平線
        if (m == 0) {
            while (x < x1) {
                x = x + 1;
                Add_Coor_to_Vec(&coor_vec, x, y);
            }
        }
        //垂直線
        else if (x0 == x1 && y0 != y1) {
            if (y0 < y1)
                while (y < y1) {
                    y = y + 1;
                    Add_Coor_to_Vec(&coor_vec, x, y);
                }
            else if (y0 > y1)
                while (y > y1) {
                    y = y - 1;
                    Add_Coor_to_Vec(&coor_vec, x, y);
                }
        }
        // 45度的斜直線
        else if (m == 1) {
            while (x < x1) {
                x = x + 1;
                y = y + 1;
                Add_Coor_to_Vec(&coor_vec, x, y);
            }
        }
        // -45度的斜直線
        else if (m == -1) {
            while (x < x1) {
                x = x + 1;
                y = y - 1;
                Add_Coor_to_Vec(&coor_vec, x, y);
            }
        }
        else {
            while (x < x1) {
                if (d <= 0) {
                    d += delE;
                    x = x + 1;
                }
                else {
                    d += delNE;
                    x = x + 1;
                    y = y + ystep;
                }
                if (y0 != y1 && steep) {
                    Add_Coor_to_Vec(&coor_vec, y, x);
                    std::cout << "add new coor: x:" << y << " y: " << x << std::endl;
                }
                else {
                    if (ever_switch)
                        Add_Coor_to_Vec(&coor_vec, y, x);
                    else
                        Add_Coor_to_Vec(&coor_vec, x, y);
                }
            }
        }
    }

    void Add_Coor_to_Vec(std::vector<Coordinate> *vec, int x, int y) {
        Coordinate temp(x, y);
        vec->push_back(temp);
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
