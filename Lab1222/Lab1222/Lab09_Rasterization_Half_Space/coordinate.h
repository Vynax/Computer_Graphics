#pragma once

class Coordinate {
public:
    Coordinate(int x, int y) :x(x), y(y) {}
    float magnitude() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
    int x;
    int y;
    float angle;
};
