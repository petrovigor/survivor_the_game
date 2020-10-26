#pragma once

#include <Windows.h>
#include <math.h>

#include <memory>

class GameObject {
protected:
	bool alive;
	float x, y;
	float oldX, oldY;
	float size;
	float maxSize;
	float speed;
	float angle;
	float height;

	float cameraOffsetX, cameraOffsetY;

public:
	GameObject() {
		x = y = size = maxSize = angle = speed = oldX = oldY = 0.0;
		cameraOffsetX = cameraOffsetY = 0.0;
		alive = true;
		height = 1.0;
	}
  virtual ~GameObject() {};

  GameObject(int _x, int _y, int _size, int _speed, int _angle)
    : x(_x)
    , y(_y)
    , size(_size)
    , speed(_speed)
    , angle(_angle)
  { }

	GameObject *itSelf(void) {return this;}

	float getX(void) {return x;}
	float getY(void) {return y;}
	void setXY(float newX, float newY) {x = newX; y = newY;}
	void setSpeed(float newSpeed) {speed = newSpeed;}
	float getSpeed(void) {return speed;}
	float getSize(void) {return size;}
	void setSize(float value) {size=value;}
	float getAngle(void) {return angle;}
	void setHeight(float h) {height=h;}
	void setCameraOffset(float X,float Y){cameraOffsetX=X;cameraOffsetY=Y;}

	void backupXY(void) {oldX = x; oldY = y;}
	void restoreXY(void) {x = oldX; y = oldY;}

	float distance(GameObject *obj) {
		float x1 = obj->getX();
		float y1 = obj->getY();
		float x2 = x;
		float y2 = y;

		float d=x2-x1;
		float d2=y2-y1;
		float result = sqrt(pow(x - obj->getX(), 2.0) + pow(y - obj->getY(), 2.0));

		return result;
	}

	float getAngleAt(GameObject *obj) {
		return(atan2(obj->y - y, obj->x - x));
	}

  void draw(HDC hdc) {
    
  }
	
	virtual void takeDamage(float damage) {};
};
