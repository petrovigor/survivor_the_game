#pragma once

#include <Windows.h>
#include <math.h>

#include <memory>

class GameObject {
protected:
	bool alive;
	double x, y;
	double oldX, oldY;
	double size;
	double maxSize;
	double speed;
	double angle;
	double height;

	double cameraOffsetX, cameraOffsetY;

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

	double getX(void) {return x;}
	double getY(void) {return y;}
	void setXY(double newX, double newY) {x = newX; y = newY;}
	void setSpeed(double newSpeed) {speed = newSpeed;}
	double getSpeed(void) {return speed;}
	double getSize(void) {return size;}
	void setSize(double value) {size=value;}
	double getAngle(void) {return angle;}
	void setHeight(double h) {height=h;}
	void setCameraOffset(double X,double Y){cameraOffsetX=X;cameraOffsetY=Y;}

	void backupXY(void) {oldX = x; oldY = y;}
	void restoreXY(void) {x = oldX; y = oldY;}

	double distance(GameObject *obj) {
		double x1 = obj->getX();
		double y1 = obj->getY();
		double x2 = x;
		double y2 = y;

		double d=x2-x1;
		double d2=y2-y1;
		double result = sqrt(pow(x - obj->getX(), 2.0) + pow(y - obj->getY(), 2.0));

		return result;
	}

	double getAngleAt(GameObject *obj) {
		return(atan2(obj->y - y, obj->x - x));
	}

  void draw(HDC hdc) {
    
  }
	
	virtual void takeDamage(double damage) {};
};
