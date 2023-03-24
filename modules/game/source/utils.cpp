#include "utils.h"
#include <math.h>

float abc(float32 x1, float32 y1, float32 x2, float32 y2) {
  return atan2f(y2 - y1, x2 - x1);
}

float abp(worldPoint from, worldPoint to)
{
  return abc(from.p.x, from.p.y, to.p.x, to.p.y);
}
