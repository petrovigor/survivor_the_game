#pragma once

#include <memory>

#include "window.h"
#include "physics_man.h"

#include "defines.h"
#include "misc.h"
#include "keys.h"
#include "timer.h"
#include "fxManager.h"

#include "weaponManager.h"
#include "eventManager.h"
#include "player.h"
#include "cursor.h"
#include "missileManager.h"
#include "enemyManager.h"
#include "physicsManager.h"
#include "abilityManager.h"
#include "camera.h"

class Engine {
private:
  std::unique_ptr<Window>         window;
  std::unique_ptr<WindowCallback> callback;

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
	float timeFactor;

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
