#ifndef VECTOR2D_H
#define VECTOR2D_H

typedef struct _vector2d {
    float _x, _y;
} vector2d;

float distance_to(const vector2d *source, const vector2d *destination);

#endif // VECTOR2D_H
