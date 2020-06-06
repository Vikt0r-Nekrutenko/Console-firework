#include "window.h"
#include "renderer.h"

typedef struct _entity {
    vector2d _pos;
    vector2d _vel;
    ConsoleColor _col;
    char    _sym;
} entity;

#define ents_num 1089 * 5
entity ents[ents_num];

void fill_ents(const MOUSE_EVENT_RECORD *mer, uint32_t n, ConsoleColor col, vector2d(*type)(const float))
{
    vector2d center = { mer->dwMousePosition.X, mer->dwMousePosition.Y };
    float radius = 17;

    for (int y = center._y - radius; y < center._y + radius; ++y) {
        for (int x = center._x - radius; x < center._x + radius; ++x) {
            vector2d pos = { x, y };
            float dist = distance_to(&center, &pos);
//            if (dist < radius)
            {
                vector2d dpos = { pos._x - center._x, pos._y - center._y };
                float angle = atan2f(dpos._y, dpos._x) - atanf(45);

                ents[n]._pos = pos;
                ents[n]._vel = type(angle);
                ents[n]._sym = '*';

                if (dist < radius / 4)                      ents[n++]._col = col;
                else if (dist < radius / 2)                 ents[n++]._col = col - 8;
                else if (dist < radius / 2 + radius / 4)    ents[n++]._col = col - 2;
                else if (dist < radius / 2 + radius / 2)    ents[n++]._col = col - 10;
                else ents[n++]._col = FG_DARK_RED;
            }
        }
    }
}

vector2d type1(const float angle) {
    vector2d vel = { 15 * cosf(angle), 15 * sinf(angle) };
    return vel;
}

vector2d type2(const float angle) {
    vector2d vel = { 15 * cosf(angle), 15 * -sinf(angle) };
    return vel;
}

vector2d type3(const float angle) {
    vector2d vel = { 15 * -cosf(angle), 15 * sinf(angle) };
    return vel;
}

vector2d type4(const float angle) {
    vector2d vel = { 15 * -cosf(angle), 15 * -sinf(angle) };
    return vel;
}

vector2d type5(const float angle) {
    vector2d vel = { 15 * sinf(angle), 15 * cosf(angle) };
    return vel;
}

vector2d type6(const float angle) {
    vector2d vel = { 15 * sinf(angle), 15 * -cosf(angle) };
    return vel;
}

vector2d type7(const float angle) {
    vector2d vel = { 15 * -sinf(angle), 15 * cosf(angle) };
    return vel;
}

vector2d type8(const float angle) {
    vector2d vel = { 15 * -sinf(angle), 15 * -cosf(angle) };
    return vel;
}

//void bounding(const ConsoleWindow *wnd, entity *ent)
//{
//    if (ent->_pos._x < 0)                       { ent->_pos._x = 0; ent->_vel._x *= -1.f; }
//    if (ent->_pos._x >= wnd->_rend->_size.X)    { ent->_pos._x = wnd->_rend->_size.X - 1; ent->_vel._x *= -1.f; }
//    if (ent->_pos._y < 0)                       { ent->_pos._y = 0; ent->_vel._y *= -1.f; }
//    if (ent->_pos._y >= wnd->_rend->_size.Y)    { ent->_pos._y = wnd->_rend->_size.Y - 1; ent->_vel._y *= -1.f; }
//}

BOOL bounding(const ConsoleWindow *wnd, entity *ent)
{
    if ((ent->_pos._x < 0) || (ent->_pos._x >= wnd->_rend->_size.X) ||
        (ent->_pos._y < 0) || (ent->_pos._y >= wnd->_rend->_size.Y)) {
        ent->_pos._x = ent->_vel._x = 0.f;
        ent->_pos._y = ent->_vel._y = 0.f;
        return FALSE;
    }
    return TRUE;
}

void ConsoleWindowUpdateProc(ConsoleWindow *wnd, const float dt)
{
    for (int i = 0; i < ents_num; ++i) {
        entity *ent = &ents[i];
        ent->_pos._x += ent->_vel._x * dt;
        ent->_pos._y += ent->_vel._y * dt;

        if (bounding(wnd, ent)) {
            ConsoleRendererPutPixel(wnd->_rend, ent->_pos, ent->_sym, ent->_col);
        }
    }
}

void ConsoleWindowMouseEventProc(ConsoleWindow *wnd, const MOUSE_EVENT_RECORD *mer)
{
    static uint32_t n = 0;
    static int type = 0;
    const uint32_t max_types = 7;

    if (mer->dwEventFlags == MOUSE_WHEELED) {
        if (HIWORD(mer->dwButtonState) < UINT16_MAX >> 1) {
            if (type > (int)max_types - 1) type = 0; else type++;
        } else if (HIWORD(mer->dwButtonState) > UINT16_MAX >> 1) {
            if (type < 1) type = max_types; else type--;
        }
    } else if (mer->dwEventFlags == 0) {
        if (mer->dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            switch (type) {
            case 0: fill_ents(mer, n, FG_MAGENTA,      &type1); break;
            case 1: fill_ents(mer, n, FG_CYAN,      &type2); break;
            case 2: fill_ents(mer, n, FG_BLUE,      &type3); break;
            case 3: fill_ents(mer, n, FG_GREEN,     &type4); break;
            case 4: fill_ents(mer, n, FG_CYAN,      &type5); break;
            case 5: fill_ents(mer, n, FG_RED,       &type6); break;
            case 6: fill_ents(mer, n, FG_MAGENTA,   &type7); break;
            case 7: fill_ents(mer, n, FG_YELLOW,    &type8); break;
            }
        }
        if (n >= ents_num) n = 0;
        else n += 1089;
    }
}

int main()
{
    memset(ents, 0, ents_num);
    ConsoleWindow *wnd = ConsoleWindowCreate();
    return ConsoleWindowProc(wnd);
}
