//#pragma once
//
//#include <windows.h>
//#include "game_object.h"
//
//const int MISSILE_TARGET_TYPE_ENEMIES = 0,
//	      MISSILE_TARGET_TYPE_HERO = 1;
//
//class MISSILE : public GameObject {
//private:
//	bool flag;
//	float damage;
//	int targetType;
//	int penCount;
//	HBRUSH *br;
//	HPEN *pn;
//
//public:
//	MISSILE(float newX, float newY, float newSpeed, float newDamage, float newAngle, const int newTargetType, float newMissileSize, int newPenCount, HBRUSH *newBrush, HPEN *newPen);
//
//	void pen();
//	int getPenCount();
//
//	void setMissileUnused();
//
//	bool isUnused();
//
//	float getX();
//	float getY();
//	float getDamage();
//	int getTargetType();
//};
