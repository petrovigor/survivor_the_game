#ifndef __MISSILE_H
#define __MISSILE_H

#include "object.h"
#include "routine.h"

class e4_missile : public e4_object {
private:
public:
	e4_missile(float x, float y, float a, float r, float s);

	void draw(HDC hdc);
	void move(float deltaTime);
};

#endif