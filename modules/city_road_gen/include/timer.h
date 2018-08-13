#ifndef __TIMER_H
#define __TIMER_H

#include <windows.h>

class e4_timer {
	LARGE_INTEGER startTime;
	float current;
	float last;
	float frequency;
	float tickLength;

public:
	e4_timer(void);

	bool init(void);
	void update(void);
	float get(void);
	float getDelta(void);
};

#endif