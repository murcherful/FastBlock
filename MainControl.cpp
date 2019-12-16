#include "MainControl.h"
#include <iostream>
#include "ScreenDraw.h"
#ifdef _WIN32
#include<Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

MainControl::MainControl(int bt){
    breakTime = bt;
    rec = new Record(MWIDTH, MHEIGHT, "record.txt");
    init_keyboard();
	hideCursor();
    //cout << "\033[?25l\n"; //隐藏光标
}

MainControl::~MainControl(){
    delete rec;
    close_keyboard();
	showCursor();
    //cout << "\033[?25h\n"; //打开光标
}

void MainControl::start(){
    while(1){
        //screenClear();
        drawRect(0, 0, MWIDTH, MHEIGHT, BULE);
        drawWholeRect(1, 1, MWIDTH-2, MHEIGHT-2, WHITE);
        loadWelcome();
        int key = waitKey();
        if(key == 27){
            break;
        }
        else if(key == 'r'){
            rec->show();
            while(waitKey() != 27){}
        }
        else if(key == 'h'){
            loadHelper();
            while(waitKey() != 27){}
        }
        else if(key == '1'){
            screenClear();
            Scene scene(0, 0, MWIDTH, MHEIGHT);
            //waitKey();
            scene.start();
            while(1){
                if(scene.update()){
                    scene.draw();
                    rec->record(scene.getScore());
                    while(waitKey() != 27){}
                    break;
                }
                scene.draw();
                if(kbhit()){
                    int key = readch();
                    if(key == 27){
                        break;
                    }
                    else if(key == ' '){
                        /* scene.playerJump(); */
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
                        scene.playerJump();
                    }
                    else if(key == 's'){
                    }
                    else if(key == 'a'){
                        scene.playerLeft();
                    }
                    else if(key == 'd'){
                        scene.playerRight();
                    }

                }
#ifdef _WIN32
				Sleep(breakTime);
#else
                usleep(breakTime*1000);
#endif
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
                    rec->record(scene1.getScore());
                    rec->record(scene2.getScore());
                    while(waitKey() != 27){}
                    break;
                }
                if(kbhit()){
                    int key = readch();
                    if(key == 27){
                        break;
                    }
                    else if(key == 'p'){
                        if(scene1.getIsStop()){
                            scene1.start();
                            scene2.start();
                        }                 
                        else{
                            scene1.stop();
                            scene2.stop();
                        }
                    }

                    else if(key == 'w'){
                        scene1.playerJump();
                    }
                    else if(key == 'i'){
                        scene2.playerJump();
                    }
                    else if(key == 'a'){
                        scene1.playerLeft();
                    }
                    else if(key == 'j'){
                        scene2.playerLeft();
                    }
                    else if(key == 'd'){
                        scene1.playerRight();
                    }
                    else if(key == 'l'){
                        scene2.playerRight();
                    }

                }
#ifdef _WIN32
				Sleep(breakTime);
#else
                usleep(breakTime*1000);
#endif
            }

        }
#ifdef _WIN32
		Sleep(breakTime);
#else
        usleep(breakTime*1000);
#endif
    }
    screenClear();
	setPosition(0, 0);
    // cout << "\033[0;0H"; // 光标置于0， 0
} 

void MainControl::loadWelcome(){
    int shiftX = (MWIDTH-TITLEW)/2;
    int shiftY = (MHEIGHT-TITLEH)/2;
    for(int i = 0; i < TITLEH; ++i){
        for(int j = 0; j < TITLEW; ++j){
            drawPixel(shiftX+j, shiftY+i, Title[i][j]);
        }
    } 
    /* drawText(shiftX+43, shiftY+12, "PLAYER1: PRESS '1' TO PALY", WHITE, BLACK); */
    /* drawText(shiftX+45, shiftY+13, "press 'space' to jump", WHITE, BLACK); */
    /* drawText(shiftX+43, shiftY+14, "PLAYER2: PRESS '2' TO PALY", WHITE, BLACK); */
    drawText(shiftX+43, shiftY+15, "PRESS 'h' TO SEE HELP", WHITE, BLACK);
    /* drawText(shiftX+45, shiftY+16, "player1 press 'l' to jump", WHITE, BLACK); */
    /* drawText(shiftX+43, shiftY+17, "PRESS 'p' TO PAUSE", WHITE, BLACK); */
    /* drawText(shiftX+43, shiftY+18, "PRESS 'ESC' TO QUIT", WHITE, BLACK); */
    /* drawText(shiftX+43, shiftY+18, "PRESS 'r' TO SEE RECORD", WHITE, BLACK); */
    drawText(shiftX+51, shiftY+18, "HAVE FUN!!!:)", RED, BLACK);
    drawText(shiftX+51, shiftY+20, "BY  MURCHERFUL", BULE, BLACK);
}

void MainControl::loadHelper(){
    int shiftX = (MWIDTH-HELPERW)/2;
    int shiftY = (MHEIGHT-HELPERH)/2;
    drawRect(shiftX, shiftY, HELPERW, HELPERH, BULE);
    drawWholeRect(shiftX+1, shiftY+1, HELPERW-2, HELPERH-2, WHITE);

    drawText(shiftX+8, shiftY+2, "HELPER", BLACK, WHITE);

    drawText(shiftX+2, shiftY+4, "ONE PLAYER: PRESS '1' TO PALY", BLACK, WHITE);
    drawText(shiftX+4, shiftY+5, "press 'w' to jump", BLACK, WHITE);
    drawText(shiftX+4, shiftY+6, "press 'a' to move left", BLACK, WHITE);
    drawText(shiftX+4, shiftY+7, "press 'd' to move right", BLACK, WHITE);
    drawText(shiftX+2, shiftY+8, "TWO PLAYERS: PRESS '2' TO PALY", BLACK, WHITE);
    drawText(shiftX+4, shiftY+9, "player1 press 'w' to jump", BLACK, WHITE);
    drawText(shiftX+4, shiftY+10, "player1 press 'a' to move left", BLACK, WHITE);
    drawText(shiftX+4, shiftY+11, "player1 press 'd' to move right", BLACK, WHITE);
    drawText(shiftX+4, shiftY+12, "player2 press 'i' to jump", BLACK, WHITE);
    drawText(shiftX+4, shiftY+13, "player2 press 'j' to move left", BLACK, WHITE);
    drawText(shiftX+4, shiftY+14, "player2 press 'l' to move right", BLACK, WHITE);
    drawText(shiftX+2, shiftY+15, "PRESS 'p' TO PAUSE", BLACK, WHITE);
    drawText(shiftX+2, shiftY+16, "PRESS 'ESC' TO QUIT OR GO BACK", BLACK, WHITE);
    drawText(shiftX+2, shiftY+17, "PRESS 'r' TO SEE RECORD", BLACK, WHITE);
    drawText(shiftX+2, shiftY+19, "IN THIS GAME YOU NEED TO KEEP THE", BLACK, WHITE);
    drawText(shiftX+2, shiftY+20, "BLUE BLOCK AWAY FROM RED BLOCKS AND", BLACK, WHITE);
    drawText(shiftX+2, shiftY+21, "WHITE BREAKS. YOUR SCORE WILL", BLACK, WHITE);
    drawText(shiftX+2, shiftY+22, "INCREASE UNTIL YOU DIE. YOU ONLY", BLACK, WHITE);
    drawText(shiftX+2, shiftY+23, "GOT ONE LIFE.", BLACK, WHITE);

    /* drawText(shiftX+2, shiftY+10, "HAVE FUN!!!:)", RED, WHITE); */
    /* drawText(shiftX+2, shiftY+11, "BY  MURCHERFUL", BULE, WHITE); */
   
}

int MainControl::waitKey(){
    while(!kbhit()){
#ifdef _WIN32
		Sleep(breakTime);
#else
        usleep(breakTime*1000);
#endif
    }
    return readch();
}
