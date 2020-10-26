#ifndef __WEAPON_H
#define __WEAPON_H

#include "missileManager.h"

const int WEAPON_PISTOL = 0,
	      WEAPON_MACHINEGUN = 1,
		  WEAPON_ASSAULT_RIFLE = 2,
		  WEAPON_PUNISHER = 3,
		  WEAPON_SHOTGUN = 4;

const int WEAPON_PENETRATIONS_UNLIMITED = -1;

const int WEAPON_ATTACK_TYPE_PROJECTILES = 0,
	      WEAPON_ATTACK_TYPE_INSTANT = 1,
		  WEAPON_ATTACK_TYPE_MELEE = 2,
		  WEAPON_ATTACK_TYPE_POINT = 3;

class WEAPON {
private:
	int id;
	int ammo;
	int maxAmmo;
	int penCount;
	int attackType;
	int targetType;
	int missileVisualType;
	int missilesCountPerAttack;
	double reloadTime;
	double minDamage;
	double maxDamage;
	double missileSpeed;
	double waitingTime;
	double missileSize;
	double noiseRadius;
	MISSILE_MANAGER *ptr;

public:
	WEAPON(const int newId, const int newAttackType, const int newTargetType, const int newMissileVisualType, int newMissilesCountPerAttack,
		double newWaitingTime, double newMinDamage, double newMaxDamage, double newMissileSpeed,
		double newReloadTime, int newMaxAmmo, double newMissileSize, int newPenCount, double newNoiseRadius, MISSILE_MANAGER *newMissileManagerPtr) {
			id=newId;
			ammo=maxAmmo=newMaxAmmo;
			attackType=newAttackType;
			targetType=newTargetType;
			missileVisualType=newMissileVisualType;
			missilesCountPerAttack=newMissilesCountPerAttack;
			reloadTime=newReloadTime;
			minDamage=newMinDamage;
			maxDamage=newMaxDamage;
			missileSpeed=newMissileSpeed;
			waitingTime=newWaitingTime;
			missileSize=newMissileSize;
			noiseRadius=newNoiseRadius;
			ptr=newMissileManagerPtr;
			penCount=newPenCount;
	}

	void attack(double fromX, double fromY, double toX, double toY, HBRUSH *b, HPEN *p) {
		if(maxAmmo!=DEBUGVAR_UNLIMITED_AMMO) ammo--;

		if(attackType==WEAPON_ATTACK_TYPE_PROJECTILES) {
			for(int i=0;i<missilesCountPerAttack;i++) {
				double damage;

				if(minDamage == maxDamage) damage = minDamage;
				else damage = ((double)(rand()%(int)(maxDamage*100)+(minDamage*100))/100);

				double angle = abc(fromX, fromY, toX, toY);

				if(DEBUGVAR_ALLOW_SHOT_PRECISION) {
					double dispersionMax = 10 * DEGTORAD;

					if(rand()%2==0) {
						angle += ((double)(rand()%(int)(dispersionMax*100))/100);
					} else {
						angle -= ((double)(rand()%(int)(dispersionMax*100))/100);
					}
				}

				ptr->addMissile(fromX, fromY, angle, missileSpeed, damage, missileVisualType, targetType, missileSize, penCount, b, p);
			}
		}
	}

	double getWaitingTime(void) {return waitingTime;}
	int getMissilesCountPerAttack(void) {return missilesCountPerAttack;}
	double getMissileSpeed(void) {return missileSpeed;}
	int getMissileVisualType(void) {return missileVisualType;}
	double getMissileSize(void) {return missileSize;}
	int getAmmo(void) {return ammo;}
	int getMaxAmmo(void) {return maxAmmo;}
	double getReloadTime(void) {return reloadTime;}
	int getMissileTargetType(void) {return targetType;}
	int getPenCount(void) {return penCount;}
	int getAttackType(void) {return attackType;}
	double getWeaponNoiseRadius(void) {return noiseRadius;}

	void reloaded(void) {ammo=maxAmmo;}
};

#endif