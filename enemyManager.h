#ifndef __ENEMY_MANAGER_H
#define __ENEMY_MANAGER_H

#include <list>
#include "player.h"
#include "enemy.h"

class ENEMY_MANAGER {
private:
	int enemyMultiplier;
	std::list<ENEMY> list;
	PLAYER *playerPtr;
	MISSILE_MANAGER *missileMan;
	HBRUSH *enemybrushptr;//enemy brush and pen
	HPEN *enemypenptr;
	HBRUSH *mbr;//missile brush and pen
	HPEN *mpn;

public:
	ENEMY_MANAGER() {
		enemyMultiplier = 0;
	}
	
	void process(double);

	void resetEnemyMultiplier() {enemyMultiplier = 0;}
	int getEnemyMultiplier(void) {return enemyMultiplier;}

	void add(double newX, double newY, double newSpeed, double newHP,
		const int newAttackType, const int newMovingType, const int newRole, const int newVisualType) {
			if(DEBUGVAR_INCLUDE_ENEMIES && getCount()<MAXIMAL_ENEMIES_AT_MAP)
				list.push_back(ENEMY(newX, newY, newSpeed, newHP, newAttackType, newMovingType, newRole, newVisualType, enemybrushptr, enemypenptr, missileMan));
	}

	void init(PLAYER *ptr, MISSILE_MANAGER *mm, HBRUSH *newEnemyBrush, HPEN *newEnemyPen, HBRUSH *newMissileBrush, HPEN *newMissilePen) {playerPtr = ptr; missileMan = mm; enemybrushptr = newEnemyBrush; enemypenptr = newEnemyPen; mbr = newMissileBrush; mpn = newMissilePen;}

	void draw(HDC bhdc) {
		for(std::list<ENEMY>::iterator i=list.begin(); i!=list.end(); ++i) {
			i->draw(bhdc);
		}
	}

	void increaseMultiplier(void) {enemyMultiplier++;}

	void move(double deltaTime) {
		for(std::list<ENEMY>::iterator i=list.begin(); i!=list.end(); ++i) {
			i->move(deltaTime, playerPtr->getX(), playerPtr->getY());
		}
	}

	//void correctPosition() {
	//	for(std::list<ENEMY>::iterator i=list.begin(); i!=list.end(); ++i) {
	//		i->correct();//(deltaTime, playerPtr->getX(), playerPtr->getY());
	//	}
	//}

	void removeDeadEnemies(void) {
		std::list<ENEMY>::iterator i = list.begin();
		while (i != list.end()) {
			if (!i->isAlive())
			{
			list.erase(i);
			i = list.begin();
			}
			else
			++i;
		}
	}

	std::list<ENEMY> *getList(void) {return &list;}

	int getCount(void) {
		return list.size();
	}
};

#endif