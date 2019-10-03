#pragma once
#include "KeyBoard.h"
#include "Data.h"
#include "Scene.h"
#define MWIDTH 70
#define MHEIGHT 30
#define MWIDTH2 70
#define MHEIGHT2 25

class MainControl
{
public:
    MainControl(int bt); 
    ~MainControl(); 
    void start();
private:
    int breakTime;
    void loadWelcome();
    int waitKey();
};


