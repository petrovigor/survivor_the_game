#ifndef __CURSOR_H
#define __CURSOR_H

#include "defines.h"
#include "gameObject.h"

class CURSOR : public GAME_OBJECT {
public:
	CURSOR() {
		size = CURSOR_SIZE;
	}

	void move(double newX, double newY) {x = newX; y = newY;}
	void draw(HDC bhdc);
};

#endif