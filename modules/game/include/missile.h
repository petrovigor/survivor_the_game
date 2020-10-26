#ifndef __MISSILE_H
#define __MISSILE_H

#include <windows.h>
#include <math.h>
#include "game_object.h"

const int MISSILE_VISUAL_TYPE_ELLIPSE = 0,
	      MISSILE_VISUAL_TYPE_SQUARE = 1;

const int MISSILE_TARGET_TYPE_ENEMIES = 0,
	      MISSILE_TARGET_TYPE_HERO = 1;

class MISSILE:public GameObject {
private:
	//double angle;
	bool flag;
	double damage;
	int visualType;
	int targetType;
	int penCount;//penetrations
	HBRUSH *br;
	HPEN *pn;

public:
	MISSILE(double newX, double newY, double newSpeed, double newDamage, double newAngle, const int newVisualType, const int newTargetType, double newMissileSize, int newPenCount, HBRUSH *newBrush, HPEN *newPen) {
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

	void move(double deltaTime) {
		x+=(speed*deltaTime)*cos(angle);
		y+=(speed*deltaTime)*sin(angle);
		//x = x + (speed*deltaTime) * cos(angle);
		//y = y + (speed*deltaTime) * sin(angle);
		//setXY(x, y);
	}

	void pen(void) {penCount--;}
	int getPenCount(void) {return penCount;}

	void setMissileUnused(void) {
		flag = false;
	}

	bool isUnused(void) {
		return !flag;
	}

	double getX(void) {return x;}
	double getY(void) {return y;}
	double getDamage(void) {return damage;}
	//double getAngle(void) {return angle;}
	int getTargetType(void) {return targetType;}
};

#endif