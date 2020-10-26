#ifndef __ENEMY_H
#define __ENEMY_H

#include <Windows.h>
#include <math.h>
#include "misc.h"
#include "game_object.h"
#include "missileManager.h"

const int ENEMY_ROLE_NEUTRAL = 0,
	      ENEMY_ROLE_GUARD = 1;

const int ENEMY_CURRENT_TARGET_PATROL = 0,
	      ENEMY_CURRENT_TARGET_ATTACK_PLAYER = 1,
		  ENEMY_CURRENT_TARGET_SEARCH_PLAYER = 2,
		  ENEMY_CURRENT_TARGET_ESCAPE = 3;

const int ENEMY_ATTACK_TYPE_NONE = 0,
	      ENEMY_ATTACK_TYPE_MELEE = 1,
		  ENEMY_ATTACK_TYPE_RANGED = 2;

const int ENEMY_MOVING_TYPE_NONE = 0,
	      ENEMY_MOVING_TYPE_TOWARDS_HERO = 1,
	      ENEMY_MOVING_TYPE_STATIC = 2;

const int ENEMY_VISUAL_TYPE_SQUARE = 0,
	      ENEMY_VISUAL_TYPE_ELLIPSE = 1;

class ENEMY :public GameObject{
private:
	double hp;
	double hpMax;
	double attackRange;
	int currentTarget;
	int attackType;
	int movingType;
	int visualType;
	int role;
	int r, g, b;
	bool canAttack;
	double attackTime;
	double reloadingTime;
	MISSILE_MANAGER *mMan;
	HBRUSH *enemyBrush;
	HPEN *enemyPen;
	bool playerSpotted;
	bool vis;
	double toX, toY;
	bool computeTo;
	double px[40];
	double py[40];
	double PX,PY;
	bool running;

	double damageResistance;
	double woundedTime;
	bool wounded;

public:
	ENEMY(double newX, double newY, double newSpeed, double newHP,
		const int newAttackType, const int newMovingType, const int newRole, const int newVisualType, HBRUSH *newEnemyBrush, HPEN *newEnemyPen, MISSILE_MANAGER *newMMAN)
	{
		x = toX = newX;
		y = toY = newY;
		size = ENEMY_SIZE;
		speed = newSpeed;
		hp = hpMax = newHP;
		attackType = newAttackType;
		movingType = newMovingType;
		visualType = newVisualType;
		PX = PY = 0;
		reloadingTime = rand()%(int)2.0+0.5;
		attackTime = 0.0;
		canAttack = true;
		role = newRole;
		playerSpotted = true;
		computeTo = false;
		vis = false;
		running = false;

		damageResistance = 0.25;
		woundedTime = 0.0;
		wounded = false;
		currentTarget = ENEMY_CURRENT_TARGET_PATROL;

		for(int i=0;i<4;i++) {px[i]=newX; py[i]=newY;}

		switch(attackType) {
		case ENEMY_ATTACK_TYPE_NONE:
			attackRange = 0.0;
			break;

		case ENEMY_ATTACK_TYPE_MELEE:
			attackRange = ATTACK_RANGE_MELEE;
			break;

		case ENEMY_ATTACK_TYPE_RANGED:
			attackRange = ATTACK_RANGE_RANGED;
			break;
		}

		switch(role) {
		case ENEMY_ROLE_NEUTRAL:
			speed = ENEMY_NORMAL_SPEED;
			break;

		case ENEMY_ROLE_GUARD:
			speed = ENEMY_NORMAL_SPEED;
			break;
		}

	    r = g = b = 0;
		mMan = newMMAN;
		enemyBrush = newEnemyBrush;
		enemyPen = newEnemyPen;
	}

	void setPointXY(int index, double x, double y) {
		px[index] = x;
		py[index] = y;
	}

	void setPlayerCoords(double px, double py) {
		PX = px;
		PY = py;
	}

	double getCoordX(int index) {return px[index];}
	double getCoordY(int index) {return py[index];}

	void draw(HDC bhdc);
	bool checkForVisibility(void);
	
	void depose(double X, double Y) {
		x = x + X;
		y = y + Y;
		toX = toX + X;
		toY = toY + Y;

		for(int i=0;i<40;i++) {
			px[i] = px[i] + X;
			py[i] = py[i] + Y;
		}

		PX = PX + X;
		PY = PY + Y;
	}

	void faceTo(double x2, double y2) {
		angle = abc(x, y, x2, y2);
	}

	void correct(double deltaTime, double px, double py, double angle);

	void takeDamage(double damage) {
		if(!DEBUGVAR_INVULNERABLE_ENEMIES) {
			hp -= damage;
		}
		
		if (hp <= 0) {
			kill();
		} else {
			Wound(WEAPON_BASE_WOUND_TIME);
		}
	}

	void attack() {
		attackTime = reloadingTime;
		canAttack=false;
	}

	void reloadingProcess(double deltaTime) {
		attackTime -= deltaTime;
		if(attackTime<=0.0 ) {
			canAttack=true;
		}
	}

	void setTo(double X,double Y) {
		toX=X;toY=Y;
	}

	void kill(void) {alive = false;}
	void move(double deltaTime, double playerX, double playerY);
	void removeDeadEnemies(void);
	bool isAlive(void) {return alive;}
	int getAttackType(void) {return attackType;}
	double getAttackRange(void) {return attackRange;}
	MISSILE_MANAGER* getMissileManagerPtr(void) {return mMan;}
	bool CanAttack(void) {return canAttack;}
	bool isPlayerSpotted(void) {return playerSpotted;}
	int getRole(void) {return role;}
	double getToX(void) {return toX;}
	double getToY(void) {return toY;}
	int getCurrentTarget(void) {return currentTarget;}

	bool isComputedTo(void) {return computeTo;}
	void computed(void) {computeTo=true;}
	void NotComputedTo(void) {computeTo=false;}

	void run(void) {running=true; speed=ENEMY_FAST_SPEED;}
	void walk(void) {running=false; speed=ENEMY_NORMAL_SPEED;}

	bool isWounded(void) {return wounded;}
	void Wound(double time)	{
		wounded = true; woundedTime = time;
		if(running) speed = ENEMY_FAST_SPEED*damageResistance;
		else speed=ENEMY_NORMAL_SPEED*damageResistance;
	}
	void updateWound(double deltaTime) {
		woundedTime = woundedTime - deltaTime;
		if(woundedTime <= 0.0) {
			wounded = false;

			if(running) speed = ENEMY_FAST_SPEED;
			else speed=ENEMY_NORMAL_SPEED;
		}
	}

	void setCurrentTarget(const int t) {
		currentTarget=t;
		if(t==ENEMY_CURRENT_TARGET_SEARCH_PLAYER || t==ENEMY_CURRENT_TARGET_ATTACK_PLAYER) {
			computeTo=false;
		}

		if(t!=ENEMY_CURRENT_TARGET_PATROL) {
			run();
		} else {
			walk();
		}
	}
};

#endif
