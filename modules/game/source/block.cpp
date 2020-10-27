#include "block.h"
#include <math.h>

static const float _PI = 3.14f;

Block::Block(float newX, float newY, float newW, float newH) {

	

	float _x,_y;
	//vis[0]=vis[1]=vis[2]=vis[3]=true;

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


//
//bool Block::checkForVisibility() {
//	int k=0,j;
//	for(int i=0; i<4; i++) {
//		vis[i]=false;
//		j=i+1;
//		if(j>3) j=0;
//		if(isMapContainsCoord(bx[i],by[i])||isMapContainsCoord(bx[j],by[j])) {
//			vis[i]=true;
//			k++;
//		}
//	}
//	if(k!=0) return true;
//	return false;
//}
//
//void Block::draw(HDC bhdc) {
//	if(checkForVisibility()) {
//		//SelectObject(bhdc, *penPtr);
//		for(int i=0; i<4; i++) {
//			int j=i+1;
//			if(j>3) j=0;
//			if(vis[i]) {
//				MoveToEx(bhdc, bx[i]+cameraOffsetX, by[i]+cameraOffsetY, 0);
//				LineTo(bhdc, bx[j]+cameraOffsetX, by[j]+cameraOffsetY);
//			}
//		}
//	}
//}
//
//void Block::offset(std::list<ENEMY>::iterator it) {
//	float X=it->getX();
//	float Y=it->getY();
//	float S=it->getSize();
//
//	if( X+S > x-w/2 && X-S > x+w/2 && Y+S > y-h/2 && Y-S > y+h/2 ) {
//		//X = x-w/2-S;
//		//Y = y-h/2-S;
//		
//		//if( X+S > x-w/2 ) {
//		//	X = x-w/2-S;
//		//}
//		//if( X-S > x+w/2 ) {
//		//	X = x+w/2+S;
//		//}
//		//if( Y+S > y-h/2 ) {
//		//	Y = y-h/2-S;
//		//}
//		//if( Y-S > y+h/2 ) {
//		//	Y = y+h/2+S;
//		//}
//	}
//
//
//	//if( X > x-w/2 ) {
//	//	X = x-w/2;
//	//}
//
//	//if(X+s > x-w/2) {
//	//	X = x-w/2-s;
//	//}
//
//	it->setXY(X,Y);
//}
//
//bool Block::isGOinBlock(GameObject *go) {
//	// check for 8 points of circle?
//	float X = go->getX();
//	float Y = go->getY();
//
//	return X-go->getSize()<x+w/2 && Y-go->getSize()<y+h/2 && X+go->getSize()>x-w/2 && Y+go->getSize()>y-h/2;
//
//	//return false;
//}
//
//bool Block::rectCollision(float X, float Y, float W, float H) {
//	return X-W<x+w/2 && Y-H<y+h/2 && X+W>x-w/2 && Y+H>y-h/2;
//}
//
//bool Block::isCoordInBlock(float X, float Y, float R) {
//	return X-R<x+w/2
//		&& Y-R<y+h/2
//		&& X+R>x-w/2
//		&& Y+R>y-h/2;
//}
//
////void Block::draw(HDC bhdc) {
////	SelectObject(bhdc, *penPtr);
////	//float xx[4],yy[4];
////
////	//xx[0]=x1; yy[0]=y1; xx[1]=x2; yy[1]=y2;
////	//xx[2]=x3; yy[2]=y3; xx[3]=x4; yy[3]=y4;
////
////	//float _x, _y;
////
////	//_x = x + ((w/2)*height) * cos(_PI);
////	//_y = y + ((w/2)*height) * sin(_PI);
////	//xx[0] = _x + ((h/2)*height) * cos(_PI/2);
////	//yy[0] = _y + ((h/2)*height) * sin(_PI/2);
////	//xx[3] = _x + ((h/2)*height) * cos(_PI*3/2);
////	//yy[3] = _y + ((h/2)*height) * sin(_PI*3/2);
////	//_x = x + ((w/2)*height) * cos(0.0);
////	//_y = y + ((w/2)*height) * sin(0.0);
////	//xx[1] = _x + ((h/2)*height) * cos(_PI/2);
////	//yy[1] = _y + ((h/2)*height) * sin(_PI/2);
////	//xx[2] = _x + ((h/2)*height) * cos(_PI*3/2);
////	//yy[2] = _y + ((h/2)*height) * sin(_PI*3/2);
////
////	for(int i=0; i<4; i++) {
////		MoveToEx(bhdc, bx[i], by[i], 0);
////
////		int j=i+1;
////		if(j>3) j=0;
////
////		LineTo(bhdc, bx[j], by[j]);
////	}
////}