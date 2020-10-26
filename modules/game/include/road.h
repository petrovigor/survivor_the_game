#pragma once

#include <Windows.h>

class ROAD {
private:
	float ax,ay;
	float bx,by;
	float cx,cy;
	float dx,dy;
	HPEN *penPtr;

public:
	ROAD(float AX,float AY,float BX,float BY,float CX,float CY,float DX,float DY,HPEN *p) {
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

	void depose(float x, float y) {
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
