#include "ray.h"

void ray::draw(HDC bhdc)
{
	MoveToEx(bhdc, x1 + cox, y1 + coy, 0);
	LineTo(bhdc, x2 + cox, y2 + coy);
}

void ray::setCameraOffset(float32 x, float32 y)
{
	cox = x;
	coy = y;
}
