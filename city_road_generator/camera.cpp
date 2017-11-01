#include "camera.h"

e4_camera::e4_camera(void) {
	x = y = 0.0f;
	playerPtr = nullptr;
	physicsPtr = nullptr;
	rate = CAMERA_RATE;
}

void e4_camera::init(e4_physics *physicsPtr, e4_player *playerPtr) {
	e4_camera::physicsPtr = physicsPtr;
	e4_camera::playerPtr = playerPtr;
}

float e4_camera::getX(void) {
	return x;
}

float e4_camera::getY(void) {
	return y;
}

void e4_camera::setCameraRate(float rate) {
	e4_camera::rate = rate;
}

void e4_camera::moveCamera(float dx, float dy) {
	const float centerX = 640.0f / 2.0f;
	const float centerY = 480.0f / 2.0f;

	dx = -dx;
	dy = -dy;

	x = (centerX + dx) * rate;
	y = (centerY + dy) * rate;

	physicsPtr->setCameraCoordinates(x, y);
}