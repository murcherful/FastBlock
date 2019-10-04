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
    player = new Player(x+PLAYERX, y+th-1-FLOORH-1);
    draw();
}

Scene::~Scene(){
    clearRect(x, y, w, h);
}

/* bool Scene::update(){ */
/*     if(isStop || isGameOver){ */
/*         return 0; */
/*     } */
/*     player->update(); */
/*     if(player->getIsDead()){ */
/*         isGameOver = 1; */
/*         return 1; */
/*     } */
/*     else{ */
/*         floors->update(); */
/*         score++; */
/*         return 0; */
/*     } */
/* } */

bool Scene::update(){
    if(isStop || isGameOver){
        return 0; 
    }
    player->update2();
    floors->update();
    int floorY = floors->y - (floors->infos[player->x - floors->x].height - floors->h);
    int floorType = floors->infos[player->x - floors->x].type;
    if(floorY <= player->y){
        player->jumpTime = 0;
        player->v = 0;
        player->a = 0;
        player->y = floorY - 1;
        player->ry = floorY - 1;
        if(floorType == BREAK_FLOOR || floorType == DEATH_FLOOR){
            isGameOver = 1;
            return 1;
        }
        /* else if(floorType == FLOAT_FLOOR){ */
        /*     player->floatStart(); */
        /* } */
        /* else if(floorType == SCORE_FLOOR){ */
        /*     score += 100; */
        /* } */
    }
    else{
        if(!player->isFloat && player->jumpTime == 0 && floorType == BREAK_FLOOR){
            isGameOver = 1;
            return 1;
        }
        else if(!player->isFloat && player->jumpTime == 0 && floorType == FLOAT_FLOOR){
            player->floatStart();
        }
        else if(!player->isFloat && player->jumpTime == 0 && floorType == SCORE_FLOOR){
            score += 100;
        }
    }
    score++;
    return 0;
}

void Scene::draw(){
    drawRect(x, y, w, h, BULE);
    drawWholeRect(x+1, y+1, w-2, h-2-FLOORH, WHITE);
    drawLineC(x+PLAYERR+1, y+1, h-2-FLOORH, '|', ' ', 0, GREEN, WHITE);
    floors->draw();
    if(player->y > y){
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
    if(isStop || isGameOver || player->isFloat){
        return;
    }
    player->jump();
}

void Scene::playerLeft(){
    if(isStop || isGameOver){
        return;
    }
    if(player->x > x + PLAYERL){
        player->left();
    }
}

void Scene::playerRight(){
    if(isStop || isGameOver){
        return;
    }
    if(player->x < x + PLAYERR){
        player->right();
    }
}

void Scene::drawInfo(){
    drawText(x+2, y+2, "STATE:", BLACK, WHITE);
    if(isStop){
        drawText(x+5, y+2, "PAUSE", YELLOW, WHITE);
    }
    else if(isGameOver){
        drawText(x+5, y+2, "GAME OVER", RED, WHITE);
    }
    else{
        drawText(x+5, y+2, "RUN", GREEN, WHITE);
    }
    drawText(x+2, y+4, "SCORE:", BLACK, WHITE);
    stringstream scoreSS;
    scoreSS << score;
    drawText(x+5, y+4, scoreSS.str(), RED, WHITE);
    
}

bool Scene::getIsGameOver(){
    return isGameOver;
}

int Scene::getScore(){
    return score;
}
