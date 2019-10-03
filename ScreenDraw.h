#pragma once
#include <string>

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BULE 4
#define PURPLE 5
#define DARKGREEN 6
#define WHITE 7

using namespace std;

void drawPixel(int x, int y, int color);
void screenClear();
void clearRect(int x, int y, int w, int h);
void drawLine(int x, int y, int l, bool hori, int color);
void drawRect(int x, int y, int w, int h, int color);
void drawWholeRect(int x, int y, int w, int h, int color);
void drawText(int x, int y, string str, int color, int backColor);
