#include "engine.h"
#include "defines.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Engine engine;

  if( true ) {

    AllocConsole( );
    freopen("CONOUT$", "w", stdout);

  }

	engine.initWindow(RESOLUTION_X, RESOLUTION_Y);
	engine.mainLoop();

	return 0;
}