#ifndef __GAME_OBJECT_H
#define __GAME_OBJECT_H

#include <math.h>

// abstract game object class
class GAME_OBJECT {
protected:
	bool alive;
	double x, y;
	double oldX, oldY;
	double size;
	double maxSize;
	double speed;
	double angle;
	double height;

	double cameraOffsetX, cameraOffsetY;//*

public:
	GAME_OBJECT() {
		x = y = size = maxSize = angle = speed = oldX = oldY = 0.0;
		cameraOffsetX = cameraOffsetY = 0.0;
		alive = true;
		height = 1.0;
	}

	GAME_OBJECT *itSelf(void) {return this;}

	double getX(void) {return x;}
	double getY(void) {return y;}
	void setXY(double newX, double newY) {x = newX; y = newY;}
	void setSpeed(double newSpeed) {speed = newSpeed;}//unused
	double getSpeed(void) {return speed;}//unused
	double getSize(void) {return size;}
	void setSize(double value) {size=value;}
	double getAngle(void) {return angle;}
	void setHeight(double h) {height=h;}
	void setCameraOffset(double X,double Y){cameraOffsetX=X;cameraOffsetY=Y;}

	//void hit(double damage) {
	//	hp -= damage;
	//	if(hp <= 0.0) {
	//		kill();
	//	}
	//}

	void backupXY(void) {oldX = x; oldY = y;}
	void restoreXY(void) {x = oldX; y = oldY;}

	inline double distance(GAME_OBJECT *obj) {
		//obj->setXY(0., 10.0);
		//setXY(-20., 110.0);

		double x1 = obj->getX();
		double y1 = obj->getY();
		double x2 = x;
		double y2 = y;

		double d=x2-x1;
		double d2=y2-y1;
		double result = sqrt(pow(x - obj->getX(), 2.0) + pow(y - obj->getY(), 2.0));

		//MessageBox(0, 0, 0, 0);

		return result;
	}

	inline double getAngleAt(GAME_OBJECT *obj) {
		//double result;

		//result = atan2(obj->y - y, obj->x - x);

		return(atan2(obj->y - y, obj->x - x));
		//result = atan2
	}

	//virtual void heal() = 0;

	virtual void draw(HDC hbdc) = 0;
	virtual void takeDamage(double damage) {};
	//virtual void attack(double x, double y) {};

    virtual ~GAME_OBJECT() {}; // ????????????
	//virtual void draw(HDC bhdc) = 0;
	//double setCollisionRadius(void) {return collisionRadius;}
};

#endif