#pragma once
#include "ScreenDraw.h"
#include "Floor.h"
#include "Player.h"
#include <vector>
#include <iostream>
#define FLOORH 4
#define FLOORS 2
#define PLAYERL 1
#define PLAYERR 29


using namespace std;

class Scene
{
public:
    Scene(int tx, int ty, int tw, int th);
    ~Scene();
    bool update();
    /* bool update2(); */
    void draw();
    void stop();
    void start();
    bool getIsStop();
    bool getIsGameOver();
    void playerJump();
    void playerLeft();
    void playerRight();
    int getScore();
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

