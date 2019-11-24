#pragma once

#include <memory>

#include "window.h"
#include "physics_man.h"

#include "defines.h"
#include "misc.h"
#include "keys.h"
#include "timer.h"
#include "fxManager.h"

#include "weaponManager.h" //weapon.h|missileManager.h|defines.h|missile.h|misc.h|gameObject.h
#include "eventManager.h" //event.h|player.h|enemyManager.h|enemy.h
#include "player.h" //defines.h|gameObject.h|weapon.h|weaponManager.h|ability.h
#include "cursor.h" //defines.h|gameObject.h
#include "missileManager.h" //defines.h|missile.h|misc.h
#include "enemyManager.h" //player.h|enemy.h
#include "physicsManager.h" //enemy.h|missile.h|collision.h|player.h|block.h
#include "abilityManager.h" //ability.h
#include "camera.h"

class Engine {
private:
  std::unique_ptr<Window>         window;
  std::unique_ptr<WindowCallback> callback;
  //std::unique_ptr<PhysicsManager> physics_man;

	CURSOR cursor;
	TIMER timer;
	EVENT_MANAGER eventMan;
	Player player;
	WEAPON_MANAGER weaponMan;
	KEYS keys;
	HBRUSH windowCleanerBrush;
	FX_MANAGER fxMan;
	MISSILE_MANAGER mMan;
	ENEMY_MANAGER enemyMan;
	PHYSICS_MANAGER physicsMan;
	ABILITY_MANAGER abilityMan;
	CAMERA camera;

	bool debugMode;
	double timeFactor;

public:
	Engine();
  ~Engine();
  
  KEYS& getControlManager() { return keys; }
  CURSOR& getCursor() { return cursor; }
  Player& getPlayer() { return player; }
  CAMERA& getCamera() { return camera; }
  PHYSICS_MANAGER& getPhysicsManager() { return physicsMan; }

	void initWindow(int width, int height);
	void mainLoop();
  void closeApp();

private:
	void drawFrame();

};



#if 0

#pragma once

#include <windows.h>
#include <time.h>

#include "defines.h"
#include "misc.h"
#include "keys.h"
#include "timer.h"
#include "fxManager.h"

#include "weaponManager.h" //weapon.h|missileManager.h|defines.h|missile.h|misc.h|gameObject.h
#include "eventManager.h" //event.h|player.h|enemyManager.h|enemy.h
#include "player.h" //defines.h|gameObject.h|weapon.h|weaponManager.h|ability.h
#include "cursor.h" //defines.h|gameObject.h
#include "missileManager.h" //defines.h|missile.h|misc.h
#include "enemyManager.h" //player.h|enemy.h
#include "physicsManager.h" //enemy.h|missile.h|collision.h|player.h|block.h
#include "abilityManager.h" //ability.h
#include "camera.h"


#include <memory>
#include "window.h"

class Engine {
private:
  std::unique_ptr<Window> window;

	CURSOR cursor;
	TIMER timer;
	EVENT_MANAGER eventMan;
	Player player;
	WEAPON_MANAGER weaponMan;
	KEYS keys;
	HBRUSH windowCleanerBrush;
	FX_MANAGER fxMan;
	MISSILE_MANAGER mMan;
	ENEMY_MANAGER enemyMan;
	PHYSICS_MANAGER physicsMan;
	ABILITY_MANAGER abilityMan;
	CAMERA camera;

	bool debugMode;
	double timeFactor;
	void drawFrame();

public:
	Engine();
  ~Engine();

	void initWindow(HINSTANCE hInstance, int nCmdShow);
	void restart(void);
	void mainLoop(void);
	friend void computeShadows(HDC bhdc);

	//void switchDebugMode(void) {debugMode=!debugMode;}
};


#endif //0

