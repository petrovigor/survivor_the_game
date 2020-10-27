//#include "shell.h"
//
//SHELL::SHELL(float newX, float newY, float newAngle, float newSize, float newSpeed, float newDecreaseSpeed, float newAngleRate) {
//	b = true;
//	x = newX;
//	y = newY;
//	angle = newAngle;
//	size = newSize;
//	speed = newSpeed;
//	decreaseSpeed = newDecreaseSpeed;
//	drawAngle = 0.0;
//	angleRate = newAngleRate;
//}
//
//void SHELL::process(float deltaTime) {
//	speed = speed - decreaseSpeed * deltaTime;
//
//	if(speed > 0) {
//		drawAngle = drawAngle + angleRate;
//		x = x + speed * deltaTime * cos(angle);
//		y = y + speed * deltaTime * sin(angle);
//	} else {
//		b = false;
//	}
//}
//
//void SHELL::setCameraOffset(float offsetX, float offsetY) {
//	cameraOffsetX = offsetX;
//	cameraOffsetY = offsetY;
//}
//
//void SHELL::draw(HDC bhdc) {
//	float newX = x + cameraOffsetX;
//	float newY = y + cameraOffsetY;
//	Rectangle(bhdc, newX-size, newY-size, newX+size, newY+size);
//}
//
//void SHELL::depose(float X, float Y) {
//	x = x + X;
//	y = y + Y;
//}