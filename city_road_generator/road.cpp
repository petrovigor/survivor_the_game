#include "road.h"

e4_road::e4_road(void) {
	roadDirection = UNKNOWN;
	x = y = 0.0f;
	ax = bx = cx = dx = 0.0f;
	ay = by = cy = dy = 0.0f;
	horizontal = true;
	render = false;
	range = 0.0f;
	unused = false;
}

e4_road::e4_road(float x, float y, float range, int roadDirection, bool horizontal = true) {
	unused = false;
	e4_road::x = x;
	e4_road::y = y;
	e4_road::range = range;
	e4_road::roadDirection = roadDirection;
	e4_road::horizontal = horizontal;

	if(horizontal) {
		e4_road::ax = x - range;
		e4_road::ay = y - ROAD_SIZE;
		e4_road::bx = x + range;
		e4_road::by = y - ROAD_SIZE;

		e4_road::cx = x + range;
		e4_road::cy = y + ROAD_SIZE;
		e4_road::dx = x - range;
		e4_road::dy = y + ROAD_SIZE;
	} else {
		e4_road::ax = x - ROAD_SIZE;
		e4_road::ay = y - range;
		e4_road::bx = x + ROAD_SIZE;
		e4_road::by = y - range;

		e4_road::cx = x + ROAD_SIZE;
		e4_road::cy = y + range;
		e4_road::dx = x - ROAD_SIZE;
		e4_road::dy = y + range;
	}
}

void e4_road::draw(HDC hdc) {
	if(render) {
		if(horizontal) {
			MoveToEx(hdc, (int)(ax + camX), (int)(ay + camY), NULL);
			LineTo(hdc, (int)(bx + camX), (int)(by + camY));
			MoveToEx(hdc, (int)(cx + camX), (int)(cy + camY), NULL);
			LineTo(hdc, (int)(dx + camX), (int)(dy + camY));
		} else {
			MoveToEx(hdc, (int)(ax + camX), (int)(ay + camY), NULL);
			LineTo(hdc, (int)(dx + camX), (int)(dy + camY));
			MoveToEx(hdc, (int)(bx + camX), (int)(by + camY), NULL);
			LineTo(hdc, (int)(cx + camX), (int)(cy + camY));
		}
	}
}

float e4_road::getRange(void) {
	return range;
}

float e4_road::getX(void) {
	return x;
}

float e4_road::getY(void) {
	return y;
}

int e4_road::getDirection(void) {
	return roadDirection;
}

void e4_road::toDelete(void) {
	unused = true;
}

bool e4_road::isToDelete(void) {
	return unused;
}

void e4_road::setCameraCoordinates(float cx, float cy) {
	e4_road::camX = cx;
	e4_road::camY = cy;
}

//e4_road *e4_road::getSelfPointer(void) {
//	return this;
//}

bool e4_road::presumeCollisionRectangle(float x, float y, float hw, float hh) {
	return x + hw > ax && x - hw < bx && y + hh > ay && y - hh < cy;
}

void e4_road::checkRender(void) {
	render = (ax + camX < 640.0f) && (bx + camX < 640.0f) && (cx + camX < 640.0f) && (dx + camX < 640.0f) ||
		(ay + camY < 480.0f) && (by + camY < 480.0f) && (cy + camY < 480.0f) && (dy + camY < 480.0f) ||
		(ax + camX > 0.0f) && (bx + camX > 0.0f) && (cx + camX > 0.0f) && (dx + camX > 0.0f) ||
		(ay + camY > 0.0f) && (by + camY > 0.0f) && (cy + camY > 0.0f) && (dy + camY > 0.0f);
}

void e4_road::offset(float dx, float dy) {
	e4_road::x += dx;
	e4_road::y += dy;

	if(horizontal) {
		e4_road::ax = e4_road::x - e4_road::range;
		e4_road::ay = e4_road::y - ROAD_SIZE;
		e4_road::bx = e4_road::x + e4_road::range;
		e4_road::by = e4_road::y - ROAD_SIZE;

		e4_road::cx = x + e4_road::range;
		e4_road::cy = y + ROAD_SIZE;
		e4_road::dx = x - e4_road::range;
		e4_road::dy = y + ROAD_SIZE;
	} else {
		e4_road::ax = e4_road::x - ROAD_SIZE;
		e4_road::ay = e4_road::y - e4_road::range;
		e4_road::bx = e4_road::x + ROAD_SIZE;
		e4_road::by = e4_road::y - e4_road::range;

		e4_road::cx = e4_road::x + ROAD_SIZE;
		e4_road::cy = e4_road::y + e4_road::range;
		e4_road::dx = e4_road::x - ROAD_SIZE;
		e4_road::dy = e4_road::y + e4_road::range;
	}
}