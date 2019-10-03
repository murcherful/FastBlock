#include "Player.h"
#include <sstream>

Player::Player(int tx, int ty, Floor* tfloors){
    x = tx;
    y = ty;
    rx = tx;
    ry = ty;
    floors = tfloors;
    v = 0;
    a = 0;
    jumpTime = 0;
    isDead = 0;
    draw();
}

Player::~Player(){

}

void Player::update(){
    ry += v;
    v += a;
    int floorY = floors->getY()-(floors->infos[x-floors->getX()].height-floors->getH());
    /* stringstream s1; */
    /* s1 << "<DEBUG>: player Y: " << ry << " floor Y: " << floorY; */
    /* drawText(0, 41, s1.str(), RED, GREEN); */

    int floorType = floors->infos[x-floors->getX()].type;
    if(floorY <= ry){
        jumpTime = 0;
        v = 0;
        a = 0;
        y = floorY-1;
        
        /* stringstream s2; */
        /* s2 << "<DEBUG>: player Y: " << ry << " floor Y: " << floorY << " type: " << floorType; */
        /* drawText(0, 40, s2.str(), RED, GREEN); */
        if(floorType == BREAK_FLOOR || floorType == DEATH_FLOOR){
            isDead = 1;
        }
        else if(floorType == SCORE_FLOOR){

        }
    }
    else{
        if(jumpTime == 0 && floorType == BREAK_FLOOR){
            isDead = 1;
        }
        y = ry;
    }
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

bool Player::getIsDead(){
    return isDead;
}

int Player::getY(){
    return y;
}
