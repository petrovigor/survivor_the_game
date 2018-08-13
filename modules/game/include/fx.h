#ifndef __FX_H
#define __FX_H

#include <math.h>

const int FX_VISUAL_TYPE_NONE = 0,
	      FX_VISUAL_TYPE_ELLIPSE = 1,
	      FX_VISUAL_TYPE_RECTANGLE = 2;

class FX {
protected:
	bool flag;//true=dead
	double x, y;
	double size;
	double speed;
	double angle;
	double duration;
	int visualType;
	double cameraOffsetX;
	double cameraOffsetY;

public:
	FX() {
		flag = false;
		x = y = size = speed = angle = duration = 0.0;
		visualType = FX_VISUAL_TYPE_NONE;
		cameraOffsetY=cameraOffsetX=0.0;
	}

	void setCameraOffset(double X,double Y) {
		cameraOffsetX = X;
		cameraOffsetY = Y;
	}

	bool getFlag(void) {return flag;}

	//void draw(HDC bhdc);
	//void update(double deltaTime);
};

class FX_FLASH : public FX {
public:
	FX_FLASH(double _x, double _y, double newPower, double _lifeTime, const int newVisualType) {
		x = _x;
		y = _y;
		size = 0.0;
		flag = false;
		speed = newPower;
		duration = _lifeTime;
		visualType = newVisualType;
	}

	void draw(HDC bhdc);

	void update(double deltaTime) {
		size += speed*deltaTime;

		duration -= deltaTime;
		if(duration <= 0.0) {
			flag = true;
		}
	}
};

class FX_BLOOD : public FX {
//private:
	//PHYSICS_MANAGER *ptr;

public:
	FX_BLOOD(double newX, double newY, double newAngle, double newRadius, double newSpeed, const int newVisualType/*, PHYSICS_MANAGER *phyPtr*/) {// double _lifeTime, const int newVisualType) {
		flag = false;
		x = newX;
		y = newY;
		angle = newAngle;
		size = newRadius;
		speed = newSpeed;
		visualType = newVisualType;
		//ptr=phyPtr;
	}

	void draw(HDC bhdc);

	void depose(double X,double Y) {
		x = x + X;
		y = y + Y;
	}

	void update(double deltaTime) {
		size -= 2.0 * deltaTime;
		speed -= (speed*2) * deltaTime;
		if(speed < 0) speed=0;

		if(size <= 0.0) {
			flag = true;
		} else {
			//if(ptr->checkForPlacementCollision(x,y,size/2,size/2)) {
				x += speed*deltaTime * cos(angle);
				y += speed*deltaTime * sin(angle);
			//}
		}
	}
};

//class FX_SEGMENTS : public FX {
//public:
//	FX_SEGMENTS(double newX, double newY, double newAngle, double newRadius, double newSpeed, const int newVisualType) {// double _lifeTime, const int newVisualType) {
//		flag = false;
//		x = newX;
//		y = newY;
//		angle = newAngle;
//		size = newRadius;
//		speed = newSpeed;
//		visualType = newVisualType;
//	}
//
//	//void draw(HDC bhdc);
//
//	void update(double deltaTime) {
//		speed-=(speed/10)*deltaTime;
//		if(speed<=1.0) {
//			flag = true;
//		} else {
//			x += speed*deltaTime * cos(angle);
//			y += speed*deltaTime * sin(angle);
//		}
//	}
//};

#endif