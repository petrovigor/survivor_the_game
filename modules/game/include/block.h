#pragma once

//#include <windows.h>
//#include <math.h>
//#include <list>
//#include "enemy.h"
//#include "defines.h"
//#include "misc.h"

#include "game_object.h"

class Block final : public GameObject {
private:
  float w, h;
	float bx[4], by[4];

public:
	Block(float newX, float newY, float newW, float newH);

  void draw(HDC bhdc) override;
	void depose(float x, float y) override;

	//void deposeByCenter(float X, float Y) {
	//	float cx = RESOLUTION_X/2;
	//	float cy = RESOLUTION_Y/2;

	//	for(int i=0;i<4;i++) {
	//		bx[i]=cx+X;
	//		by[i]=cy+Y;
	//	}
	//	x=cx+X;
	//	y=cy+Y;
	//}

	//bool isCoordInBlock(float x, float y, float r);
	//bool isGOinBlock(GameObject *go);

	//bool checkForIntersection(float aX,float aY,float bX,float bY) {
	//	for(int i=0; i<4; i++) {
	//		int j=i+1;
	//		if(j>3) j=0;
	//		if(isIntersection(aX,aY,bX,bY,bx[i],by[i],bx[j],by[j])) {
	//			return(true);
	//		}
	//	}
	//	return(false);
	//}

	//int checkForIntersection(float aX,float aY,float bX,float bY,float *coords,int *count) {
	//	int intersected = -1;

	//	for(int i=0; i<4; i++) {
	//		int j=i+1;
	//		if(j>3) j=0;

	//		if(isIntersection(aX,aY,bX,bY,bx[i],by[i],bx[j],by[j])) {

	//			if(*count*4+3 < DEBUGVAR_INTERSECTS_COUNT_MAX) {

	//				coords[(*count)*4      ] = bx[i];
	//				coords[(*count)*4   +1 ] = by[i];
	//				coords[(*count)*4   +2 ] = bx[j];
	//				coords[(*count)*4   +3 ] = by[j];
	//				*count=*count+1;

	//				intersected = i;

	//			}
	//		}
	//	}

	//	return intersected;
	//}

	//void computeShadows(HDC bhdc, float X, float Y) {
	//	if(DEBUGVAR_SHOW_SHADOWS) {
	//		float nx[4], ny[4];
	//		for(int i=0; i<4; i++) {
	//			float a = abc(X, Y, bx[i], by[i]);
	//			float d = dbc(X, Y, bx[i], by[i])*height;
	//			nx[i] = bx[i] + d * cos(a);
	//			ny[i] = by[i] + d * sin(a);
	//		}

	//		for(int i=0; i<4; i++) {
	//			float a = abc(X, Y, bx[i], by[i]);
	//			float d = dbc(X, Y, bx[i], by[i])*height;

	//			MoveToEx(bhdc, bx[i]+cameraOffsetX, by[i]+cameraOffsetY, 0);
	//			LineTo(bhdc, bx[i] + d * cos(a)+cameraOffsetX, by[i] + d * sin(a)+cameraOffsetY);

	//			if(DEBUGVAR_ALPHA_ROOFS) {
	//				MoveToEx(bhdc, nx[i]+cameraOffsetX, ny[i]+cameraOffsetY, 0);

	//				int j=i+1;
	//				if(j>3) j=0;

	//				LineTo(bhdc, nx[j]+cameraOffsetX, ny[j]+cameraOffsetY);
	//			}
	//		}

	//		if(!DEBUGVAR_ALPHA_ROOFS) {

	//			HBRUSH b = CreateSolidBrush(RGB(255,255,255));

	//			SelectObject(bhdc, b);
	//			Rectangle(bhdc, nx[0]+cameraOffsetX, ny[0]+cameraOffsetY, nx[2]+cameraOffsetX, ny[2]+cameraOffsetY);

	//			DeleteObject(b);
	//			b = 0;

	//		}
	//	}
	//}
};
