#include "engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	e4_engine g;

	if(g.InitWindow(hInstance, nCmdShow)) {
		if(g.InitGame()) {
			g.Launch();	
		}
	}

	return 0;
}