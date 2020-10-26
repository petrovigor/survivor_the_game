#pragma once

#include <windows.h>

class TIMER {
	LARGE_INTEGER startTime;
	float current;
	float last;
	float frequency;
	float tickLength;

public:
	bool init();
	void update();
	float get();
	float getDelta() {return current-last;}
};
