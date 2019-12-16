#include <iostream>
#include <string>
#include <sstream>
#include "ScreenDraw.h"
#include <cstdio>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
void clearAttrib() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_SUFFIX(WHITE) | BACKGROUND_SUFFIX(BLACK));
}

void setBackgroundColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_SUFFIX(color));
}

void setForegroundColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_SUFFIX(color));
}

#endif

void showCursor() {
#ifdef _WIN32
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = true; 
	SetConsoleCursorInfo(handle, &CursorInfo);
#else
	cout << "\033[?25h\n";
#endif
}

void hideCursor() {
#ifdef _WIN32
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false; 
	SetConsoleCursorInfo(handle, &CursorInfo);
#else
	cout << "\033[?25l\n";
#endif
}

void setPosition(int x, int y) {
	int tx = max(x, 0) + 1;
	int ty = max(y, 0) + 1;
#ifdef _WIN32
	COORD point = { 2*tx-1, ty };  
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
#else
	printf("\033[%d;%dH", ty, 2 * tx - 1);
#endif
}

void drawPixel(int x, int y, int color){
#ifdef _WIN32
	setPosition(x, y);
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_SUFFIX(color));
	setBackgroundColor(color);
	printf("  ");
	clearAttrib();
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_SUFFIX(BLACK));
#else
    int tx = max(x, 0) + 1;
    int ty = max(y, 0) + 1;
    printf("\033[%d;%dH\033[4%dm  \033[0m\n", ty, 2*tx-1, color);
#endif
}

void drawPixelC(int x, int y, char c1, char c2, int color, int backColor){
#ifdef _WIN32
	setPosition(x, y);
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_SUFFIX(color));
	setBackgroundColor(color);
	printf("%c%c", c1, c2);
	clearAttrib();
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_SUFFIX(BLACK));
#else

    int tx = (x, 0) + 1;
    int ty = (y, 0) + 1;
    printf("\033[%d;%dH\033[3%dm\033[4%dm%c%c\033[0m\n", ty, 2*tx-1, color, backColor, c1, c2);
#endif
}
void screenClear(){
#ifdef _WIN32
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the
									   cursor */
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in
										the current buffer */

										/* get the number of character cells in the current buffer */
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */

	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputCharacter");

	/* get the current text attribute */

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "ConsoleScreenBufferInfo");

	/* now set the buffer's attributes accordingly */

	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputAttribute");

	/* put the cursor at (0, 0) */

	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");
#else 
    printf("\033[2J\n");
#endif 
}

void clearRect(int x, int y, int w, int h){
#ifdef _WIN32
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_SUFFIX(WHITE)| BACKGROUND_SUFFIX(BLACK));
	clearAttrib();
	for (int i = 0; i < h; ++i) {
		setPosition(x, y + i);
		for (int j = 0; j < w; ++j) {
			printf("  ");
		}
	}
	printf("\n");
#else 
    printf("\033[0m");
    for(int i = 0; i < h; ++i){ 
        printf("\033[%d;%dH", y+1+i, 2*(x+1)-1);
        for(int j = 0; j < w; ++j){
            printf("  ");
        }
    }
    printf("\n");
#endif 
}

void drawLine(int x, int y, int l, bool hori, int color){
    if(hori){
#ifdef _WIN32
		setPosition(x, y);
		setBackgroundColor(color);
		for (int i = 0; i < l; ++i) {
			printf("  ");
		}
		clearAttrib();
#else 
        printf("\033[%d;%dH", y+1, 2*(x+1)-1);
        printf("\033[4%dm", color);
        for(int i = 0; i < l; ++i){
            printf("  ");
        }
        printf("\033[0m\n");
#endif 
    }
    else{
        for(int i = 0; i < l; ++i){
            drawPixel(x, y+i, color);
        }
    }
}

void drawLineC(int x, int y, int l, char c1, char c2, bool hori, int color, int backColor){
    if(hori){
#ifdef _WIN32
		setPosition(x, y);
		setBackgroundColor(color);
		for (int i = 0; i < l; ++i) {
			printf("%c%c", c1, c2);
		}
		clearAttrib();
#else 
        printf("\033[%d;%dH", y+1, 2*(x+1)-1);
        printf("\033[3%dm\033[4%dm", color, backColor);
        for(int i = 0; i < l; ++i){
            printf("%c%c", c1, c2);
        }
        printf("\033[0m\n");
#endif
    }
    else{
        for(int i = 0; i < l; ++i){
            drawPixelC(x, y+i, c1, c2, color, backColor);
        }
    }
}

void drawRect(int x, int y, int w, int h, int color){
    drawLine(x, y, w, 1, color);
    drawLine(x, y+h-1, w, 1, color);
    drawLine(x, y, h, 0, color);
    drawLine(x+w-1, y, h, 0, color);
}

void drawWholeRect(int x, int y, int w, int h, int color){
    for(int i = 0; i < h; ++i){
        drawLine(x, y+i, w, 1, color);
    }
}

void drawText(int x, int y, string str, int color, int backColor){
#ifdef _WIN32
	setPosition(x, y);
	setForegroundColor(color);
	setBackgroundColor(backColor);
	printf(str.c_str());
	clearAttrib();
#else 
    printf("\033[%d;%dH", y+1, 2*x+1);
    printf("\033[3%dm", color);
    printf("\033[4%dm", backColor);
    printf(str.c_str());
    printf("\033[0m\n");
#endif 
}
