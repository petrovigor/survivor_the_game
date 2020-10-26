#pragma once

#include <windows.h>
#include "defines.h"
#include "game_object.h"
#include "weapon.h"
#include "weaponManager.h"
#include "ability.h"
//#include "physicsManager.h"

class Player final : public GameObject {
private:
	//PHYSICS_MANAGER *phyManPtr;
	WEAPON_MANAGER *weaponManPtr;
	ABILITY *ability;
	WEAPON *weapon;
	bool allowedAttack;
	bool casting;
	bool reloading;

	double reloadingTime;
	double reloadingAngle;

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

	//void shootAt(GameObject *obj);

	void faceTo(double X, double Y) {angle = abc(x,y,X,Y);}
	void allowShooting(void) {allowedAttack = true;}
	void allowCasting(void) {allowCastingSpells = true;}
	void denyShooting(void) {allowedAttack = false;}
	void denyCasting(void) {allowCastingSpells = false;}
	bool isAllowedAttack(void) {return allowedAttack;}
	bool isAllowedCasting(void) {return allowCastingSpells;}

	void draw(HDC bhdc);
	void move(double deltaTime, int direction);
	void init(WEAPON_MANAGER *weaponMan/*, PHYSICS_MANAGER *pmPtr*/, HBRUSH *br, HPEN *pen, HPEN *newReloadingPPtr) {/*phyManPtr = pmPtr;*/ weaponManPtr = weaponMan; brPtr=br; pPtr=pen; reloadingPPtr=newReloadingPPtr;}

	bool isCasting(void) {return casting;}
	void setCastingFlag(bool flag) {casting=flag;}

	//void makeAttackPosition(void) {
	//	shieldHolding=false;
	//}

	void attack(double fromX, double fromY, double toX, double toY,HBRUSH *b,HPEN *p);

	void incReloadingTime(double deltaTime) {reloadingTime += deltaTime;}
	double getReloadingPerc(void) {return reloadingTime/weapon->getReloadTime();}
	void incAngle() {reloadingAngle = 270.0 + (360.0 * getReloadingPerc());}
	void startReloading(void) {reloading = true; reloadingTime = 0.0; reloadingAngle = 270.0;}
	void finishReloading(void) {reloading = false; /*reloadingTime = weapon->getReloadTime();*/}
	bool isReloading(void) {return reloading;}

	//void dropWeapons(void) {weaponManPtr->dropWeapons();}
	void setWeapon(WEAPON *whichWeapon) {weapon = whichWeapon;}
	void setAbility(ABILITY *whichAbility) {ability = whichAbility;}
	WEAPON* getCurrentWeapon(void) {return weapon;}
	ABILITY* getCurrentAbility(void) {return ability;}
};
