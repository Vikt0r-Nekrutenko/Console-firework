#include "window.h"
#include "renderer.h"
#include "boom_type.h"
#include "particle.h"

void ConsoleWindowUpdateProc(ConsoleWindow *wnd, const float dt)
{
    for (int j = 0; j < PARTICLE_SETS_NUM; ++j) {
        for (int i = 0; i < PARTICLES_NUM; ++i) {
            particle *ent = &particle_sets[j][i];
            if (ent->_pos._x > 0 && ent->_pos._y > 0)
            {
                ent->_pos._x += ent->_vel._x * dt;
                ent->_pos._y += ent->_vel._y * dt;

                if (ParticleIsOnField(wnd, ent)) {
                    ConsoleRendererPutPixel(wnd->_rend, ent->_pos, ent->_sym, ent->_col);
                }
            }
        }
    }
}

void ConsoleWindowMouseEventProc(ConsoleWindow *wnd, const MOUSE_EVENT_RECORD *mer)
{
    static uint32_t set_number = 0;
    static int boom_type = 0;
    const uint32_t max_types = 7;

    if (mer->dwEventFlags == MOUSE_WHEELED) {
        if (HIWORD(mer->dwButtonState) < UINT16_MAX >> 1) {
            if (boom_type > (int)max_types - 1) boom_type = 0; else boom_type++;
        } else if (HIWORD(mer->dwButtonState) > UINT16_MAX >> 1) {
            if (boom_type < 1) boom_type = max_types; else boom_type--;
        }
    } else if (mer->dwEventFlags == 0) {
        if (mer->dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            switch (boom_type) {
            case 0: BOOM(mer, set_number, FG_MAGENTA,   &ConsoleBoomType1); break;
            case 1: BOOM(mer, set_number, FG_CYAN,      &ConsoleBoomType2); break;
            case 2: BOOM(mer, set_number, FG_BLUE,      &ConsoleBoomType3); break;
            case 3: BOOM(mer, set_number, FG_GREEN,     &ConsoleBoomType4); break;
            case 4: BOOM(mer, set_number, FG_CYAN,      &ConsoleBoomType5); break;
            case 5: BOOM(mer, set_number, FG_RED,       &ConsoleBoomType6); break;
            case 6: BOOM(mer, set_number, FG_MAGENTA,   &ConsoleBoomType7); break;
            case 7: BOOM(mer, set_number, FG_YELLOW,    &ConsoleBoomType8); break;
            }
        }
        if (set_number >= PARTICLE_SETS_NUM) set_number = 0;
        else set_number++;
    }
}

int main()
{
    ConsoleWindow *wnd = ConsoleWindowCreate();
    return ConsoleWindowProc(wnd);
}
