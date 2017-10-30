#include "shell.h"

SHELL::SHELL(double newX, double newY, double newAngle, double newSize, double newSpeed, double newDecreaseSpeed, double newAngleRate) {
	b = true;
	x = newX;
	y = newY;
	angle = newAngle;
	size = newSize;
	speed = newSpeed;
	decreaseSpeed = newDecreaseSpeed;
	drawAngle = 0.0;
	angleRate = newAngleRate;
}

void SHELL::process(double deltaTime) {
	speed = speed - decreaseSpeed * deltaTime;

	if(speed > 0) {
		drawAngle = drawAngle + angleRate;
		x = x + speed * deltaTime * cos(angle);
		y = y + speed * deltaTime * sin(angle);
	} else {
		b = false;
	}
}

void SHELL::setCameraOffset(double offsetX, double offsetY) {
	cameraOffsetX = offsetX;
	cameraOffsetY = offsetY;
}

void SHELL::draw(HDC bhdc) {
	double newX = x + cameraOffsetX;
	double newY = y + cameraOffsetY;
	Rectangle(bhdc, newX-size, newY-size, newX+size, newY+size);
}

void SHELL::depose(double X, double Y) {
	x = x + X;
	y = y + Y;
}