#pragma once

#include <windows.h>
#include <math.h>
#include <list>
#include "enemy.h"
#include "defines.h"
#include "misc.h"

class BLOCK {
private:
	bool toDeleteVar;
	bool vis[4];
	float height;
	float x,y,w,h;
	float bx[4],by[4];

	HPEN *penPtr;
	float cameraOffsetX, cameraOffsetY;

public:
	BLOCK(float newX, float newY, float newW, float newH, HPEN *newPenPtr) {
		toDeleteVar=false;

		height = (rand()%75+25)/100.0;

		penPtr=newPenPtr;
		float _x,_y;
		vis[0]=vis[1]=vis[2]=vis[3]=true;

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

		cameraOffsetX=cameraOffsetY=0.0;
	}

	void toDelete(void) {toDeleteVar=true;}
	bool isToDelete(void) {return toDeleteVar;}

	bool checkForVisibility(void);
	void setCameraOffset(float X,float Y){cameraOffsetX=X;cameraOffsetY=Y;}
	bool rectCollision(float,float,float,float);

	void offset(std::list<ENEMY>::iterator it);

	void depose(float X, float Y) {
		for(int i=0;i<4;i++) {
			bx[i]=bx[i]+X;
			by[i]=by[i]+Y;
		}
		x=x+X;
		y=y+Y;
	}

	void deposeByCenter(float X, float Y) {
		float cx = RESOLUTION_X/2;
		float cy = RESOLUTION_Y/2;

		for(int i=0;i<4;i++) {
			bx[i]=cx+X;
			by[i]=cy+Y;
		}
		x=cx+X;
		y=cy+Y;
	}

	bool isCoordInBlock(float x, float y, float r);
	bool isGOinBlock(GameObject *go);
	void draw(HDC bhdc);

	bool checkForIntersection(float aX,float aY,float bX,float bY) {
		for(int i=0; i<4; i++) {
			int j=i+1;
			if(j>3) j=0;
			if(isIntersection(aX,aY,bX,bY,bx[i],by[i],bx[j],by[j])) {
				return(true);
			}
		}
		return(false);
	}

	int checkForIntersection(float aX,float aY,float bX,float bY,float *coords,int *count) {
		int intersected = -1;

		for(int i=0; i<4; i++) {
			int j=i+1;
			if(j>3) j=0;

			if(isIntersection(aX,aY,bX,bY,bx[i],by[i],bx[j],by[j])) {

				if(*count*4+3 < DEBUGVAR_INTERSECTS_COUNT_MAX) {

					coords[(*count)*4      ] = bx[i];
					coords[(*count)*4   +1 ] = by[i];
					coords[(*count)*4   +2 ] = bx[j];
					coords[(*count)*4   +3 ] = by[j];
					*count=*count+1;

					intersected = i;

				}
			}
		}

		return intersected;
	}

	void setHeight(float h) {height = h;}

	void computeShadows(HDC bhdc, float X, float Y) {
		if(DEBUGVAR_SHOW_SHADOWS) {
			float nx[4], ny[4];
			for(int i=0; i<4; i++) {
				float a = abc(X, Y, bx[i], by[i]);
				float d = dbc(X, Y, bx[i], by[i])*height;
				nx[i] = bx[i] + d * cos(a);
				ny[i] = by[i] + d * sin(a);
			}

			for(int i=0; i<4; i++) {
				float a = abc(X, Y, bx[i], by[i]);
				float d = dbc(X, Y, bx[i], by[i])*height;

				MoveToEx(bhdc, bx[i]+cameraOffsetX, by[i]+cameraOffsetY, 0);
				LineTo(bhdc, bx[i] + d * cos(a)+cameraOffsetX, by[i] + d * sin(a)+cameraOffsetY);

				if(DEBUGVAR_ALPHA_ROOFS) {
					MoveToEx(bhdc, nx[i]+cameraOffsetX, ny[i]+cameraOffsetY, 0);

					int j=i+1;
					if(j>3) j=0;

					LineTo(bhdc, nx[j]+cameraOffsetX, ny[j]+cameraOffsetY);
				}
			}

			if(!DEBUGVAR_ALPHA_ROOFS) {

				HBRUSH b = CreateSolidBrush(RGB(255,255,255));

				SelectObject(bhdc, b);
				Rectangle(bhdc, nx[0]+cameraOffsetX, ny[0]+cameraOffsetY, nx[2]+cameraOffsetX, ny[2]+cameraOffsetY);

				DeleteObject(b);
				b = 0;

			}
		}
	}

	float getX(void) {return x;}
	float getY(void) {return y;}
};
