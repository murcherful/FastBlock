#include "Player.h"
#include <sstream>
#include <algorithm>

Player::Player(int tx, int ty){
    x = tx;
    y = ty;
    rx = tx;
    ry = ty;
    v = 0;
    a = 0;
    jumpTime = 0;
    floatTime = FLOAT_TIME;
    isFloat = 0;
    draw();
}

Player::~Player(){

}

/* void Player::update(){ */
/*     ry += v; */
/*     v += a; */
/*     int floorY = floors->getY()-(floors->infos[x-floors->getX()].height-floors->getH()); */
/*     /1* stringstream s1; *1/ */
/*     /1* s1 << "<DEBUG>: player Y: " << ry << " floor Y: " << floorY; *1/ */
/*     /1* drawText(0, 41, s1.str(), RED, GREEN); *1/ */

/*     int floorType = floors->infos[x-floors->getX()].type; */
/*     if(floorY <= ry){ */
/*         jumpTime = 0; */
/*         v = 0; */
/*         a = 0; */
/*         y = floorY-1; */
        
/*         /1* stringstream s2; *1/ */
/*         /1* s2 << "<DEBUG>: player Y: " << ry << " floor Y: " << floorY << " type: " << floorType; *1/ */
/*         /1* drawText(0, 40, s2.str(), RED, GREEN); *1/ */
/*         if(floorType == BREAK_FLOOR || floorType == DEATH_FLOOR){ */
/*             isDead = 1; */
/*         } */
/*         else if(floorType == SCORE_FLOOR){ */

/*         } */
/*     } */
/*     else{ */
/*         if(jumpTime == 0 && floorType == BREAK_FLOOR){ */
/*             isDead = 1; */
/*         } */
/*         y = ry; */
/*     } */
/* } */

void Player::update2(){
    if(floatTime == FLOAT_TIME-1){
        a = PLAYERA/2;
        floatTime++;
        isFloat = 0;
        jumpTime = 1;
    }
    else if(floatTime == FLOAT_TIME){}
    else{
        floatTime++;
    }
    ry += v;
    v += a;
    y = ry;
}

void Player::draw(){
   drawPixel(x, y, BULE); 
}

void Player::jump(){
    if(jumpTime == 0){
        v = PLAYERV;
        a = PLAYERA;
        jumpTime++;
    }
    else if(jumpTime == 1){
        v = PLAYERV;
        a = PLAYERA;
        jumpTime++;
    }
}

void Player::floatStart(){
    floatTime = 0;
    y -= FLOATH;
    ry -= FLOATH;
    a = 0;
    isFloat = 1;
}

void Player::left(){
    //x = std::max(x-1, 1);
    x--;
}

void Player::right(){
    //x = std::min(x+1, 30);
    x++;
}
