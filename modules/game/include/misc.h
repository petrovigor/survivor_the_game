#pragma once

#include <math.h>
#include "defines.h"
#include "gameObject.h"

const double _PI = 3.1415926535897932384626;//4338327950288419716939937510582097494459230781640628620899;
const double ATTACK_RANGE_MELEE = 5.0,
	         ATTACK_RANGE_RANGED = 200.0;

// way searching
//double lx1, ly1, lx2, ly2; // coords of intersected block line

inline bool isIntersection(double ax1, double ay1, double ax2, double ay2, double bx1, double by1, double bx2, double by2/*,double *coords,int *count*/) {
	double v1=(bx2-bx1)*(ay1-by1)-(by2-by1)*(ax1-bx1);
	double v2=(bx2-bx1)*(ay2-by1)-(by2-by1)*(ax2-bx1);
	double v3=(ax2-ax1)*(by1-ay1)-(ay2-ay1)*(bx1-ax1);
	double v4=(ax2-ax1)*(by2-ay1)-(ay2-ay1)*(bx2-ax1);
	bool b=((v1*v2<0)&&(v3*v4<0));
	//if(b) {
	//	int c = *count;
	//	coords[c*4] = bx1;
	//	coords[c*4+1] = by1;
	//	coords[c*4+2] = bx2;
	//	coords[c*4+3] = by2;
	//	*count = *count + 1;
	//}
	return(b);
	//return((v1*v2<0)&&(v3*v4<0));
}

inline bool isMapContainsCoord(double x,double y) {
	return(x<RESOLUTION_X && y<RESOLUTION_Y && x>0 && y>0);
}

inline bool isSegmentsParallel(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	return(((x2-x1)/(y2-y1))==((x4-x3)/(y4-y3)));
}

//angle between coords in radians
inline double abc(double x1, double y1, double x2, double y2) {
	return(atan2(y2-y1, x2-x1));
}

//distance between objects
inline double dbo(GAME_OBJECT *f, GAME_OBJECT *s) {
	double x1=f->getX();
	double y1=f->getY();
	double x2=s->getX();
	double y2=s->getY();
	return sqrt(pow(x2-x1,2.0)+pow(y2-y1,2.0));
	//return(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

//distance between coords
inline double dbc(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2-x1,2.0)+pow(y2-y1,2.0));
}

//class COLOR {
//private:
//	int r, g, b;
//
//public:
//	COLOR(int R, int G, int B) {
//		r = R;
//		g = G;
//		b = B;
//	}
//};

//function Intersection(ax1,ay1,ax2,ay2,bx1,by1,bx2,by2:real):boolean;
//var v1,v2,v3,v4:real;
//begin
//   v1:=(bx2-bx1)*(ay1-by1)-(by2-by1)*(ax1-bx1);
//   v2:=(bx2-bx1)*(ay2-by1)-(by2-by1)*(ax2-bx1);
//   v3:=(ax2-ax1)*(by1-ay1)-(ay2-ay1)*(bx1-ax1);
//   v4:=(ax2-ax1)*(by2-ay1)-(ay2-ay1)*(bx2-ax1);
//   Intersection:=(v1*v2<0) and (v3*v4<0);
//end;
