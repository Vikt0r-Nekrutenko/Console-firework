#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"
#include "vector2d.h"

typedef enum _ConsoleColor {
    FB_BLACK        = 0U,
    FG_DARK_BLUE    = 1U,
    FG_DARK_GREEN   = 2U,
    FG_DARK_CYAN    = 3U,
    FG_DARK_RED     = 4U,
    FG_DARK_MAGENTA = 5U,
    FG_DARK_YELLOW  = 6U,
    FG_GREY         = 7U,
    FG_DARK_GREY    = 8U,
    FG_BLUE         = 9U,
    FG_GREEN        = 10U,
    FG_CYAN         = 11U,
    FG_RED          = 12U,
    FG_MAGENTA      = 13U,
    FG_YELLOW       = 14U,
    FG_WHITE        = 15U,

    BG_DARK_BLUE    = 16U,
    BG_DARK_GREEN   = 32U,
    BG_DARK_CYAN    = 48U,
    BG_DARK_RED     = 64U,
    BG_DARK_MAGENTA = 80U,
    BG_DARK_YELLOW  = 96U,
    BG_GREY         = 112U,
    BG_DARK_GREY    = 128U,
    BG_BLUE         = 144U,
    BG_GREEN        = 160U,
    BG_CYAN         = 176U,
    BG_RED          = 192U,
    BG_MAGENTA      = 208U,
    BG_YELLOW       = 224U,
    BG_WHITE        = 230U,
} ConsoleColor;

typedef struct _ConsoleRenderer {
    CHAR_INFO *_array;
    COORD      _size;
} ConsoleRenderer;

ConsoleRenderer *ConsoleRendererCreate(const ConsoleWindow *wnd);

void ConsoleRendererDelete(ConsoleRenderer *rend);

void ConsoleRendererClear(ConsoleRenderer *rend);

void ConsoleRendererPresent(ConsoleWindow *wnd, ConsoleRenderer *rend);

void ConsoleRendererPutPixel(ConsoleRenderer *rend, const vector2d pos, const uint8_t sym, const ConsoleColor col);

#endif // RENDERER_H
