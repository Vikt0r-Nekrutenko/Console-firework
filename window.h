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

/**
 * @brief ConsoleWindowCreate new window
 * @return created window
 */
ConsoleWindow *ConsoleWindowCreate();

/**
 * @brief ConsoleWindowUpdateProc - update window every iterations
 */
extern void ConsoleWindowUpdateProc(ConsoleWindow *, const float);

/**
 * @brief ConsoleWindowProc - window procedure
 * @param wnd - window object
 * @return code
 */
int ConsoleWindowProc(ConsoleWindow *wnd);

/**
 * @brief ConsoleWindowSetSize - resize window
 * @param wnd - window object
 * @param width - width of window
 * @param height - height of window
 */
void ConsoleWindowSetSize(ConsoleWindow *wnd, short width, short height);

/**
 * @brief ConsoleWindowEnableFullscreen - enable fullscreen mode
 * @param wnd - window object
 */
void ConsoleWindowEnableFullscreen(ConsoleWindow *wnd);


#endif // WINDOW_H
