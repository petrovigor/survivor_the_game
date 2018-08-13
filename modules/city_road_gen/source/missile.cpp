#include "missile.h"

e4_missile::e4_missile(float x, float y, float a, float r, float s) {
	e4_missile::x = x;
	e4_missile::y = y;
	e4_missile::a = a;
	e4_missile::r = r;
	e4_missile::s = s;
}

void e4_missile::draw(HDC hdc) {
	if(render) {
		Ellipse(hdc, (int)(x - r + cx), (int)(y - r + cy), (int)(x + r + cx), (int)(y + r + cy));
	}
}

void e4_missile::move(float deltaTime) {
	float x = e4_missile::x + s * deltaTime * cos(a);
	float y = e4_missile::y + s * deltaTime * sin(a);

	setXY(x, y);
}