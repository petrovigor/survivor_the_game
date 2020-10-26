#pragma once

const int ABILITY_CAST_TYPE_INSTANT = 0,
		  ABILITY_CAST_TYPE_SWITCH = 1,
	      ABILITY_CAST_TYPE_POINT = 2,
		  ABILITY_CAST_TYPE_TARGET = 3,
		  ABILITY_CAST_TYPE_CHANNELING = 4;

const int ABILITY_CAST_REQUIREMENT_NONE = 0,
	      ABILITY_CAST_REQUIREMENT_FREE_POINT = 1;

const int ABILITY_TARGET_TYPE_NONE = 0;

const int ABILITY_ID_BLINK = 0,
	      ABILITY_ID_TIME_SLOW = 1;

class ABILITY {
private:
	int abilityId;
	int castType;
	int targetType;

	double maxCastTime;
	double castTime;
	int manaCost;
	int cooldown;
	bool switchFlag;

	double targetX;
	double targetY;

	double arg1,arg2,arg3;

	bool targeting;
	bool casting;

public:
	ABILITY(const int newAbilityId, const int newCastType, const int newTargetType, int newManaCost, int newCoolDown, double newCastTime) {
		abilityId = newAbilityId;
		castType = newCastType;
		targetType = newTargetType;
		manaCost = newManaCost;
		cooldown = newCoolDown;
		maxCastTime = newCastTime;
		castTime = targetX = targetY = arg1 = arg2 = arg3 = 0.00;
		switchFlag = false;
		casting = false;
		targeting = false;
	}

	~ABILITY() {};

	//write access
	void startCasting(double x, double y) {casting = true; castTime=0.00; targetX=x; targetY=y;}
	void increaseCastingTime(double deltaTime) {castTime+=deltaTime;}
	void CastingEnd(void) {casting = false;}
	void startTargeting(void) {targeting = true;}
	void endTargeting(void) {targeting = false;}

	//read access
	int getAbilityId(void) {return abilityId;}
	double getCastingTime(void) {return maxCastTime;}
	double currentCastTime(void) {return castTime;}

	double getPointX(void) {return targetX;}
	double getPointY(void) {return targetY;}

	bool isCasting(void) {return casting;}
	bool isTargeting(void) {return targeting;}
};
