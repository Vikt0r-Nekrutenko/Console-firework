#include "renderer.h"
#include <assert.h>

ConsoleRenderer *ConsoleRendererCreate(const ConsoleWindow *wnd)
{
    ConsoleRenderer *rend = (ConsoleRenderer *)malloc(sizeof(ConsoleRenderer));
    rend->_array = (CHAR_INFO *)malloc(wnd->_size.X * wnd->_size.Y * sizeof (CHAR_INFO));
    rend->_size = wnd->_size;

    return rend;
}

void ConsoleRendererDelete(ConsoleRenderer *rend)
{
    free(rend->_array);
    free(rend);
}

void ConsoleRendererClear(ConsoleRenderer *rend)
{
    for (int i = rend->_size.X * rend->_size.Y - 1; i >= 0; --i) {
        rend->_array[i].Char.AsciiChar = ' ';
        rend->_array[i].Attributes = FB_BLACK;
    }
}

void ConsoleRendererPresent(ConsoleWindow *wnd, ConsoleRenderer *rend)
{
    COORD offset = { 0, 0 }; SMALL_RECT srect = { 0, 0, rend->_size.X, rend->_size.Y };
    WriteConsoleOutputA(wnd->_output, rend->_array, rend->_size, offset, &srect);
}

void ConsoleRendererPutPixel(ConsoleRenderer *rend, const vector2d pos, const uint8_t sym, const ConsoleColor col)
{
    int indx = rend->_size.X * (int)pos._y + (int)pos._x;
    assert(indx < rend->_size.X * rend->_size.Y && indx >= 0);
    rend->_array[indx].Char.AsciiChar = sym;
    rend->_array[indx].Attributes = col;
}
