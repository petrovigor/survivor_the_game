#include "block.h"
#include <math.h>

static const float _PI = 3.14f;

Block::Block(float newX, float newY, float newW, float newH) {
	float _x,_y;
	_x=newX+newW/2*cos(_PI);
	_y=newY+newW/2*sin(_PI);
	bx[0]=_x+newH/2*cos(_PI/2);
	by[0]=_y+newH/2*sin(_PI/2);
	bx[3]=_x+newH/2*cos(_PI*3/2);
	by[3]=_y+newH/2*sin(_PI*3/2);
	_x=newX+newW/2*cos(0.00);
	_y=newY+newW/2*sin(0.00);
	bx[1]=_x+newH/2*cos(_PI/2);
	by[1]=_y+newH/2*sin(_PI/2);
	bx[2]=_x+newH/2*cos(_PI*3/2);
	by[2]=_y+newH/2*sin(_PI*3/2);

	x=newX;
	y=newY;
	w=newW;
	h=newH;
}

void Block::draw(HDC bhdc) {
	for(int i=0; i<4; i++) {
		MoveToEx(bhdc, bx[i] + cameraOffsetX, by[i] + cameraOffsetY, 0);

		int j=i+1;
		if(j>3) j=0;

		LineTo(bhdc, bx[j] + cameraOffsetX, by[j] + cameraOffsetY);
	}
}

void Block::depose(float X, float Y) {
	for(int i=0;i<4;i++) {
		bx[i]=bx[i]+X;
		by[i]=by[i]+Y;
	}
	x=x+X;
	y=y+Y;
}
