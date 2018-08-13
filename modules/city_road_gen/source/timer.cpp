#include "timer.h"

e4_timer::e4_timer() {
	current = 0.0f;
	last = 0.0f;
	tickLength = 0.0f;
	frequency = 0.0f;
	memset(&startTime, 0, sizeof(startTime));
}

float e4_timer::get(void) {
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	SetThreadAffinityMask(GetCurrentThread(), oldMask);

	return ((currentTime.QuadPart - startTime.QuadPart) * tickLength);
}

void e4_timer::update(void) {
	last = current;
	current = get();
}

float e4_timer::getDelta(void) {
	return current - last;
}

bool e4_timer::init(void) {
	LARGE_INTEGER li;

	if(!QueryPerformanceFrequency(&li)) {
		return false;
	}

	frequency = (float)li.QuadPart;
	tickLength = 1.0f / frequency;

	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&startTime);
	SetThreadAffinityMask(GetCurrentThread(), oldMask);

    current = last = get();
	return true;
}