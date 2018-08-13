#ifndef __ROAD_H
#define __ROAD_H

#include <windows.h>

#define ROAD_SIZE (60.0f)

enum CROSSWAY_ROAD_INDECIES {UNKNOWN = -1, A = 0, B = 1, C = 2, D = 3};

class e4_road {
private:
	float x, y;
	float ax, ay;
	float bx, by;
	float cx, cy;
	float dx, dy;
	float camX, camY;
	float range;
	bool horizontal;
	bool render;
	int roadDirection;
	bool unused;

public:
	e4_road(void);
	e4_road(float x, float y, float range, int roadDirection, bool horizontal);

	//e4_road *getSelfPointer(void);
	void offset(float dx, float dy);
	void setCameraCoordinates(float cx, float cy);
	void draw(HDC hdc);
	void checkRender(void);
	bool presumeCollisionRectangle(float x, float y, float hw, float hh);
	float getX(void);
	float getY(void);
	float getRange(void);
	int getDirection(void);

	void toDelete(void);
	bool isToDelete(void);
};

#endif