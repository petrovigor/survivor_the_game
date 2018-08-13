#include "mouse.h"

e4_mouse::e4_mouse(void) {
	left = false;
	x = y = 0.0f;
	r = 4.0f;
}

void e4_mouse::setPos(float x, float y) {
	e4_mouse::x = x;
	e4_mouse::y = y;
}

float e4_mouse::getX(void) {
	return x;
}

float e4_mouse::getY(void) {
	return y;
}

void e4_mouse::draw(HDC hdc) {
	if(left) {
		Rectangle(hdc, x - r, y - r, x + r, y + r);
	} else {
		Ellipse(hdc, x - r, y - r, x + r, y + r);
	}
}

void e4_mouse::setLeft(bool flag) {
	left = flag;
}

bool e4_mouse::isLeft(void) {
	return left;
}

void e4_mouse::setRight(bool flag) {
	right = flag;
}

bool e4_mouse::isRight(void) {
	return right;
}