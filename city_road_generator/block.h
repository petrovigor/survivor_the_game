#ifndef __BLOCK_H
#define __BLOCK_H

#include <Windows.h>
//#include <stdio.h> //FOR DEBUG ONLY
#include "routine.h"

enum BLOCK_TYPE { BLOCK_TYPE_DEFAULT = 0,
	              BLOCK_TYPE_HOUSE = 0,
	              BLOCK_TYPE_TREE = 1 };

class e4_block {
private:
	bool unused;
	int type;
	float x, y;
	float hwidth;
	float hheight;
	float ax, ay;
	float bx, by;
	float cx, cy;
	float dx, dy;
	float camX, camY;
	float heightRate;
	bool render;

public:
	e4_block(void);
	e4_block(float x, float y, float hw, float hh, int type);

	void draw(HDC hdc, float px, float py);
	void init(float x, float y, float hw, float hh, int type);

	bool isCoordInBlock(float x, float y, float hw, float hh);
	void setCameraCoordinates(float cx, float cy);
	void offset(float dx, float dy);
	void checkRender(void);

	float getX(void);
	float getY(void);

	float getHalfWidth(void);
	float getHalfHeight(void);

	void toDelete(void);
	bool isToDelete(void);
};

#endif