#pragma once

#include <Windows.h>

class ROAD {
private:
	double ax,ay;
	double bx,by;
	double cx,cy;
	double dx,dy;
	HPEN *penPtr;

public:
	ROAD(double AX,double AY,double BX,double BY,double CX,double CY,double DX,double DY,HPEN *p) {
		ax = AX;
		ay = AY;
		bx = BX;
		by = BY;
		cx = CX;
		cy = CY;
		dx = DX;
		dy = DY;
		penPtr = p;
	}

	void depose(double x, double y) {
		ax = ax + x;
		ay = ay + y;
		bx = bx + x;
		by = by + y;
		cx = cx + x;
		cy = cy + y;
		dx = dx + x;
		dy = dy + y;
	}

	void draw(HDC bhdc);
};
