//#ifndef ___PROJECTILE_H
//#define ___PROJECTILE_H
//
//#include "gameObject.h"
//
//const int PROJ_MOVING_TYPE_STRAIGHT = 0,
//	      PROJ_MOVING_TYPE_BOUNCE = 1, //hard to programming this, but would be cool
//          PROJ_MOVING_TYPE_INSTANT = 2;
//
//const int PROJ_TARGET_TYPE_ENEMIES = 0,
//	      PROJ_TARGET_TYPE_HERO = 1;
//
//const int PROJ_VISUAL_TYPE_SQUARE = 0,
//	      PROJ_VISUAL_TYPE_CIRCLE = 1;
//
//class PROJECTILE:public GAME_OBJECT {
//private:
//	int movingType;
//	int targetType;
//	int visualType;
//	double minDamage;
//	double maxDamage;
//	bool flag;
//
//public:
//	PROJECTILE(int newMovingType, int newTargetType, int newVisualType, double newMinDamage, double newMaxDamage) {
//		flag = true;
//		movingType = newMovingType;
//		targetType = newTargetType;
//		visualType = newVisualType;
//		minDamage = newMinDamage;
//		maxDamage = newMaxDamage;
//	}
//
//	void draw(); //HDC hbdc
//
//	//read access
//	int getMovingType(void) {return movingType;}
//	int getTargetType(void) {return targetType;}
//	int getVisualType(void) {return visualType;}
//
//	//write access
//	void setMovingType(int newMovingType) {movingType = newMovingType;}
//	void setTargetType(int newTargetType) {targetType = newTargetType;}
//	void setVisualType(int newVisualType) {visualType = newVisualType;}
//};
//
//#endif