#include "Floor.h"
#include "ScreenDraw.h"
#include <ctime>
#include <cstdlib>

Floor::Floor(int tx, int ty, int tw, int th, int tv){
    x = tx;
    y = ty;
    w = tw;
    h = th;
    v = tv;
    srand(time(0));
    initFloor();
    draw();
}

Floor::~Floor(){

}

void Floor::update(){
    if(count < v){
        count++;
    }
    else{
        count = 0;
        infos.erase(infos.begin());
        addRandomFloor();
    }
}

void Floor::draw(){
    drawWholeRect(x, y, w, h, BLACK);
    for(int i = 0; i < infos.size(); ++i){
        switch(infos[i].type){
        case NORMAL_FLOOR:
            break;
        case BREAK_FLOOR:
            drawLine(x+i, y, infos[i].height, 0, WHITE);
            break;
        case DEATH_FLOOR:
            drawLine(x+i, y-(infos[i].height-h), infos[i].height-h, 0, RED);
            break;
        case SCORE_FLOOR:
            drawLine(x+i, y, infos[i].height, 0, YELLOW);
            break;
        case FLOAT_FLOOR:
            drawLine(x+i, y, infos[i].height, 0, PURPLE);
            break;
        }
    }
}

void Floor::addRandomFloor(){
    int type = rand()%70;
    Info newInfo;
    if(type == 0 || type == 5){
        newInfo.height = h;
        newInfo.type = BREAK_FLOOR;
    }
    else if(type == 1 || type == 6){
        newInfo.height = h+DEATH_FLOOR_H1;
        newInfo.type = DEATH_FLOOR;
    }
    else if(type == 2 || type == 7){
        newInfo.height = h+DEATH_FLOOR_H2;
        newInfo.type = DEATH_FLOOR;
    }
    else if(type == 3){
        newInfo.height = h;
        newInfo.type = SCORE_FLOOR;
    }
    else if(type == 4){
        newInfo.height = h;
        newInfo.type = FLOAT_FLOOR;
    }
    else{
        newInfo.height = h;
        newInfo.type = NORMAL_FLOOR;
    }
    infos.push_back(newInfo);
}

void Floor::initFloor(){
    for(int i = 0; i < w/4; ++i){
        Info newInfo;
        newInfo.height = h;
        newInfo.type = NORMAL_FLOOR;
        infos.push_back(newInfo);
    }
    for(int i = w/4; i < w; ++i){
        addRandomFloor();
    }
}

