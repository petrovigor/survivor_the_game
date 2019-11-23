#include "engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Engine engine;

  if( true ) {

    AllocConsole( );
    freopen("CONOUT$", "w", stdout);

  }

	engine.initWindow(hInstance, nCmdShow);
	engine.mainLoop();

	return 0;
}