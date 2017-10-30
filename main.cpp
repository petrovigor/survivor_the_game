#include "engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ENGINE engine;

	engine.initWindow(hInstance, nCmdShow);
	engine.mainLoop();

	return 0;
}