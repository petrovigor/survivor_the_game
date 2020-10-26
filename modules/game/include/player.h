#pragma once

#include <windows.h>
#include "defines.h"
#include "game_object.h"
#include "weapon.h"
#include "weaponManager.h"
#include "ability.h"

class Player final : public GameObject {
private:
	WEAPON_MANAGER *weaponManPtr;
	ABILITY *ability;
	WEAPON *weapon;
	bool allowedAttack;
	bool casting;
	bool reloading;

	float reloadingTime;
	float reloadingAngle;

	HBRUSH *brPtr;
	HPEN *pPtr;
	HPEN *reloadingPPtr;
	bool allowCastingSpells;

public:
  Player(int _x, int _y, int _size, int _speed)
    : GameObject(_x, _y, _size, _speed, 0)
  { }

	Player() {
		alive = true;
		casting = false;
		x = RESOLUTION_X/2;
		y = RESOLUTION_Y/2;
		size = PLAYER_SIZE;
		speed = PLAYER_NORMAL_SPEED;
		allowedAttack = true;
		reloading = false;
		allowCastingSpells = true;
	}

	void faceTo(float X, float Y) {angle = abc(x,y,X,Y);}
	void allowShooting(void) {allowedAttack = true;}
	void allowCasting(void) {allowCastingSpells = true;}
	void denyShooting(void) {allowedAttack = false;}
	void denyCasting(void) {allowCastingSpells = false;}
	bool isAllowedAttack(void) {return allowedAttack;}
	bool isAllowedCasting(void) {return allowCastingSpells;}

	void draw(HDC bhdc);
	void move(float deltaTime, int direction);
	void init(WEAPON_MANAGER *weaponMan, HBRUSH *br, HPEN *pen, HPEN *newReloadingPPtr) {weaponManPtr = weaponMan; brPtr=br; pPtr=pen; reloadingPPtr=newReloadingPPtr;}

	bool isCasting(void) {return casting;}
	void setCastingFlag(bool flag) {casting=flag;}

	void attack(float fromX, float fromY, float toX, float toY,HBRUSH *b,HPEN *p);

	void incReloadingTime(float deltaTime) {reloadingTime += deltaTime;}
	float getReloadingPerc(void) {return reloadingTime/weapon->getReloadTime();}
	void incAngle() {reloadingAngle = 270.0 + (360.0 * getReloadingPerc());}
	void startReloading(void) {reloading = true; reloadingTime = 0.0; reloadingAngle = 270.0;}
	void finishReloading(void) {reloading = false; }
	bool isReloading(void) {return reloading;}

	void setWeapon(WEAPON *whichWeapon) {weapon = whichWeapon;}
	void setAbility(ABILITY *whichAbility) {ability = whichAbility;}
	WEAPON* getCurrentWeapon(void) {return weapon;}
	ABILITY* getCurrentAbility(void) {return ability;}
};
