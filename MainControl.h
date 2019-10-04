#pragma once
#include "KeyBoard.h"
#include "Data.h"
#include "Record.h"
#include "Scene.h"
#define MWIDTH 70
#define MHEIGHT 30
#define MWIDTH2 70
#define MHEIGHT2 25
#define HELPERW 22
#define HELPERH 26


class MainControl
{
public:
    MainControl(int bt); 
    ~MainControl(); 
    void start();
private:
    int breakTime;
    Record * rec;
    void loadWelcome();
    void loadHelper();
    int waitKey();
};


