#pragma once

#include <windows.h>
#include "types.h"

class TIMER {
	LARGE_INTEGER startTime;
	float32 current;
	float32 last;
	float32 frequency;
	float32 tickLength;

public:
	bool init();
	void update();
	float32 get();
	float32 getDelta() {return current-last;}
};
