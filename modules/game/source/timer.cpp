#include "timer.h"

float TIMER::get(void) {
	DWORD_PTR oldMask=SetThreadAffinityMask(GetCurrentThread(),0);
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	SetThreadAffinityMask(GetCurrentThread(),oldMask);
	return((currentTime.QuadPart-startTime.QuadPart)*tickLength);
}

void TIMER::update(void) {
	last=current;
	current=get();
}

bool TIMER::init(void) {
	LARGE_INTEGER li;

	if(!QueryPerformanceFrequency(&li)) {
		return false;
	}

	frequency=(float)li.QuadPart;
	tickLength=1.0/frequency;

	DWORD_PTR oldMask=SetThreadAffinityMask(GetCurrentThread(),0);
    QueryPerformanceCounter(&startTime);
	SetThreadAffinityMask(GetCurrentThread(),oldMask);

    current=last=get();

	return true;
}