#include "block.h"
#include <math.h>
#include <Windows.h>


//x/y 0,0 is left-top corner
//x/y max,0 is right-top corner
Block::Block(float32 newX, float32 newY, float32 newW, float32 newH) {
	//float _x,_y;
	//_x=newX+newW/2*cos(_PI);
	//_y=newY+newW/2*sin(_PI);
	//bx[0]=_x+newH/2*cos(_PI/2);
	//by[0]=_y+newH/2*sin(_PI/2);
	//bx[3]=_x+newH/2*cos(_PI*3/2);
	//by[3]=_y+newH/2*sin(_PI*3/2);
	//_x=newX+newW/2*cos(0.00);
	//_y=newY+newW/2*sin(0.00);
	//bx[1]=_x+newH/2*cos(_PI/2);
	//by[1]=_y+newH/2*sin(_PI/2);
	//bx[2]=_x+newH/2*cos(_PI*3/2);
	//by[2]=_y+newH/2*sin(_PI*3/2);

	p.p.x=newX;
	p.p.y=newY;
	width=newW;
	height=newH;
}

void Block::draw(HDC bhdc, const worldPoint &playerPos, float32 cox, float32 coy)
{
	//const float32 worldCenterOffsetWidth = 800 / 2;
	//const float32 worldCenterOffsetHeight = 600 / 2;
	//float32 nx = p.p.x + cameraOffsetX + worldCenterOffsetWidth;
	//float32 ny = p.p.y + cameraOffsetY + worldCenterOffsetHeight;



	const float32 x = (p.p.x - playerPos.p.x + cox);
	const float32 y = (p.p.y - playerPos.p.y + coy);



	MoveToEx(bhdc, x, y, 0);
	LineTo(bhdc, x + width, y);
	LineTo(bhdc, x + width, y + height);
	LineTo(bhdc, x, y + height);
	LineTo(bhdc, x, y);

	//for(int i=0; i<4; i++) {
	//	MoveToEx(bhdc, bx[i] + cameraOffsetX, by[i] + cameraOffsetY, 0);

	//	int j=i+1;
	//	if(j>3) j=0;

	//	LineTo(bhdc, bx[j] + cameraOffsetX, by[j] + cameraOffsetY);
	//}
}

//void Block::depose(float X, float Y) {
//	//for(int i=0;i<4;i++) {
//	//	bx[i]=bx[i]+X;
//	//	by[i]=by[i]+Y;
//	//}
//	x=x+X;
//	y=y+Y;
//}
