#include "object.h"

e4_object::e4_object(void) {
	x = y = r = a = s = 0.0f;
	cx = cy = 0.0f;
	active = true;
	render = false;
}

void e4_object::checkRender(void) {
	render = (x + cx < 640.0f && x + cx > 0.0f && y + cy < 480.0f && y + cy > 0.0f);
}

bool e4_object::isToRender(void) {
	return render;
}

void e4_object::setXY(float x, float y) {
	e4_object::x = x;
	e4_object::y = y;
}

void e4_object::setRadius(float r) {
	e4_object::r = r;
}

void e4_object::setAngle(float a) {
	e4_object::a = a;
}

void e4_object::setSpeed(float s) {
	e4_object::s = s;
}

void e4_object::offset(float dx, float dy) {
	x += dx;
	y += dy;
}

float e4_object::getX(void) {
	return x;
}

float e4_object::getY(void) {
	return y;
}

float e4_object::getAngle(void) {
	return a;
}

float e4_object::getSpeed(void) {
	return s;
}

float e4_object::getRadius(void) {
	return r;
}

void e4_object::setCameraCoordinates(float cx, float cy) {
	e4_object::cx = cx;
	e4_object::cy = cy;
}

float e4_object::getCameraX(void) {
	return cx;
}

float e4_object::getCameraY(void) {
	return cy;
}

bool e4_object::isActive(void) {
	return active;
}

void e4_object::deactivate(void) {
	active = false;
}