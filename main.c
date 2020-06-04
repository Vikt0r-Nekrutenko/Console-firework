#include "window.h"
#include "renderer.h"

typedef struct _entity {
    vector2d _pos;
    vector2d _vel;
    ConsoleColor _col;
    char    _sym;
} entity;

#define ents_num 80
entity ents[ents_num];

void ConsoleWindowUpdateProc(ConsoleWindow *wnd, const float dt)
{
    for (int i = 0; i < ents_num; ++i) {
        entity *ent = &ents[i];

        ent->_pos._x += ent->_vel._x * dt;
        ent->_pos._y += ent->_vel._y * dt;

        if (ent->_pos._x < 0)                       { ent->_pos._x = 0; ent->_vel._x *= -1.f; }
        if (ent->_pos._x >= wnd->_rend->_size.X)    { ent->_pos._x = wnd->_rend->_size.X - 1; ent->_vel._x *= -1.f; }
        if (ent->_pos._y < 0)                       { ent->_pos._y = 0; ent->_vel._y *= -1.f; }
        if (ent->_pos._y >= wnd->_rend->_size.Y)    { ent->_pos._y = wnd->_rend->_size.Y - 1; ent->_vel._y *= -1.f; }

        ConsoleRendererPutPixel(wnd->_rend, ent->_pos, ent->_sym, ent->_col);
    }
}

int main()
{
    for (int i = 0; i < ents_num; ++i)
    {
        ents[i]._col = 1 + rand() % 15;
        ents[i]._pos._x = rand() % 120;
        ents[i]._pos._y = rand() % 60;
        ents[i]._vel._x = 10 + rand() % 20;
        ents[i]._vel._y = 10 + rand() % 20;
        ents[i]._sym = '#';
    }
    ConsoleWindow *wnd = ConsoleWindowCreate();
    return ConsoleWindowProc(wnd);
}
