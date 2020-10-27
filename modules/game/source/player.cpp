//#include <windows.h>
//#include <math.h>
#include "player.h"
#include "physicsManager.h"

#include <iostream>
//#include "weaponManager.h"
////
////Player::Player() {
////	//COLOR red(255, 0, 0);
////
////	//WEAPON pistol(WEAPON_ATTACK_TYPE_PROJECTILES, MISSILE_VISUAL_TYPE_ELLIPSE,
////	//	1, 0.10, 10.0, 10.0, 400.0, 2.0, 10, &red, NULL);
////
////	//weapon = &pistol;
////
////}
//
//void Player::draw(HDC bhdc) {
//	//SelectObject(bhdc, *brPtr);
//	//SelectObject(bhdc, *pPtr);
//
//	const float s = size * height;
//
//	float newX = x + cameraOffsetX;
//	float newY = y + cameraOffsetY;
//
//	Ellipse(bhdc, newX-s, newY-s, newX+s, newY+s);
//
//	float X = x + size * cos(angle) +cameraOffsetX;
//	float Y = y + size * sin(angle) +cameraOffsetY;
//	float sz = size/3;
//
//	Ellipse(bhdc, X-sz, Y-sz, X+sz, Y+sz);
//
//	if(isReloading()) {
//		//SelectObject(bhdc, *reloadingPPtr);
//		MoveToEx(bhdc, newX, newY, NULL);
//		LineTo(bhdc, newX + s/2 * cos(DEGTORAD * reloadingAngle), newY + s/2 * sin(DEGTORAD * reloadingAngle));
//		//LineTo(bhdc, x + size * cos(DEGTORAD * reloadingAngle), y + size * sin(DEGTORAD * reloadingAngle));
//	}
//}
//
//void Player::attack(float fromX, float fromY, float toX, float toY,HBRUSH *b,HPEN *p) {
//	if(allowedAttack) {
//		denyShooting();
//
//		//float fromX = x + size/2 * cos(angle);
//		//float fromY = y + size/2 * sin(angle);
//
//		weapon->attack(fromX,fromY,toX,toY,b,p);
//	}
//}
//
//void Player::move(float deltaTime, const int direction) {
//	//reloading cursor
//	//--------------------
//	backupXY();
//
//	float dist = speed * deltaTime;
//	float proection = dist / sqrt(float(2));
//
//	if(direction == PLAYER_DIRECTION_N) {
//		y -= dist;
//	} else if(direction == PLAYER_DIRECTION_S) {
//		y += dist;
//	} else if(direction == PLAYER_DIRECTION_W) {
//		x -= dist;
//	} else if(direction == PLAYER_DIRECTION_E) {
//		x += dist;
//	} else if(direction == PLAYER_DIRECTION_NW) {
//		x -= proection;
//		y -= proection;
//	} else if(direction == PLAYER_DIRECTION_NE) {
//		x += proection;
//		y -= proection;
//	} else if(direction == PLAYER_DIRECTION_SE) {
//		x += proection;
//		y += proection;
//	} else if(direction == PLAYER_DIRECTION_WS) {
//		x -= proection;
//		y += proection;
//	}
//
//	//float playerSize = PLAYER_SIZE;
//
//	//if(x < PLAYER_SIZE) x = PLAYER_SIZE;
//	//if(y < PLAYER_SIZE) y = PLAYER_SIZE;
//	//if(x > RESOLUTION_X/*-playerSize*/) x = RESOLUTION_X/*-playerSize*/;
//	//if(y > RESOLUTION_Y/*-playerSize*/) y = RESOLUTION_Y/*-playerSize*/;
//}
//
////void Player::shootAt(GameObject *obj) {
////	if(allowedAttack) {
////		
////		//weapon->shoot(getAngleAt(obj), x, y);
////	}
////}

#include "keys.h"

void Player::processPhysics(float dt) {
  const auto& keys = Keyboard::instance();

	int v, h;
	v = h = 0;

	if(keys.isPressed(KEY_MOVE_LEFT)) {
		--h;
	}

	if(keys.isPressed(KEY_MOVE_RIGHT)) {
		++h;
	}

	if(keys.isPressed(KEY_MOVE_UP)) {
		--v;
	}

	if(keys.isPressed(KEY_MOVE_DOWN)) {
		++v;
	}

  float dist = speed * dt;
  float proection = dist / sqrt(float(2));

	if(!v && h < 0) {
    x -= dist;
	} else if(!v && h > 0) {
    x += dist;
	} else if(!h && v < 0) {
    y -= dist;
	} else if(!h && v > 0) {
    y += dist;
	} else if(h > 0 && v > 0) {
    x += proection;
    y += proection;
	} else if(h > 0 && v < 0) {
    x += proection;
    y -= proection;
	} else if(h < 0 && v < 0) {
    x -= proection;
    y -= proection;
	} else if(h < 0 && v > 0) {
    x -= proection;
    y += proection;
	}

  //when hero going out of last 10% of the map
  //we need to depose all game objects render coordinates
  //to imitate infinite map

  const float map_bounds_percent = 0.1f;

  const float window_width = 800.0f;
  const float window_height = 600.0f;

  const float lastX = (window_width * map_bounds_percent);
  const float lastY = (window_height * map_bounds_percent);

  const float boundsX = window_width - lastX;
  const float boundsY = window_height - lastY;

  auto& phys = PhysicsManager::instance();

  if(x > boundsX) {
    phys.deposeObjects( boundsX - x, 0.f );
  }
  if(y > boundsY) {
    phys.deposeObjects( 0.f, boundsY - y );
  }
  if(x < lastX) {
    phys.deposeObjects( lastX - x, 0.f );
  }
  if(y < lastY) {
    phys.deposeObjects( 0.f, lastY - y );
  }
}
