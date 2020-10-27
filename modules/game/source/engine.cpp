#include <iostream>
#include <time.h>
#include "engine.h"

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

  phys.createPlayer( 400.f, 300.f );

	//eventMan.addEvent(EVENT_TYPE_INFINITE, EVENT_ACTION_SPAWN_ENEMY, 3); //1.5
	//eventMan.addEvent(EVENT_TYPE_INFINITE, EVENT_ACTION_INCREASE_ENEMY_MULTIPLIER, 30.0);

	//if(DEBUGVAR_INCLUDE_BLOCKS) {
		phys.createBlock(320, 120, 200, 20);
		phys.createBlock(50, 200, 25, 50);
		phys.createBlock(75, 400, 75, 75);
		phys.createBlock(200, 300, 200, 75);
		phys.createBlock(600, 420, 30, 80);
		phys.createBlock(550, 300, 200, 100);
	//}
}

void Engine::mainLoop(void) {

	
	//weaponMan.init(&mMan);
	//abilityMan.init(&physicsMan, &player, &eventMan, &fxMan);
	//enemyMan.init(&player, &mMan, NULL, NULL, NULL, NULL/*&enemyBrush, &enemyPen, &missileBrush, &missilePen*/);
	//eventMan.initEventManager(&player, &enemyMan, &physicsMan);
	//player.init(&weaponMan, NULL, NULL, NULL/*&playerBrush, &playerPen, &reloadingPen*/);
	//physicsMan.init(enemyMan.getList(), mMan.getList(), &player, &fxMan, NULL, NULL, NULL/*&standardPen, &standardPen, &roadPen*/);
	//restart();

	MSG msg;
	float deltaTime;

	//player.setWeapon(weaponMan.getWeaponById(WEAPON_PISTOL));
	//player.setAbility(abilityMan.getAbilityById(ABILITY_ID_BLINK));

	float newCursorX = 0.0,
		   newCursorY = 0.0;

	while(true) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if(GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				return;
			}
		} else {

		  //if(ATTACH_CAMERA_TO_CURSOR) {
			 // newCursorX = cursor.getX() - physicsMan.getCameraOffsetX();
			 // newCursorY = cursor.getY() - physicsMan.getCameraOffsetY();
		  //} else {
			 // newCursorX = cursor.getX();
			 // newCursorY = cursor.getY();
		  //}

		  timer.update();
		  deltaTime = timer.getDelta();

      auto& phys = PhysicsManager::instance();
      phys.updateWorldPhysics(deltaTime);

		  //if(keys.isPressed('1') && !player.isReloading()) {
			 // player.setWeapon(weaponMan.getWeaponById(WEAPON_PISTOL));
		  //} else if(keys.isPressed('2') && !player.isReloading()) {
			 // player.setWeapon(weaponMan.getWeaponById(WEAPON_MACHINEGUN));
	   //   } else if(keys.isPressed('3') && !player.isReloading()) {
			 // player.setWeapon(weaponMan.getWeaponById(WEAPON_ASSAULT_RIFLE));
	   //   } else if(keys.isPressed('4') && !player.isReloading()) {
			 // player.setWeapon(weaponMan.getWeaponById(WEAPON_PUNISHER));
	   //   } else if(keys.isPressed('5') && !player.isReloading()) {
			 // player.setWeapon(weaponMan.getWeaponById(WEAPON_SHOTGUN));
	   //   }

		  //if(keys.isPressed('R') && !player.isReloading()) {
			 // player.denyShooting();
			 // player.startReloading();
			 // eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_RELOADING, player.getCurrentWeapon()->getReloadTime());
		  //}

		  //if(keys.isRMBpressed()) {
			 // if(!player.isCasting()) {
				//  if(player.isAllowedCasting()) {
				//	  // start targeting ability
				//	  player.setCastingFlag(true);
				//	  player.getCurrentAbility()->startTargeting();
				//  }
			 // }
		  //} else {
			 // if(player.isCasting()) {
				//  player.setCastingFlag(false);
				//  player.getCurrentAbility()->endTargeting();
				//  abilityMan.endCasting(player.getCurrentAbility(), newCursorX, newCursorY/*newCursorX, newCursorY*/);
			 // }
		  //}

		  //if(keys.isLMBpressed() && player.isAllowedAttack() && !player.isReloading()) {
			 // if(player.getCurrentWeapon()->getAmmo() <= 0 && player.getCurrentWeapon()->getMaxAmmo()!=-1) {
				//  player.denyShooting();
				//  player.startReloading();
				//  eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_RELOADING, player.getCurrentWeapon()->getReloadTime());
			 // } else {
				//  // *���������� �������� ��������. ������ ��������
				//  float angle = abc(player.getX(), player.getY(), newCursorX, newCursorY);
				//  float x = player.getX() + player.getSize() * cos(angle)/* + physicsMan.getCameraOffsetX()*/;
				//  float y = player.getY() + player.getSize() * sin(angle)/* + physicsMan.getCameraOffsetY()*/;

				//  player.attack(x,y,newCursorX, newCursorY, 0, 0/*&missileBrush,&missilePen*/);

				//  if(!DEBUGVAR_AEZAKMI) {
				//	  physicsMan.createNoise(x,y,player.getCurrentWeapon()->getWeaponNoiseRadius());
				//  }

				//  eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_ALLOW_SHOOTING, player.getCurrentWeapon()->getWaitingTime());
				//  fxMan.addShell(x,y, angle + 90*DEGTORAD);
				//  fxMan.addFlash(x, y, 40.0, 0.1, FX_VISUAL_TYPE_ELLIPSE);
			 // }
		  //}

		  //if(player.isReloading()) {
			 // player.incAngle();
			 // player.incReloadingTime(deltaTime);
		  //}

		  //eventMan.updateEvents(deltaTime);
		  //abilityMan.updateAbilitiesProcess(deltaTime);
		  //fxMan.updateFXs(deltaTime);
		  //physicsMan.processNoises(deltaTime);
		  //physicsMan.moveAll(deltaTime,keys.getPlayerDirection());
		  //physicsMan.processCollisions();
		  //physicsMan.cleanUpMissiles();
		  //physicsMan.removeNoises();
		  //physicsMan.deposeGameObjectsFromCenter(/*physicsMan.getCameraOffsetX(), physicsMan.getCameraOffsetY()*/);
		  //enemyMan.removeDeadEnemies();

		  drawFrame();
		  //Sleep(SLEEP_MS);
    }
	}
}

void Engine::drawFrame() {
  const HDC  dc     = window->getDC( );
  const HDC  memdc  = window->getMemDC( );

  const RECT clientRect = window->getClientRect();

	//BitBlt(bhdc, 0, 0, clientRect.right, clientRect.bottom, hdc, 0, 0, SRCCOPY);
	FillRect(memdc, &clientRect, window->getBrush());
  
  auto& phys = PhysicsManager::instance();
  phys.renderWorld(memdc);
	//SelectObject(memdc, brushWhite);
	//SelectObject(memdc, penBlack);

	//if(DEBUGVAR_SHOW_NOISES) {
	//	physicsMan.drawNoises(memdc);
	//}

	//physicsMan.drawRoads(memdc);
	//physicsMan.drawBlocks(memdc);
	//mMan.draw(memdc);
	//player.draw(memdc);
	//enemyMan.draw(memdc);
	//fxMan.draw(memdc);
	//cursor.draw(memdc);

	//if(DEBUGVAR_SHOW_SHADOWS) {
	//	//SelectObject(bhdc, standardPen);
	//	//SelectObject(bhdc, standardBrush);

	//	physicsMan.computeShadows(memdc,
	//		player.getX()/*pointer->cursor.getX() + pointer->physicsMan.getCameraOffsetX()*/,
	//		player.getY()/*pointer->cursor.getY() + pointer->physicsMan.getCameraOffsetY()*/);
	//}

	BitBlt(dc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, SRCCOPY);
	//DeleteObject(bhdc);
	//DeleteObject(buff);
}

void Engine::closeApp() {
  callback->OnDestroy( );
}
