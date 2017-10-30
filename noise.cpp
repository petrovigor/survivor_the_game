#include "noise.h"

void NOISE::increaseNoiseRadius(double deltaTime) {
	radiusTemp = radiusTemp + NOISE_SPEED * deltaTime;
	if(radiusTemp > radiusMax) {
		markAsUnused();
	}
}

void NOISE::draw(HDC bhdc) {
	//SelectObject(bhdc, *ptr);
	double newX = x + cameraOffsetX;
	double newY = y + cameraOffsetY;
	Ellipse(bhdc, newX-radiusTemp, newY-radiusTemp, newX+radiusTemp, newY+radiusTemp);
}

void NOISE::depose(double X, double Y) {
	x = x + X;
	y = y + Y;
}