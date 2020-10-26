#pragma once

#include <math.h>
#include <Windows.h>

const int FX_VISUAL_TYPE_NONE = 0,
	      FX_VISUAL_TYPE_ELLIPSE = 1,
	      FX_VISUAL_TYPE_RECTANGLE = 2;

class FX {
protected:
	bool flag;
	float x, y;
	float size;
	float speed;
	float angle;
	float duration;
	int visualType;
	float cameraOffsetX;
	float cameraOffsetY;

public:
	FX() {
		flag = false;
		x = y = size = speed = angle = duration = 0.0;
		visualType = FX_VISUAL_TYPE_NONE;
		cameraOffsetY=cameraOffsetX=0.0;
	}

	void setCameraOffset(float X,float Y) {
		cameraOffsetX = X;
		cameraOffsetY = Y;
	}

	bool getFlag(void) {return flag;}
};

class FX_FLASH : public FX {
public:
	FX_FLASH(float _x, float _y, float newPower, float _lifeTime, const int newVisualType) {
		x = _x;
		y = _y;
		size = 0.0;
		flag = false;
		speed = newPower;
		duration = _lifeTime;
		visualType = newVisualType;
	}

	void draw(HDC bhdc);

	void update(float deltaTime) {
		size += speed*deltaTime;

		duration -= deltaTime;
		if(duration <= 0.0) {
			flag = true;
		}
	}
};

class FX_BLOOD : public FX {
public:
	FX_BLOOD(float newX, float newY, float newAngle, float newRadius, float newSpeed, const int newVisualType) {
		flag = false;
		x = newX;
		y = newY;
		angle = newAngle;
		size = newRadius;
		speed = newSpeed;
		visualType = newVisualType;
	}

	void draw(HDC bhdc);

	void depose(float X,float Y) {
		x = x + X;
		y = y + Y;
	}

	void update(float deltaTime) {
		size -= 2.0 * deltaTime;
		speed -= (speed*2) * deltaTime;
		if(speed < 0) speed=0;

		if(size <= 0.0) {
			flag = true;
		} else {
				x += speed*deltaTime * cos(angle);
				y += speed*deltaTime * sin(angle);
		}
	}
};
