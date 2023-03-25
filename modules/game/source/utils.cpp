#include "utils.h"
#include <math.h>

float32 abc(float32 x1, float32 y1, float32 x2, float32 y2)
{
  return atan2f(y2 - y1, x2 - x1);
}

float32 abp(worldPoint from, worldPoint to)
{
  return abc(from.p.x, from.p.y, to.p.x, to.p.y);
}

float32 dbc(float32 x1, float32 y1, float32 x2, float32 y2)
{
  const float32 dx = x2 - x1;
  const float32 dy = y2 - y1;
  return sqrt(dx * dx + dy * dy);
}

float32 dbp(worldPoint from, worldPoint to)
{
  return dbc(from.p.x, from.p.y, to.p.x, to.p.y);
}

