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
void drawPixelC(int x, int y, char c1, char c2, int color, int backColor);
void screenClear();
void clearRect(int x, int y, int w, int h);
void drawLine(int x, int y, int l, bool hori, int color);
void drawLineC(int x, int y, int l, char c1, char c2, bool hori, int color, int backColor);
void drawRect(int x, int y, int w, int h, int color);
void drawWholeRect(int x, int y, int w, int h, int color);
void drawText(int x, int y, string str, int color, int backColor);
