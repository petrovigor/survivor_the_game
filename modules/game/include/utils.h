#pragma once

#include "types.h"
#include "point.h"

//calculates angle between two points
float32 abc(float32 x1, float32 y1, float32 x2, float32 y2);

//calculates angle between two points
float32 abp(worldPoint from, worldPoint to);

float32 dbc(float32 x1, float32 y1, float32 x2, float32 y2);

float32 dbp(worldPoint from, worldPoint to);

