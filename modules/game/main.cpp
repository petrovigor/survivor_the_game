#include "engine.h"
#include "defines.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Engine engine;

  if( true ) {

    AllocConsole( );
    freopen("CONOUT$", "w", stdout);

  }

	engine.initWindow(800, 600);
	engine.mainLoop();

	return 0;
}