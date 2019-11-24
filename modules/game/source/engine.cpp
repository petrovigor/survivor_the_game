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
  window->createWindow( width, height );

	eventMan.addEvent(EVENT_TYPE_INFINITE, EVENT_ACTION_SPAWN_ENEMY, 3); //1.5
	eventMan.addEvent(EVENT_TYPE_INFINITE, EVENT_ACTION_INCREASE_ENEMY_MULTIPLIER, 30.0);

	if(DEBUGVAR_INCLUDE_BLOCKS) {
		physicsMan.placeBlock(320,120,200,20);
		physicsMan.placeBlock(50,200,25,50);
		physicsMan.placeBlock(75,400,75,75);
		physicsMan.placeBlock(200,300,200,75);
		physicsMan.placeBlock(600,420,30,80);
		physicsMan.placeBlock(550,300,200,100);
	}
}

void Engine::mainLoop(void) {
	srand((unsigned)time(NULL));

	timer.init();
	weaponMan.init(&mMan);
	abilityMan.init(&physicsMan, &player, &eventMan, &fxMan);
	enemyMan.init(&player, &mMan, NULL, NULL, NULL, NULL/*&enemyBrush, &enemyPen, &missileBrush, &missilePen*/);
	eventMan.initEventManager(&player, &enemyMan, &physicsMan);
	player.init(&weaponMan, NULL, NULL, NULL/*&playerBrush, &playerPen, &reloadingPen*/);
	physicsMan.init(enemyMan.getList(), mMan.getList(), &player, &fxMan, NULL, NULL, NULL/*&standardPen, &standardPen, &roadPen*/);
	//restart();

	MSG msg;

	char debugTxt[80];
	char intStr[5];

	int fps = 0;
	double sec = 0.0;
	double deltaTime;

	player.setWeapon(weaponMan.getWeaponById(WEAPON_PISTOL));
	player.setAbility(abilityMan.getAbilityById(ABILITY_ID_BLINK));

	double newCursorX = 0.0,
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

		  if(ATTACH_CAMERA_TO_CURSOR) {
			  newCursorX = cursor.getX() - physicsMan.getCameraOffsetX();
			  newCursorY = cursor.getY() - physicsMan.getCameraOffsetY();
		  } else {
			  newCursorX = cursor.getX();
			  newCursorY = cursor.getY();
		  }

		  fps++;
		  timer.update();
		  deltaTime = timer.getDelta();

		  if(keys.isPressed('1') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_PISTOL));
		  } else if(keys.isPressed('2') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_MACHINEGUN));
	      } else if(keys.isPressed('3') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_ASSAULT_RIFLE));
	      } else if(keys.isPressed('4') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_PUNISHER));
	      } else if(keys.isPressed('5') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_SHOTGUN));
	      }

		  if(keys.isPressed('R') && !player.isReloading()) {
			  player.denyShooting();
			  player.startReloading();
			  eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_RELOADING, player.getCurrentWeapon()->getReloadTime());
		  }

		  if(keys.isRMBpressed()) {
			  if(!player.isCasting()) {
				  if(player.isAllowedCasting()) {
					  // start targeting ability
					  player.setCastingFlag(true);
					  player.getCurrentAbility()->startTargeting();
				  }
			  }
		  } else {
			  if(player.isCasting()) {
				  player.setCastingFlag(false);
				  player.getCurrentAbility()->endTargeting();
				  abilityMan.endCasting(player.getCurrentAbility(), newCursorX, newCursorY/*newCursorX, newCursorY*/);
			  }
		  }

		  if(keys.isLMBpressed() && player.isAllowedAttack() && !player.isReloading()) {
			  if(player.getCurrentWeapon()->getAmmo() <= 0 && player.getCurrentWeapon()->getMaxAmmo()!=-1) {
				  player.denyShooting();
				  player.startReloading();
				  eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_RELOADING, player.getCurrentWeapon()->getReloadTime());
			  } else {
				  // *переписать алгоритм стрельбы. именно выстрела
				  double angle = abc(player.getX(), player.getY(), newCursorX, newCursorY);
				  double x = player.getX() + player.getSize() * cos(angle)/* + physicsMan.getCameraOffsetX()*/;
				  double y = player.getY() + player.getSize() * sin(angle)/* + physicsMan.getCameraOffsetY()*/;

				  player.attack(x,y,newCursorX, newCursorY, 0, 0/*&missileBrush,&missilePen*/);

				  if(!DEBUGVAR_AEZAKMI) {
					  physicsMan.createNoise(x,y,player.getCurrentWeapon()->getWeaponNoiseRadius());
				  }

				  eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_ALLOW_SHOOTING, player.getCurrentWeapon()->getWaitingTime());
				  fxMan.addShell(x,y, angle + 90*DEGTORAD);
				  fxMan.addFlash(x, y, 40.0, 0.1, FX_VISUAL_TYPE_ELLIPSE);
			  }
		  }

		  if(player.isReloading()) {
			  player.incAngle();
			  player.incReloadingTime(deltaTime);
		  }

		  eventMan.updateEvents(deltaTime);
		  abilityMan.updateAbilitiesProcess(deltaTime);
		  fxMan.updateFXs(deltaTime);
		  physicsMan.processNoises(deltaTime);
		  physicsMan.moveAll(deltaTime,keys.getPlayerDirection());
		  physicsMan.processCollisions();
		  physicsMan.cleanUpMissiles();
		  physicsMan.removeNoises();
		  physicsMan.deposeGameObjectsFromCenter(/*physicsMan.getCameraOffsetX(), physicsMan.getCameraOffsetY()*/);
		  enemyMan.removeDeadEnemies();

		  sec+=deltaTime;

		  //debug:
		  if(sec>=1.0) {
			  strcpy_s(debugTxt, 80, "");

			  //strcpy_s(debugTxt, 80, "ev=");
			  //_itoa_s(eventMan.getEventCount(), intStr, 10);
			  //strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "|fps=");
			  _itoa_s(fps, intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "|w=");
			  _itoa_s(player.getCurrentWeapon()->getMissilesCountPerAttack(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "|m=");
			  _itoa_s(mMan.getCount(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "|a=");
			  _itoa_s(player.getCurrentWeapon()->getAmmo(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "/");
			  _itoa_s(player.getCurrentWeapon()->getMaxAmmo(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  if(DEBUGVAR_INCLUDE_ENEMIES) {
				  strcat_s(debugTxt, 80, "|e=");
				  _itoa_s(enemyMan.getCount(), intStr, 10);
				  strcat_s(debugTxt, 80, intStr);
			  }

			  strcat_s(debugTxt, 80, "|c=");
			  _itoa_s(physicsMan.getCollisionsCount(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  if(DEBUGVAR_INCLUDE_BLOCKS) {
				  strcat_s(debugTxt, 80, "|b=");
				  _itoa_s(physicsMan.getBlocksCount(), intStr, 10);
				  strcat_s(debugTxt, 80, intStr);
			  }

			  if(DEBUGVAR_INCLUDE_ROADS) {
				  strcat_s(debugTxt, 80, "|r=");
				  _itoa_s(physicsMan.getRoadsCount(), intStr, 10);
				  strcat_s(debugTxt, 80, intStr);
			  }

			  if(DEBUGVAR_INCLUDE_SHELLS) {
				  strcat_s(debugTxt, 80, "|sh=");
				  _itoa_s(physicsMan.getShellsCount(), intStr, 10);
				  strcat_s(debugTxt, 80, intStr);
			  }
			
			  SetWindowTextA(window->getHWND(), debugTxt);
			  sec = 0;
			  fps = 0;
		  }

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


	//SelectObject(memdc, brushWhite);
	//SelectObject(memdc, penBlack);

	if(DEBUGVAR_SHOW_NOISES) {
		physicsMan.drawNoises(memdc);
	}

	physicsMan.drawRoads(memdc);
	physicsMan.drawBlocks(memdc);
	mMan.draw(memdc);
	player.draw(memdc);
	enemyMan.draw(memdc);
	fxMan.draw(memdc);
	cursor.draw(memdc);

	if(DEBUGVAR_SHOW_SHADOWS) {
		//SelectObject(bhdc, standardPen);
		//SelectObject(bhdc, standardBrush);

		physicsMan.computeShadows(memdc,
			player.getX()/*pointer->cursor.getX() + pointer->physicsMan.getCameraOffsetX()*/,
			player.getY()/*pointer->cursor.getY() + pointer->physicsMan.getCameraOffsetY()*/);
	}

	BitBlt(dc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, SRCCOPY);
	//DeleteObject(bhdc);
	//DeleteObject(buff);
}

void Engine::closeApp() {
  callback->OnDestroy( );
}

#if 0

#include <iostream>
#include "engine.h"

static HWND hWnd;
static RECT clientRect;
static HDC hdc;
static HDC bhdc;
static HGDIOBJ buff;
static PAINTSTRUCT ps;

static RECT tmprct;

static HBRUSH brushWhite;
static HBRUSH brushBlack;
static HPEN penBlack;
static HPEN penWhite;

double mouseX, mouseY;
POINT mousePoint;

Engine::Engine() {
	timeFactor = 1.0;
	debugMode = false;
}

Engine::~Engine() { }

void Engine::drawFrame() {
	bhdc = CreateCompatibleDC(hdc);
	GetClientRect(hWnd, &clientRect);
	buff = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
	SelectObject(bhdc, buff);
	BitBlt(bhdc, 0, 0, clientRect.right, clientRect.bottom, hdc, 0, 0, SRCCOPY);
	FillRect(bhdc, &clientRect, brushWhite);


	SelectObject(bhdc, brushWhite);
	SelectObject(bhdc, penBlack);

	if(DEBUGVAR_SHOW_NOISES) {
		physicsMan.drawNoises(bhdc);
	}

	physicsMan.drawRoads(bhdc);
	physicsMan.drawBlocks(bhdc);
	mMan.draw(bhdc);
	player.draw(bhdc);
	enemyMan.draw(bhdc);
	fxMan.draw(bhdc);
	cursor.draw(bhdc);

	if(DEBUGVAR_SHOW_SHADOWS) {
		//SelectObject(bhdc, standardPen);
		//SelectObject(bhdc, standardBrush);

		physicsMan.computeShadows(bhdc,
			player.getX()/*pointer->cursor.getX() + pointer->physicsMan.getCameraOffsetX()*/,
			player.getY()/*pointer->cursor.getY() + pointer->physicsMan.getCameraOffsetY()*/);
	}

	BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, bhdc, 0, 0, SRCCOPY);
	DeleteObject(bhdc);
	DeleteObject(buff);
}

void Engine::initWindow(HINSTANCE hInstance, int nCmdShow) {
  window = std::make_unique<Window>( );
  window->createWindow( 640, 480 );
}

void Engine::restart(void) {
	eventMan.addEvent(EVENT_TYPE_INFINITE, EVENT_ACTION_SPAWN_ENEMY, 3); //1.5
	eventMan.addEvent(EVENT_TYPE_INFINITE, EVENT_ACTION_INCREASE_ENEMY_MULTIPLIER, 30.0);

	if(DEBUGVAR_INCLUDE_BLOCKS) {
		physicsMan.placeBlock(320,120,200,20);
		physicsMan.placeBlock(50,200,25,50);
		physicsMan.placeBlock(75,400,75,75);
		physicsMan.placeBlock(200,300,200,75);
		physicsMan.placeBlock(600,420,30,80);
		physicsMan.placeBlock(550,300,200,100);
	}
}

void Engine::mainLoop(void) {
	srand((unsigned)time(NULL));

	timer.init();
	weaponMan.init(&mMan);
	abilityMan.init(&physicsMan, &player, &eventMan, &fxMan);
	enemyMan.init(&player, &mMan, NULL, NULL, NULL, NULL/*&enemyBrush, &enemyPen, &missileBrush, &missilePen*/);
	eventMan.initEventManager(&player, &enemyMan, &physicsMan);
	player.init(&weaponMan, NULL, NULL, NULL/*&playerBrush, &playerPen, &reloadingPen*/);
	physicsMan.init(enemyMan.getList(), mMan.getList(), &player, &fxMan, NULL, NULL, NULL/*&standardPen, &standardPen, &roadPen*/);
	restart();

	MSG msg;

	char debugTxt[80];
	char intStr[5];

	int fps = 0;
	double sec = 0.0;
	double deltaTime;

	player.setWeapon(weaponMan.getWeaponById(WEAPON_PISTOL));
	player.setAbility(abilityMan.getAbilityById(ABILITY_ID_BLINK));

	double newCursorX = 0.0,
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

		  if(ATTACH_CAMERA_TO_CURSOR) {
			  newCursorX = cursor.getX() - physicsMan.getCameraOffsetX();
			  newCursorY = cursor.getY() - physicsMan.getCameraOffsetY();
		  } else {
			  newCursorX = cursor.getX();
			  newCursorY = cursor.getY();
		  }

		  fps++;
		  timer.update();
		  deltaTime = timer.getDelta();

		  if(keys.isPressed('1') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_PISTOL));
		  } else if(keys.isPressed('2') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_MACHINEGUN));
	      } else if(keys.isPressed('3') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_ASSAULT_RIFLE));
	      } else if(keys.isPressed('4') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_PUNISHER));
	      } else if(keys.isPressed('5') && !player.isReloading()) {
			  player.setWeapon(weaponMan.getWeaponById(WEAPON_SHOTGUN));
	      }

		  if(keys.isPressed('R') && !player.isReloading()) {
			  player.denyShooting();
			  player.startReloading();
			  eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_RELOADING, player.getCurrentWeapon()->getReloadTime());
		  }

		  if(keys.isRMBpressed()) {
			  if(!player.isCasting()) {
				  if(player.isAllowedCasting()) {
					  // start targeting ability
					  player.setCastingFlag(true);
					  player.getCurrentAbility()->startTargeting();
				  }
			  }
		  } else {
			  if(player.isCasting()) {
				  player.setCastingFlag(false);
				  player.getCurrentAbility()->endTargeting();
				  abilityMan.endCasting(player.getCurrentAbility(), newCursorX, newCursorY/*newCursorX, newCursorY*/);
			  }
		  }

		  if(keys.isLMBpressed() && player.isAllowedAttack() && !player.isReloading()) {
			  if(player.getCurrentWeapon()->getAmmo() <= 0 && player.getCurrentWeapon()->getMaxAmmo()!=-1) {
				  player.denyShooting();
				  player.startReloading();
				  eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_RELOADING, player.getCurrentWeapon()->getReloadTime());
			  } else {
				  // *переписать алгоритм стрельбы. именно выстрела
				  double angle = abc(player.getX(), player.getY(), newCursorX, newCursorY);
				  double x = player.getX() + player.getSize() * cos(angle)/* + physicsMan.getCameraOffsetX()*/;
				  double y = player.getY() + player.getSize() * sin(angle)/* + physicsMan.getCameraOffsetY()*/;

				  player.attack(x,y,newCursorX, newCursorY, 0, 0/*&missileBrush,&missilePen*/);

				  if(!DEBUGVAR_AEZAKMI) {
					  physicsMan.createNoise(x,y,player.getCurrentWeapon()->getWeaponNoiseRadius());
				  }

				  eventMan.addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_ALLOW_SHOOTING, player.getCurrentWeapon()->getWaitingTime());
				  fxMan.addShell(x,y, angle + 90*DEGTORAD);
				  fxMan.addFlash(x, y, 40.0, 0.1, FX_VISUAL_TYPE_ELLIPSE);
			  }
		  }

		  if(player.isReloading()) {
			  player.incAngle();
			  player.incReloadingTime(deltaTime);
		  }

		  eventMan.updateEvents(deltaTime);
		  abilityMan.updateAbilitiesProcess(deltaTime);
		  fxMan.updateFXs(deltaTime);
		  physicsMan.processNoises(deltaTime);
		  physicsMan.moveAll(deltaTime,keys.getPlayerDirection());
		  physicsMan.processCollisions();
		  physicsMan.cleanUpMissiles();
		  physicsMan.removeNoises();
		  physicsMan.deposeGameObjectsFromCenter();
		  enemyMan.removeDeadEnemies();

		  sec+=deltaTime;

		  //debug:
		  if(sec>=1.0) {
			  strcpy_s(debugTxt, 80, "");

			  //strcpy_s(debugTxt, 80, "ev=");
			  //_itoa_s(eventMan.getEventCount(), intStr, 10);
			  //strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "|fps=");
			  _itoa_s(fps, intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "|w=");
			  _itoa_s(player.getCurrentWeapon()->getMissilesCountPerAttack(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "|m=");
			  _itoa_s(mMan.getCount(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "|a=");
			  _itoa_s(player.getCurrentWeapon()->getAmmo(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  strcat_s(debugTxt, 80, "/");
			  _itoa_s(player.getCurrentWeapon()->getMaxAmmo(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  if(DEBUGVAR_INCLUDE_ENEMIES) {
				  strcat_s(debugTxt, 80, "|e=");
				  _itoa_s(enemyMan.getCount(), intStr, 10);
				  strcat_s(debugTxt, 80, intStr);
			  }

			  strcat_s(debugTxt, 80, "|c=");
			  _itoa_s(physicsMan.getCollisionsCount(), intStr, 10);
			  strcat_s(debugTxt, 80, intStr);

			  if(DEBUGVAR_INCLUDE_BLOCKS) {
				  strcat_s(debugTxt, 80, "|b=");
				  _itoa_s(physicsMan.getBlocksCount(), intStr, 10);
				  strcat_s(debugTxt, 80, intStr);
			  }

			  if(DEBUGVAR_INCLUDE_ROADS) {
				  strcat_s(debugTxt, 80, "|r=");
				  _itoa_s(physicsMan.getRoadsCount(), intStr, 10);
				  strcat_s(debugTxt, 80, intStr);
			  }

			  if(DEBUGVAR_INCLUDE_SHELLS) {
				  strcat_s(debugTxt, 80, "|sh=");
				  _itoa_s(physicsMan.getShellsCount(), intStr, 10);
				  strcat_s(debugTxt, 80, intStr);
			  }
			
			  SetWindowTextA(hWnd, debugTxt);
			  sec = 0;
			  fps = 0;
		  }

		  drawFrame();
		  //Sleep(SLEEP_MS);
    }
	}
}


#endif //0
