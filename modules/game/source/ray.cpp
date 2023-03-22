#include "ray.h"

void ray::draw(HDC bhdc)
{


	constexpr float32 s = 0.0f;

	//const float32 ratio = 600.0f / 800.0f;
	const float32 worldCenterOffsetWidth = 800.0f / 2.0f;
	const float32 worldCenterOffsetHeight = 600.0f / 2.0f;
	//const float32 newX1 = worldCenterOffsetWidth - (s / 2.0f); //p.p.x + cameraOffsetX + worldCenterOffsetWidth*ratio;
	//const float32 newY1 = worldCenterOffsetHeight - (s / 2.0f); //p.p.y + cameraOffsetY + worldCenterOffsetHeight;
	//const float32 newX2 = worldCenterOffsetWidth - (s / 2.0f); //p.p.x + cameraOffsetX + worldCenterOffsetWidth*ratio;
	//const float32 newY2 = worldCenterOffsetHeight - (s / 2.0f); //p.p.y + cameraOffsetY + worldCenterOffsetHeight;

	//coy; cox;

	MoveToEx(bhdc, x1 + worldCenterOffsetWidth + cox, y1 + worldCenterOffsetHeight + coy, 0);
	LineTo(bhdc, x2 + worldCenterOffsetWidth + cox, y2 + worldCenterOffsetHeight + coy);
}

void ray::depose(float32 dx, float32 dy) {
	x1 += dx;
	y1 += dy;
	x2 += dx;
	y2 += dy;
}

void ray::setCameraOffset(float32 x, float32 y)
{
	cox = x;
	coy = y;
}
