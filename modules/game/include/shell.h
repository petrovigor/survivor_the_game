#ifndef __SHELL_H
#define __SHELL_H

#include <Windows.h>
#include "misc.h"

class SHELL {
private:
	bool b;
	double x,y;
	double angle;
	double size;
	double speed;
	double decreaseSpeed;
	double drawAngle;
	double angleRate;
	double cameraOffsetX;
	double cameraOffsetY;

public:
	SHELL(double, double, double, double, double, double, double);

	void process(double);
	void draw(HDC);
	void depose(double, double);
	bool is(void) {return b;}
	void setCameraOffset(double, double);

	~SHELL() {};
};

#endif