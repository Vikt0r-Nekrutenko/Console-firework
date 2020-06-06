#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <windows.h>

typedef struct _ConsoleWindow
{
    struct _ConsoleRenderer *_rend;
    HANDLE _output;
    HANDLE _input;
    HWND   _wnd;
    COORD  _size;
} ConsoleWindow;

ConsoleWindow *ConsoleWindowCreate();

extern void ConsoleWindowUpdateProc(ConsoleWindow *, const float);

extern void ConsoleWindowMouseEventProc(ConsoleWindow *, const MOUSE_EVENT_RECORD *);

int ConsoleWindowProc(ConsoleWindow *wnd);

void ConsoleWindowSetSize(ConsoleWindow *wnd, short width, short height);

void ConsoleWindowEnableFullscreen(ConsoleWindow *wnd);


#endif // WINDOW_H
