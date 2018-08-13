#ifndef __NOISE_H
#define __NOISE_H

#include <windows.h>

const int NOISE_SPEED = 1200;//1200

class NOISE {
private:
	HPEN *ptr;
	int x, y;
	int radiusTemp;
	int radiusMax;
	bool toDelete;
	double cameraOffsetX, cameraOffsetY;//*


public:
	NOISE(int newX, int newY, int newRadius, HPEN *newPtr) {
		x = newX;
		y = newY;
		radiusMax = newRadius;
		radiusTemp = 0.0;
		toDelete = false;
		ptr = newPtr;
	}

	void increaseNoiseRadius(double);
	void draw(HDC);
	void depose(double, double);
	void setCameraOffset(double X,double Y){cameraOffsetX=X;cameraOffsetY=Y;}
	void markAsUnused(void) {toDelete = true;}
	bool isToDelete(void) {return toDelete;}
	int getX(void) {return x;}
	int getY(void) {return y;}
	int getRadius(void) {return radiusTemp;}
};

#endif