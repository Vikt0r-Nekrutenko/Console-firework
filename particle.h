#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector2d.h"
#include "renderer.h"

#define PARTICLE_SETS_NUM 5
#define PARTICLE_SET_RADIUS 17
#define PARTICLES_NUM (PARTICLE_SET_RADIUS + PARTICLE_SET_RADIUS - 1) * (PARTICLE_SET_RADIUS + PARTICLE_SET_RADIUS - 1)

typedef struct _particle {
    vector2d _pos;
    vector2d _vel;
    ConsoleColor _col;
    char    _sym;
} particle;

particle particle_sets[PARTICLE_SETS_NUM][PARTICLES_NUM];

void BOOM(const MOUSE_EVENT_RECORD *mer, uint32_t n, ConsoleColor col, vector2d(*type)(const float));

BOOL ParticleIsOnField(const ConsoleWindow *wnd, particle *ent);


#endif // PARTICLE_H
