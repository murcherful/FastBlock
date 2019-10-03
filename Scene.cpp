#include "Scene.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

Scene::Scene(int tx, int ty, int tw, int th){
    srand(time(0));
    x = tx;
    y = ty;
    w = tw;
    h = th;
    isStop = 1;
    isGameOver = 0;
    score = 0;
    clearRect(x, y, w, h);
    drawWholeRect(x, y, w, h, WHITE);
    floors = new Floor(x+1, y+h-1-FLOORH, w-2, FLOORH, FLOORS);
    player = new Player(x+PLAYERX, y+th-1-FLOORH-1, floors);
    draw();
}

Scene::~Scene(){
    clearRect(x, y, w, h);
}

bool Scene::update(){
    if(isStop || isGameOver){
        return 0;
    }
    player->update();
    if(player->getIsDead()){
        isGameOver = 1;
        return 1;
    }
    else{
        floors->update();
        score++;
        return 0;
    }
}

void Scene::draw(){
    drawRect(x, y, w, h, BULE);
    drawWholeRect(x+1, y+1, w-2, h-2-FLOORH, WHITE);
    floors->draw();
    if(player->getY() > y){
        player->draw();
    }
    drawInfo();
}

void Scene::stop(){
    isStop = 1;
}

void Scene::start(){
    isStop = 0;
}

bool Scene::getIsStop(){
    return isStop;
}

void Scene::playerJump(){
    if(isStop || isGameOver){
        return;
    }
    player->jump();
}

void Scene::drawInfo(){
    drawText(x+1, y+1, "STATE:", BLACK, WHITE);
    if(isStop){
        drawText(x+4, y+1, "PAUSE", YELLOW, WHITE);
    }
    else if(isGameOver){
        drawText(x+4, y+1, "GAME OVER", RED, WHITE);
    }
    else{
        drawText(x+4, y+1, "RUN", GREEN, WHITE);
    }
    drawText(x+1, y+3, "SCORE:", BLACK, WHITE);
    stringstream scoreSS;
    scoreSS << score;
    drawText(x+4, y+3, scoreSS.str(), RED, WHITE);
    
}

bool Scene::getIsGameOver(){
    return isGameOver;
}
