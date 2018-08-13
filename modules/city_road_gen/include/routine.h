#ifndef __ROUTINE_H
#define __ROUTINE_H

#include <math.h>

#ifndef FRIEND
#define FRIEND friend
#endif

#ifndef WRN
#define WRN
#endif

#ifndef DBG
#define DBG
#endif

#define AngleBetweenCoords(x1, y1, x2, y2) atan2(y2 - y1, x2 - x1)

inline float DistanceBetweenCoords(float x1, float y1, float x2, float y2) {
	return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

//temporary crossway data structure
struct e4_crossway_data {
	float x, y;
	int sourceDir;

	e4_crossway_data(float x, float y, int src) {
		e4_crossway_data::sourceDir = src;
		e4_crossway_data::x = x;
		e4_crossway_data::y = y;
	}
};

#endif