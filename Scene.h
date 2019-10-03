#pragma once
#include "ScreenDraw.h"
#include "Floor.h"
#include "Player.h"
#include <vector>
#include <iostream>
#define FLOORH 2
#define FLOORS 3


using namespace std;

class Scene
{
public:
    Scene(int tx, int ty, int tw, int th);
    ~Scene();
    bool update();
    void draw();
    void stop();
    void start();
    bool getIsStop();
    bool getIsGameOver();
    void playerJump();
private:
    int x;
    int y;
    int w;
    int h;
    bool isStop;
    bool isGameOver;
    Player* player;
    Floor* floors;
    int score;
    void drawInfo();
};

