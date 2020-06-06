#ifndef BOOM_TYPE_H
#define BOOM_TYPE_H

#include "vector2d.h"
#include <math.h>

vector2d ConsoleBoomType1(const float angle) {
    vector2d vel = { 15 * cosf(angle), 15 * sinf(angle) };
    return vel;
}

vector2d ConsoleBoomType2(const float angle) {
    vector2d vel = { 15 * cosf(angle), 15 * -sinf(angle) };
    return vel;
}

vector2d ConsoleBoomType3(const float angle) {
    vector2d vel = { 15 * -cosf(angle), 15 * sinf(angle) };
    return vel;
}

vector2d ConsoleBoomType4(const float angle) {
    vector2d vel = { 15 * -cosf(angle), 15 * -sinf(angle) };
    return vel;
}

vector2d ConsoleBoomType5(const float angle) {
    vector2d vel = { 15 * sinf(angle), 15 * cosf(angle) };
    return vel;
}

vector2d ConsoleBoomType6(const float angle) {
    vector2d vel = { 15 * sinf(angle), 15 * -cosf(angle) };
    return vel;
}

vector2d ConsoleBoomType7(const float angle) {
    vector2d vel = { 15 * -sinf(angle), 15 * cosf(angle) };
    return vel;
}

vector2d ConsoleBoomType8(const float angle) {
    vector2d vel = { 15 * -sinf(angle), 15 * -cosf(angle) };
    return vel;
}

#endif // BOOM_TYPE_H
