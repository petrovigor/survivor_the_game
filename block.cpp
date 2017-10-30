#include "block.h"

bool BLOCK::checkForVisibility() {
	int k=0,j;
	for(int i=0; i<4; i++) {
		vis[i]=false;
		j=i+1;
		if(j>3) j=0;
		if(isMapContainsCoord(bx[i],by[i])||isMapContainsCoord(bx[j],by[j])) {
			vis[i]=true;
			k++;
		}
	}
	if(k!=0) return true;
	return false;
}

void BLOCK::draw(HDC bhdc) {
	if(checkForVisibility()) {
		//SelectObject(bhdc, *penPtr);
		for(int i=0; i<4; i++) {
			int j=i+1;
			if(j>3) j=0;
			if(vis[i]) {
				MoveToEx(bhdc, bx[i]+cameraOffsetX, by[i]+cameraOffsetY, 0);
				LineTo(bhdc, bx[j]+cameraOffsetX, by[j]+cameraOffsetY);
			}
		}
	}
}

void BLOCK::offset(std::list<ENEMY>::iterator it) {
	double X=it->getX();
	double Y=it->getY();
	double S=it->getSize();

	if( X+S > x-w/2 && X-S > x+w/2 && Y+S > y-h/2 && Y-S > y+h/2 ) {
		//X = x-w/2-S;
		//Y = y-h/2-S;
		
		//if( X+S > x-w/2 ) {
		//	X = x-w/2-S;
		//}
		//if( X-S > x+w/2 ) {
		//	X = x+w/2+S;
		//}
		//if( Y+S > y-h/2 ) {
		//	Y = y-h/2-S;
		//}
		//if( Y-S > y+h/2 ) {
		//	Y = y+h/2+S;
		//}
	}


	//if( X > x-w/2 ) {
	//	X = x-w/2;
	//}

	//if(X+s > x-w/2) {
	//	X = x-w/2-s;
	//}

	it->setXY(X,Y);
}

bool BLOCK::isGOinBlock(GAME_OBJECT *go) {
	// check for 8 points of circle?
	double X = go->getX();
	double Y = go->getY();

	return X-go->getSize()<x+w/2 && Y-go->getSize()<y+h/2 && X+go->getSize()>x-w/2 && Y+go->getSize()>y-h/2;

	//return false;
}

bool BLOCK::rectCollision(double X, double Y, double W, double H) {
	return X-W<x+w/2 && Y-H<y+h/2 && X+W>x-w/2 && Y+H>y-h/2;
}

bool BLOCK::isCoordInBlock(double X, double Y, double R) {
	return X-R<x+w/2
		&& Y-R<y+h/2
		&& X+R>x-w/2
		&& Y+R>y-h/2;
}

//void BLOCK::draw(HDC bhdc) {
//	SelectObject(bhdc, *penPtr);
//	//double xx[4],yy[4];
//
//	//xx[0]=x1; yy[0]=y1; xx[1]=x2; yy[1]=y2;
//	//xx[2]=x3; yy[2]=y3; xx[3]=x4; yy[3]=y4;
//
//	//double _x, _y;
//
//	//_x = x + ((w/2)*height) * cos(_PI);
//	//_y = y + ((w/2)*height) * sin(_PI);
//	//xx[0] = _x + ((h/2)*height) * cos(_PI/2);
//	//yy[0] = _y + ((h/2)*height) * sin(_PI/2);
//	//xx[3] = _x + ((h/2)*height) * cos(_PI*3/2);
//	//yy[3] = _y + ((h/2)*height) * sin(_PI*3/2);
//	//_x = x + ((w/2)*height) * cos(0.0);
//	//_y = y + ((w/2)*height) * sin(0.0);
//	//xx[1] = _x + ((h/2)*height) * cos(_PI/2);
//	//yy[1] = _y + ((h/2)*height) * sin(_PI/2);
//	//xx[2] = _x + ((h/2)*height) * cos(_PI*3/2);
//	//yy[2] = _y + ((h/2)*height) * sin(_PI*3/2);
//
//	for(int i=0; i<4; i++) {
//		MoveToEx(bhdc, bx[i], by[i], 0);
//
//		int j=i+1;
//		if(j>3) j=0;
//
//		LineTo(bhdc, bx[j], by[j]);
//	}
//}