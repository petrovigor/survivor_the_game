#pragma once

#include "defines.h"
#include "game_object.h"

class CURSOR : public GameObject {
public:
	CURSOR() {
		size = CURSOR_SIZE;
	}

	void move(double newX, double newY) {x = newX; y = newY;}
	void draw(HDC bhdc);
};
