#pragma once

#include <windows.h>
#include <math.h>
#include "game_object.h"

const int MISSILE_VISUAL_TYPE_ELLIPSE = 0,
	      MISSILE_VISUAL_TYPE_SQUARE = 1;

const int MISSILE_TARGET_TYPE_ENEMIES = 0,
	      MISSILE_TARGET_TYPE_HERO = 1;

class MISSILE:public GameObject {
private:
	bool flag;
	float damage;
	int visualType;
	int targetType;
	int penCount;
	HBRUSH *br;
	HPEN *pn;

public:
	MISSILE(float newX, float newY, float newSpeed, float newDamage, float newAngle, const int newVisualType, const int newTargetType, float newMissileSize, int newPenCount, HBRUSH *newBrush, HPEN *newPen) {
		x = newX;
		y = newY;
		speed = newSpeed;
		angle = newAngle;
		size = newMissileSize;
		visualType = newVisualType;
		targetType = newTargetType;
		damage = newDamage;
		penCount = newPenCount;
		flag = true;
		br=newBrush;
		pn=newPen;
	}

	void draw(HDC bhdc);

	void move(float deltaTime) {
		x+=(speed*deltaTime)*cos(angle);
		y+=(speed*deltaTime)*sin(angle);
	}

	void pen(void) {penCount--;}
	int getPenCount(void) {return penCount;}

	void setMissileUnused(void) {
		flag = false;
	}

	bool isUnused(void) {
		return !flag;
	}

	float getX(void) {return x;}
	float getY(void) {return y;}
	float getDamage(void) {return damage;}
	int getTargetType(void) {return targetType;}
};
