#include "enemyManager.h"

void ENEMY_MANAGER::process(float deltaTime) {
	float x,y,a;
	
	for(std::list<ENEMY>::iterator it=list.begin(); it!=list.end(); ++it) {
		switch(it->getAttackType()) {
		case ENEMY_ATTACK_TYPE_NONE:
			it->move(deltaTime, playerPtr->getX(), playerPtr->getY());
			break;

		default:
			if( dbo(playerPtr->itSelf(), it->itSelf())-it->getSize()-playerPtr->getSize() > it->getAttackRange()) {
				it->move(deltaTime, playerPtr->getX(), playerPtr->getY());
			} else {
				if(it->CanAttack()) {
					
					it->attack();
					x=it->getX();
					y=it->getY();
					a=abc(x,y,playerPtr->getX(),playerPtr->getY());
					it->getMissileManagerPtr()->addMissile(x,y,a,600.0,MISSILE_VISUAL_TYPE_SQUARE,MISSILE_TARGET_TYPE_HERO,2.0,1,0,0);
				} else {
					it->reloadingProcess(deltaTime);
				}
			}
			break;
		}
	}



}