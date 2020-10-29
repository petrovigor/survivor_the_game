#include <iostream>
#include <time.h>
#include "engine.h"
#include "controller.h"
#include "player.h"

Engine::Engine() { }
Engine::~Engine() { }

void Engine::initWindow( int width, int height ) {
  callback = std::make_unique<WindowCallback>( );
  callback->SetEngine( this );

  window = std::make_unique<Window>( );
  window->SetCallback( callback.get() );
  window->createWindow( width, height, "myClassNameSurvivor" );

	srand((unsigned)time(NULL));
  timer.init();

  auto& phys = PhysicsManager::instance();

	//if(DEBUGVAR_INCLUDE_BLOCKS) {
		//phys.createBlock( 320.f, 120.f, 200.f, 20.f );
		//phys.createBlock( 50.f, 200.f, 25.f, 50.f );
		//phys.createBlock( 75.f, 400.f, 75.f, 75.f );
		//phys.createBlock( 200.f, 300.f, 200.f, 75.f );
		//phys.createBlock( 600.f, 420.f, 30.f, 80.f );
		//phys.createBlock( 550.f, 300.f, 200.f, 100.f );
  phys.createPlayer( 400.f, 300.f );
	//}
}

void Engine::processController() {
  const auto& keyboard = Controller::instance();
  auto& phys = PhysicsManager::instance();

	if(keyboard.isLMBpressed()) {
    static float dt = 0.f;

    if(dt <= 0.f) {
      const auto player = phys.getPlayer( );
      const float targetX = phys.getMouseWorldX();
      const float targetY = phys.getMouseWorldY();

      Player* pl = reinterpret_cast<Player*>(&*player);
      pl->attack( targetX, targetY );
      phys.createProjectile(0.f, 0.f, 1.f, 0.f);
    } else {
      dt -= 0.01f;
    }
	}
}

void Engine::mainLoop() {
	MSG msg;
	float dt;

	while(true) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if(GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				return;
			}
		} else {
		  timer.update();
		  dt = timer.getDelta();

      auto& phys = PhysicsManager::instance();
      phys.updateWorldPhysics(dt);
      processController();
		  drawFrame();
    }
	}
}

void Engine::drawFrame() {
  const HDC  dc     = window->getDC( );
  const HDC  memdc  = window->getMemDC( );

  const RECT clientRect = window->getClientRect();
	FillRect(memdc, &clientRect, window->getBrush());
  
  auto& phys = PhysicsManager::instance();
  phys.renderWorld(memdc);

	BitBlt(dc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, SRCCOPY);
}

void Engine::closeApp() {
  callback->OnDestroy( );
}
