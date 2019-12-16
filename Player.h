#pragma once
#include "Floor.h"
#include "ScreenDraw.h"
#include <vector>

#define PLAYERX 5
#define PLAYERV -2
#define PLAYERA 0.2
#define FLOAT_TIME 60
#define FLOATH 10

using namespace std;

class Player
{
public:
    Player(int tx, int ty);
    ~Player();
    /* void update(); */
    void update2();
    void draw();
    void jump();
    void left();
    void right();
    void floatStart();

    int x;
    int y;
    double rx;
    double ry;
    double v;
    double a;
    int jumpTime;
    bool isFloat;

private:
    int floatTime; 
};

