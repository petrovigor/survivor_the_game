#pragma once

#include "types.h"
#include "point.h"
#include <Windows.h>

struct ray
{
	worldPoint from, to;
	//float32 x1, y1;
	//float32 x2, y2;
	//float32 cox, coy;

	ray() = default;
	ray(worldPoint _from, worldPoint _to)
		: from(_from)
		, to(_to)
	{ }

	//void setCameraOffset(float32 x, float32 y);
	void draw(HDC bhdc, worldPoint playerPos);

};
