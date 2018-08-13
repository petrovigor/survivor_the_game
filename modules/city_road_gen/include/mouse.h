#ifndef __MOUSE_H
#define __MOUSE_H

#include "object.h"

class e4_mouse {
private:
	float x, y, r;
	bool left;
	bool right;

public:
	e4_mouse(void);

	void draw(HDC hdc);
	void setPos(float x, float y);

	void setLeft(bool flag);
	bool isLeft(void);

	void setRight(bool flag);
	bool isRight(void);

	float getX(void);
	float getY(void);
};

#endif