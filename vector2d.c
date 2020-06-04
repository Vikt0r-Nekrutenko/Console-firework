#include "vector2d.h"
#include <math.h>

float distance_to(const vector2d *source, const vector2d *destination)
{
    return sqrtf(powf(source->_x - destination->_x, 2.f) + powf(source->_y - destination->_y, 2.f));
}
