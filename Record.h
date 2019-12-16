#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "KeyBoard.h"
#include "ScreenDraw.h"
#include <sstream>
#include <cstdio>

#define RECORDW 20
#define RECORDH 7 
#define SHOWW 22
#define SHOWH 26

typedef struct scoreInfo{
    std::string name;
    int score;
}scoreInfo;

class Record
{
public:
    Record(int w, int h, std::string tFileName); 
    ~Record(); 
    void record(int score);
    void show();

private:
    int outW;
    int outH;
    std::string fileName;
    std::vector<scoreInfo> infos;
    void readFile();
    std::string getName(int score);
    void writeFile();
};

