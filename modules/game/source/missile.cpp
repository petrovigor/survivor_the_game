//#include "missile.h"
//#include <math.h>
//
//MISSILE::MISSILE(float newX, float newY, float newSpeed, float newDamage, float newAngle, const int newTargetType, float newMissileSize, int newPenCount, HBRUSH *newBrush, HPEN *newPen) {
//	x = newX;
//	y = newY;
//	speed = newSpeed;
//	angle = newAngle;
//	size = newMissileSize;
//	targetType = newTargetType;
//	damage = newDamage;
//	penCount = newPenCount;
//	flag = true;
//	br=newBrush;
//	pn=newPen;
//}
//
//void MISSILE::pen() {
//  penCount--;
//}
//
//int MISSILE::getPenCount() {
//  return penCount;
//}
//
//void MISSILE::setMissileUnused() {
//	flag = false;
//}
//
//bool MISSILE::isUnused() {
//	return !flag;
//}
//
//float MISSILE::getX() {
//  return x;
//}
//
//float MISSILE::getY() {
//  return y;
//}
//
//float MISSILE::getDamage() {
//  return damage;
//}
//
//int MISSILE::getTargetType() {
//  return targetType;
//}
