#ifndef __PLAYER_H
#define __PLAYER_H

//#include <stdio.h> //FOR DEBUG ONLY
#include "object.h"
#include "routine.h"

enum PLAYER_DIRECTION { PLAYER_DIRECTION_N = 0,
	                    PLAYER_DIRECTION_E = 1,
						PLAYER_DIRECTION_S = 2,
	                    PLAYER_DIRECTION_W = 3,
						PLAYER_DIRECTION_NE = 4,
	                    PLAYER_DIRECTION_SE = 5,
						PLAYER_DIRECTION_SW = 6,
	                    PLAYER_DIRECTION_NW = 7,
	                    PLAYER_DIRECTION_IDLE = 8 };

class e4_player : public e4_object {
private:
	int direct;
	float shootTime;
	bool canShoot;

public:
	e4_player(void);

	void draw(HDC hdc);
	void move(float deltaTime);

	void setDirection(int dir);
	int getDirection(void);

	void updateCooldown(float deltaTime);

	bool canPlayerShoot(void);
	void denyShooting(void);
};


#endif
