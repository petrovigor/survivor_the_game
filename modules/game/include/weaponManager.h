//#pragma once
//
//#include <vector>
//#include "weapon.h"
//
//class WEAPON_MANAGER {
//private:
//	std::vector<WEAPON> weaponList;
//
//public:
//	void init(MISSILE_MANAGER *ptr) {
//		weaponList.push_back(WEAPON(WEAPON_PISTOL, WEAPON_ATTACK_TYPE_PROJECTILES, MISSILE_TARGET_TYPE_ENEMIES,
//      1, 0.40, 1.0, 1.0, 600, 1.0, DEBUGVAR_UNLIMITED_AMMO, 1.9, 1, 400, ptr)); //75
//
//		weaponList.push_back(WEAPON(WEAPON_MACHINEGUN, WEAPON_ATTACK_TYPE_PROJECTILES, MISSILE_TARGET_TYPE_ENEMIES,
//      1, 0.08, 0.15, 0.50, 800.0, 2.5, DEBUGVAR_UNLIMITED_AMMO, 2.0, 1, 400, ptr)); //180
//
//		weaponList.push_back(WEAPON(WEAPON_ASSAULT_RIFLE, WEAPON_ATTACK_TYPE_PROJECTILES, MISSILE_TARGET_TYPE_ENEMIES,
//      1, 0.25, 0.5, 1.0, 1200, 2.25, DEBUGVAR_UNLIMITED_AMMO, 1.8, WEAPON_PENETRATIONS_UNLIMITED, 400, ptr)); //250
//
//		weaponList.push_back(WEAPON(WEAPON_PUNISHER, WEAPON_ATTACK_TYPE_PROJECTILES, MISSILE_TARGET_TYPE_ENEMIES,
//      1, 0.06, 0.15, 0.35, 900.0, 0.5, 40, 1.5, 1, 400, ptr)); //75
//
//		weaponList.push_back(WEAPON(WEAPON_SHOTGUN, WEAPON_ATTACK_TYPE_PROJECTILES, MISSILE_TARGET_TYPE_ENEMIES,
//      5, 0.8, 0.3, 0.5, 900.0, 1.5, 8, 1.2, 1, 400, ptr)); //75
//	}
//
//	WEAPON* getWeaponById(const int id) {
//		return &weaponList[id];
//	}
//};
