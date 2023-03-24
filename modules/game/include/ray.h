#pragma once

#include "types.h"
#include "point.h"
#include <Windows.h>

struct ray
{
	float32 x1, y1;
	float32 x2, y2;
	float32 cox, coy;

	ray(float32 _x1, float32 _y1, float32 _x2, float32 _y2)
		: x1(_x1)
		, y1(_y1)
		, x2(_x2)
		, y2(_y2)
		, cox(0.0)
		, coy(0.0)
	{ }

	void setCameraOffset(float32 x, float32 y);
	void draw(HDC bhdc, const worldPoint &wp);

};
