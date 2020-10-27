//#include "noise.h"
//
//void NOISE::increaseNoiseRadius(float deltaTime) {
//	radiusTemp = radiusTemp + NOISE_SPEED * deltaTime;
//	if(radiusTemp > radiusMax) {
//		markAsUnused();
//	}
//}
//
//void NOISE::draw(HDC bhdc) {
//	//SelectObject(bhdc, *ptr);
//	float newX = x + cameraOffsetX;
//	float newY = y + cameraOffsetY;
//	Ellipse(bhdc, newX-radiusTemp, newY-radiusTemp, newX+radiusTemp, newY+radiusTemp);
//}
//
//void NOISE::depose(float X, float Y) {
//	x = x + X;
//	y = y + Y;
//}