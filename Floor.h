#pragma once
#include <vector>

using namespace std;

#define NORMAL_FLOOR 0
#define BREAK_FLOOR 1
#define DEATH_FLOOR 2
#define SCORE_FLOOR 3
#define FLOAT_FLOOR 4

#define DEATH_FLOOR_H1 2
#define DEATH_FLOOR_H2 4

typedef struct Info{
    int height;
    int type;
}Info;

class Floor
{
public:
    Floor(int tx, int ty, int tw, int th, int tv);
    ~Floor();
    
    vector<Info> infos;

    void update();
    void draw();
    int x;
    int y;
    int w;
    int h;
    int v;


private:
    int count;
    void addRandomFloor();
    void initFloor();
};

