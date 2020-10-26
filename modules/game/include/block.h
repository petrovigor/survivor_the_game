#pragma once

#include <windows.h>
#include <math.h>
#include <list>
#include "enemy.h"
#include "defines.h"
//#include "gameObject.h"
#include "misc.h"

class BLOCK {
private:
	bool toDeleteVar;
	bool vis[4];
	double height;
	double x,y,w,h;
	double bx[4],by[4];

	//bool flag;
	HPEN *penPtr;
	//double height;
	double cameraOffsetX, cameraOffsetY;//*

public:
	BLOCK(double newX, double newY, double newW, double newH, HPEN *newPenPtr) {
		toDeleteVar=false;

		height = (rand()%75+25)/100.0;

		penPtr=newPenPtr;
		double _x,_y;
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
	void setCameraOffset(double X,double Y){cameraOffsetX=X;cameraOffsetY=Y;}
	bool rectCollision(double,double,double,double);

	void offset(std::list<ENEMY>::iterator it);

	void depose(double X, double Y) {
		for(int i=0;i<4;i++) {
			bx[i]=bx[i]+X;
			by[i]=by[i]+Y;
		}
		x=x+X;
		y=y+Y;
	}

	void deposeByCenter(double X, double Y) {
		double cx = RESOLUTION_X/2;
		double cy = RESOLUTION_Y/2;

		for(int i=0;i<4;i++) {
			bx[i]=cx+X  ;//bx[i]+X;
			by[i]=cy+Y  ;//by[i]+Y;
		}
		x=cx+X;  //x+X;
		y=cy+Y; //y+Y;
	}

	bool isCoordInBlock(double x, double y, double r);
	bool isGOinBlock(GameObject *go);
	void draw(HDC bhdc);

	bool checkForIntersection(double aX,double aY,double bX,double bY) {
		for(int i=0; i<4; i++) {
			int j=i+1;
			if(j>3) j=0;
			if(isIntersection(aX,aY,bX,bY,bx[i],by[i],bx[j],by[j])) {
				return(true);
			}
		}
		return(false);
	}

	/*inline */int checkForIntersection(double aX,double aY,double bX,double bY,double *coords,int *count) {
		int intersected = -1;

		for(int i=0; i<4; i++) {
			int j=i+1;
			if(j>3) j=0;

			if(isIntersection(aX,aY,bX,bY,bx[i],by[i],bx[j],by[j]/*,coords,count)*/)) {

				if(*count*4+3 < DEBUGVAR_INTERSECTS_COUNT_MAX) {

					coords[(*count)*4      ] = bx[i];
					coords[(*count)*4   +1 ] = by[i]; // fatal error here
					coords[(*count)*4   +2 ] = bx[j];
					coords[(*count)*4   +3 ] = by[j];
					*count=*count+1;

					intersected = i;

				}
				//return i;
			}
		}

		return intersected;
	}

	void setHeight(double h) {height = h;}

	//draw dynamic shadows
	void computeShadows(HDC bhdc, double X, double Y) {
		if(DEBUGVAR_SHOW_SHADOWS) {
			double nx[4], ny[4];
			//const double distFactor = 1.0;
			
			for(int i=0; i<4; i++) {
				double a = abc(X, Y, bx[i], by[i]);
				double d = dbc(X, Y, bx[i], by[i])*height/*distFactor*/;
				nx[i] = bx[i] + d * cos(a);
				ny[i] = by[i] + d * sin(a);
			}

			for(int i=0; i<4; i++) {
				double a = abc(X, Y, bx[i], by[i]);
				double d = dbc(X, Y, bx[i], by[i])*height/*distFactor*/;

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

	double getX(void) {return x;}
	double getY(void) {return y;}
};
