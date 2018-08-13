#include <windows.h>
#include <math.h>
#include "player.h"
#include "weaponManager.h"
//
//PLAYER::PLAYER() {
//	//COLOR red(255, 0, 0);
//
//	//WEAPON pistol(WEAPON_ATTACK_TYPE_PROJECTILES, MISSILE_VISUAL_TYPE_ELLIPSE,
//	//	1, 0.10, 10.0, 10.0, 400.0, 2.0, 10, &red, NULL);
//
//	//weapon = &pistol;
//
//}

void PLAYER::draw(HDC bhdc) {
	//SelectObject(bhdc, *brPtr);
	//SelectObject(bhdc, *pPtr);

	const double s = size * height;

	double newX = x + cameraOffsetX;
	double newY = y + cameraOffsetY;

	Ellipse(bhdc, newX-s, newY-s, newX+s, newY+s);

	double X = x + size * cos(angle) +cameraOffsetX;
	double Y = y + size * sin(angle) +cameraOffsetY;
	double sz = size/3;

	Ellipse(bhdc, X-sz, Y-sz, X+sz, Y+sz);

	if(isReloading()) {
		//SelectObject(bhdc, *reloadingPPtr);
		MoveToEx(bhdc, newX, newY, NULL);
		LineTo(bhdc, newX + s/2 * cos(DEGTORAD * reloadingAngle), newY + s/2 * sin(DEGTORAD * reloadingAngle));
		//LineTo(bhdc, x + size * cos(DEGTORAD * reloadingAngle), y + size * sin(DEGTORAD * reloadingAngle));
	}
}

void PLAYER::attack(double fromX, double fromY, double toX, double toY,HBRUSH *b,HPEN *p) {
	if(allowedAttack) {
		denyShooting();

		//double fromX = x + size/2 * cos(angle);
		//double fromY = y + size/2 * sin(angle);

		weapon->attack(fromX,fromY,toX,toY,b,p);
	}
}

void PLAYER::move(double deltaTime, const int direction) {
	//reloading cursor
	//--------------------
	backupXY();

	double dist = speed * deltaTime;
	double proection = dist / sqrt(double(2));

	if(direction == PLAYER_DIRECTION_N) {
		y -= dist;
	} else if(direction == PLAYER_DIRECTION_S) {
		y += dist;
	} else if(direction == PLAYER_DIRECTION_W) {
		x -= dist;
	} else if(direction == PLAYER_DIRECTION_E) {
		x += dist;
	} else if(direction == PLAYER_DIRECTION_NW) {
		x -= proection;
		y -= proection;
	} else if(direction == PLAYER_DIRECTION_NE) {
		x += proection;
		y -= proection;
	} else if(direction == PLAYER_DIRECTION_SE) {
		x += proection;
		y += proection;
	} else if(direction == PLAYER_DIRECTION_WS) {
		x -= proection;
		y += proection;
	}

	//double playerSize = PLAYER_SIZE;

	//if(x < PLAYER_SIZE) x = PLAYER_SIZE;
	//if(y < PLAYER_SIZE) y = PLAYER_SIZE;
	//if(x > RESOLUTION_X/*-playerSize*/) x = RESOLUTION_X/*-playerSize*/;
	//if(y > RESOLUTION_Y/*-playerSize*/) y = RESOLUTION_Y/*-playerSize*/;
}

//void PLAYER::shootAt(GAME_OBJECT *obj) {
//	if(allowedAttack) {
//		
//		//weapon->shoot(getAngleAt(obj), x, y);
//	}
//}