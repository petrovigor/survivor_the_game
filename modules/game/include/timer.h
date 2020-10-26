#pragma once

#include <windows.h>

class TIMER {
	LARGE_INTEGER startTime;
	double current;
	double last;
	double frequency;
	double tickLength;

public:
	bool init();
	void update();
	double get();
	double getDelta() {return current-last;}
};
