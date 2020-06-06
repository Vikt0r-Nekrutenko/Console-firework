#include "particle.h"

void BOOM(const MOUSE_EVENT_RECORD *mer, uint32_t n, ConsoleColor col, vector2d (*type)(const float))
{
    vector2d center = { mer->dwMousePosition.X, mer->dwMousePosition.Y };

    int i = 0;
    for (int y = center._y - PARTICLE_SET_RADIUS; y < center._y + PARTICLE_SET_RADIUS; ++y) {
        for (int x = center._x - PARTICLE_SET_RADIUS; x < center._x + PARTICLE_SET_RADIUS; ++x) {
            vector2d pos = { x, y };
            float dist = distance_to(&center, &pos);
            //            if (dist < radius)
            {
                vector2d dpos = { pos._x - center._x, pos._y - center._y };
                float angle = atan2f(dpos._y, dpos._x) - atanf(45);

                particle_sets[n][i]._pos = pos;
                particle_sets[n][i]._vel = type(angle);
                particle_sets[n][i]._sym = '*';

                if (dist < PARTICLE_SET_RADIUS / 4)                                 particle_sets[n][i++]._col = col;
                else if (dist < PARTICLE_SET_RADIUS / 2)                            particle_sets[n][i++]._col = col - 8;
                else if (dist < PARTICLE_SET_RADIUS / 2 + PARTICLE_SET_RADIUS / 4)  particle_sets[n][i++]._col = col - 2;
                else if (dist < PARTICLE_SET_RADIUS / 2 + PARTICLE_SET_RADIUS / 2)  particle_sets[n][i++]._col = col - 10;
                else particle_sets[n][i++]._col = FG_DARK_RED;
            }
        }
    }
}

WINBOOL ParticleIsOnField(const ConsoleWindow *wnd, particle *ent)
{
    if ((ent->_pos._x < 0) || (ent->_pos._x >= wnd->_rend->_size.X) ||
            (ent->_pos._y < 0) || (ent->_pos._y >= wnd->_rend->_size.Y)) {
        ent->_pos._x = ent->_vel._x = 0.f;
        ent->_pos._y = ent->_vel._y = 0.f;
        return FALSE;
    }
    return TRUE;
}
