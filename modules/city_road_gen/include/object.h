#ifndef __OBJECT_H
#define __OBJECT_H

#include <Windows.h>

//abstract game object class
class e4_object {
protected:
	float x, y, r, a, s;
	float cx, cy; //camera coordinates
	bool active;
	bool render;

public:
	e4_object(void);

	virtual void draw(HDC hdc) = 0;
	virtual void move(float timeDelta) = 0;
	
	void offset(float dx, float dy);
	void setXY(float x, float y);

	void setRadius(float r);
	void setAngle(float a);
	void setSpeed(float s);

	float getX(void);
	float getY(void);
	float getAngle(void);
	float getSpeed(void);
	float getRadius(void);

	void setCameraCoordinates(float cx, float cy);
	float getCameraX(void);
	float getCameraY(void);

	void deactivate(void);
	bool isActive(void);

	void checkRender(void);
	bool isToRender(void);
};

#endif