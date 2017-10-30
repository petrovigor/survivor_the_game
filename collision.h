//sorted.

#ifndef __COLLISION_H
#define __COLLISION_H

#include "gameObject.h"
#include "missile.h"

class COLLISION {
private:
	GAME_OBJECT *f;
	MISSILE *s;
	bool isNew;
	bool check;

public:
	explicit COLLISION(GAME_OBJECT *_f, MISSILE *_s) {
		f = _f;
		s = _s;
		isNew = true;
		check = false;
	}

	GAME_OBJECT *getFirstObjectPtr(void) {return f;}
	MISSILE *getSecondObjectPtr(void) {return s;}

	bool isCheck(void) {return check;}
	bool isItNew(void) {return isNew;}
	void makeOld(void) {isNew = false;}
	void checkNextTime(void) {check = true;}
	void uncheck(void) {check = false;}
};

#endif