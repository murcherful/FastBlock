#pragma once
#include "Floor.h"
#include "ScreenDraw.h"
#include <vector>

#define PLAYERX 5
#define PLAYERV -2
#define PLAYERA 0.2


using namespace std;

class Player
{
public:
    Player(int tx, int ty, Floor* tfloors);
    ~Player();
    void update();
    void draw();
    void jump();
    bool getIsDead();
    int getY();

private:
    int x;
    int y;
    double rx;
    double ry;
    double v;
    double a;
    int jumpTime;
    Floor* floors;
    bool isDead;
};

