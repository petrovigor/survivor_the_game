#pragma once

#include <list>
#include "defines.h"
#include "missile.h"
#include "misc.h"

class MISSILE_MANAGER {
private:
	std::list<MISSILE> mList;

public:
	void addMissile(double newX, double newY, double newAngle, double newSpeed, double newDamage, const int newVisualType, const int newTargetType, double newMissileSize, int newPenCount, HBRUSH *newBrush = 0, HPEN *newPen = 0) {
    mList.push_back(MISSILE(newX, newY, newSpeed, newDamage, newAngle, newVisualType, newTargetType, newMissileSize, newPenCount, nullptr, nullptr));
	}

	void draw(HDC bhdc) {
		for(std::list<MISSILE>::iterator i=mList.begin(); i!=mList.end(); ++i) {
			i->draw(bhdc);
		}
	}

	std::list<MISSILE> *getList(void) {return &mList;}

	int getCount(void) {return mList.size();}
};
