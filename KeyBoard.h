#pragma once

#ifdef _WIN32
#include <conio.h>
#define kbhit _kbhit
#else
int kbhit(void);
#endif 

int readch(void);
void init_keyboard(void);
void close_keyboard(void);
long long getTime();
