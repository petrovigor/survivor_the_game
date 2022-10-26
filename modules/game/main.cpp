#include "engine.h"

#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//srand((unsigned)time(NULL));

	Engine engine;

  if( true ) {

    AllocConsole( );
    freopen("CONOUT$", "w", stdout);

  }

	engine.initWindow(800, 600);
	engine.mainLoop();

  //std::cout << (1499 / 1500) << std::endl;
  //std::cout << (1500 / 1500) << std::endl;
  //std::cout << (2500 / 1500) << std::endl;
  //std::cout << (3000 / 1500) << std::endl;

	return 0;
}