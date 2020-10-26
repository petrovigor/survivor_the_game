#pragma once

#include <Windows.h>
#include "misc.h"

class SHELL {
private:
	bool b;
	float x,y;
	float angle;
	float size;
	float speed;
	float decreaseSpeed;
	float drawAngle;
	float angleRate;
	float cameraOffsetX;
	float cameraOffsetY;

public:
	SHELL(float, float, float, float, float, float, float);

	void process(float);
	void draw(HDC);
	void depose(float, float);
	bool is(void) {return b;}
	void setCameraOffset(float, float);

	~SHELL() {};
};
