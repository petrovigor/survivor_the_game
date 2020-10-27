//#pragma once
//
//#include "physicsManager.h"
//
//const int WEAPON_PISTOL = 0,
//	      WEAPON_MACHINEGUN = 1,
//		  WEAPON_ASSAULT_RIFLE = 2,
//		  WEAPON_PUNISHER = 3,
//		  WEAPON_SHOTGUN = 4;
//
//const int WEAPON_PENETRATIONS_UNLIMITED = -1;
//
//const int WEAPON_ATTACK_TYPE_PROJECTILES = 0,
//	      WEAPON_ATTACK_TYPE_INSTANT = 1,
//		  WEAPON_ATTACK_TYPE_MELEE = 2,
//		  WEAPON_ATTACK_TYPE_POINT = 3;
//
//class WEAPON {
//private:
//	int id;
//	int ammo;
//	int maxAmmo;
//	int penCount;
//	int attackType;
//	int targetType;
//	int missileVisualType;
//	int missilesCountPerAttack;
//	float reloadTime;
//	float minDamage;
//	float maxDamage;
//	float missileSpeed;
//	float waitingTime;
//	float missileSize;
//	float noiseRadius;
//	PHYSICS_MANAGER *ptr;
//
//public:
//	WEAPON(const int newId, const int newAttackType, const int newTargetType, int newMissilesCountPerAttack,
//		float newWaitingTime, float newMinDamage, float newMaxDamage, float newMissileSpeed,
//		float newReloadTime, int newMaxAmmo, float newMissileSize, int newPenCount, float newNoiseRadius, PHYSICS_MANAGER *newPhysicsManagerPtr) {
//			id=newId;
//			ammo=maxAmmo=newMaxAmmo;
//			attackType=newAttackType;
//			targetType=newTargetType;
//			missilesCountPerAttack=newMissilesCountPerAttack;
//			reloadTime=newReloadTime;
//			minDamage=newMinDamage;
//			maxDamage=newMaxDamage;
//			missileSpeed=newMissileSpeed;
//			waitingTime=newWaitingTime;
//			missileSize=newMissileSize;
//			noiseRadius=newNoiseRadius;
//			ptr=newPhysicsManagerPtr;
//			penCount=newPenCount;
//	}
//
//	void attack(float fromX, float fromY, float toX, float toY, HBRUSH *b, HPEN *p) {
//		if(maxAmmo!=DEBUGVAR_UNLIMITED_AMMO) ammo--;
//
//		if(attackType==WEAPON_ATTACK_TYPE_PROJECTILES) {
//			for(int i=0;i<missilesCountPerAttack;i++) {
//				float damage;
//
//				if(minDamage == maxDamage) damage = minDamage;
//				else damage = ((float)(rand()%(int)(maxDamage*100)+(minDamage*100))/100);
//
//				float angle = abc(fromX, fromY, toX, toY);
//
//				if(DEBUGVAR_ALLOW_SHOT_PRECISION) {
//					float dispersionMax = 10 * DEGTORAD;
//
//					if(rand()%2==0) {
//						angle += ((float)(rand()%(int)(dispersionMax*100))/100);
//					} else {
//						angle -= ((float)(rand()%(int)(dispersionMax*100))/100);
//					}
//				}
//
//				ptr->addMissile(fromX, fromY, angle, missileSpeed, damage, targetType, missileSize, penCount);
//			}
//		}
//	}
//
//	float getWaitingTime(void) {return waitingTime;}
//	int getMissilesCountPerAttack(void) {return missilesCountPerAttack;}
//	float getMissileSpeed(void) {return missileSpeed;}
//	float getMissileSize(void) {return missileSize;}
//	int getAmmo(void) {return ammo;}
//	int getMaxAmmo(void) {return maxAmmo;}
//	float getReloadTime(void) {return reloadTime;}
//	int getMissileTargetType(void) {return targetType;}
//	int getPenCount(void) {return penCount;}
//	int getAttackType(void) {return attackType;}
//	float getWeaponNoiseRadius(void) {return noiseRadius;}
//
//	void reloaded(void) {ammo=maxAmmo;}
//};
