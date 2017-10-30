

#ifndef __ENGINE_H
#define __ENGINE_H

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

class ENGINE {
private:
	CURSOR cursor;
	TIMER timer;
	EVENT_MANAGER eventMan;
	PLAYER player;
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

	friend LRESULT __stdcall WindProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	friend void drawFrame();

public:
	ENGINE();

	void initWindow(HINSTANCE hInstance, int nCmdShow);
	void restart(void);
	void mainLoop(void);
	friend void computeShadows(HDC bhdc);

	//void switchDebugMode(void) {debugMode=!debugMode;}
};

#endif