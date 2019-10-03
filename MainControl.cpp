#include "MainControl.h"
#include <iostream>
#include "ScreenDraw.h"
#include <unistd.h>
using namespace std;



MainControl::MainControl(int bt){
    breakTime = bt;
    init_keyboard();
    cout << "\033[?25l\n"; 
}

MainControl::~MainControl(){
    close_keyboard();
    cout << "\033[?25h\n"; 
}

void MainControl::start(){
    screenClear();
    while(1){
        drawRect(0, 0, MWIDTH, MHEIGHT, WHITE);
        loadWelcome();
        int key = waitKey();
        if(key == 27){
            break;
        }
        else if(key == '1'){
            screenClear();
            Scene scene(0, 0, MWIDTH, MHEIGHT);
            //waitKey();
            scene.start();
            while(1){
                if(scene.update()){
                    scene.draw();
                    waitKey();
                    break;
                }
                scene.draw();
                if(kbhit()){
                    int key = readch();
                    if(key == 27){
                        break;
                    }
                    else if(key == ' '){
                        scene.playerJump();
                    }
                    else if(key == 'p'){
                        if(scene.getIsStop()){
                            scene.start();
                        }                 
                        else{
                            scene.stop();
                        }
                    }
                    else if(key == 'w'){
                    }
                    else if(key == 's'){
                    }
                    else if(key == 'a'){
                    }
                    else if(key == 'd'){
                    }

                }
                usleep(breakTime*1000);
            }
        }
        else if(key == '2'){
            screenClear();
            Scene scene1(0, 0, MWIDTH2, MHEIGHT2);
            Scene scene2(0, MHEIGHT2, MWIDTH2, MHEIGHT2);
            scene1.start();
            scene2.start();
            while(1){
                scene1.update();
                scene2.update();
                scene1.draw();
                scene2.draw();
                if(scene1.getIsGameOver() && scene2.getIsGameOver()){
                    waitKey();
                    break;
                }
                if(kbhit()){
                    int key = readch();
                    if(key == 27){
                        break;
                    }
                    else if(key == 'a'){
                        scene1.playerJump();
                    }
                    else if(key == 'l'){
                        scene2.playerJump();
                    }
                    else if(key == 'w'){
                    }
                    else if(key == 's'){
                    }
                    else if(key == 'a'){
                    }
                    else if(key == 'd'){
                    }

                }
                usleep(breakTime*1000);
            }

        }
        usleep(breakTime*1000);
    }
    screenClear();
} 

void MainControl::loadWelcome(){
    int shiftX = (MWIDTH-TITLEW)/2;
    int shiftY = (MHEIGHT-TITLEH)/2;
    for(int i = 0; i < TITLEH; ++i){
        for(int j = 0; j < TITLEW; ++j){
            drawPixel(shiftX+j, shiftY+i, Title[i][j]);
        }
    } 
    drawText(shiftX+43, shiftY+12, "PLAYER1: PRESS '1' TO PALY", WHITE, BLACK);
    drawText(shiftX+45, shiftY+13, "press 'space' to jump", WHITE, BLACK);
    drawText(shiftX+43, shiftY+14, "PLAYER2: PRESS '2' TO PALY", WHITE, BLACK);
    drawText(shiftX+45, shiftY+15, "player1 press 'a' to jump", WHITE, BLACK);
    drawText(shiftX+45, shiftY+16, "player1 press 'l' to jump", WHITE, BLACK);
    drawText(shiftX+43, shiftY+17, "PRESS 'p' TO PAUSE", WHITE, BLACK);
    drawText(shiftX+43, shiftY+18, "PRESS 'ESC' TO QUIT", WHITE, BLACK);
    drawText(shiftX+53, shiftY+19, "HAVE FUN!!!", RED, BLACK);
    drawText(shiftX+53, shiftY+21, "BY  MURCHERFUL", BULE, BLACK);
}

int MainControl::waitKey(){
    while(!kbhit()){
        usleep(breakTime*1000);
    }
    return readch();
}
