#include "eventManager.h"

const int SIDE_LEFT = 0,
	      SIDE_RIGHT = 1,
		  SIDE_BOTTOM = 2,
		  SIDE_TOP = 3;

void EVENT_MANAGER::increaseEnemyMultiplier(void) {
	if(DEBUGVAR_INCLUDE_ENEMY_MULTIPLIER) {
		enemyManPtr->increaseMultiplier();
	}
}

void EVENT_MANAGER::allowCasting(void) {
	playerPtr->allowCasting();
}

void EVENT_MANAGER::spawnEnemy() {
	int n;
	int m=enemyManPtr->getEnemyMultiplier();

	if(m>0) {
		n=rand()%m+1;
	} else {
		n=1;
	}

	for(int i=0;i<n;i++) {
		double x,y,X,Y;
		double px=playerPtr->getX(),
			   py=playerPtr->getY();

		double minDist=400.0;

		//do {
		//	x=rand()%RESOLUTION_X;
		//	y=rand()%RESOLUTION_Y;
		//} while(!(dbc(x,y,px,py)>minDist || phy->isPointFree(x,y,ENEMY_SIZE)));
	
		do {
			x=rand()%RESOLUTION_X;
			y=rand()%RESOLUTION_Y;

			if(rand()%2==0) X=px+x;
			else X=px-x;

			if(rand()%2==0) Y=py+y;
			else Y=py-y;
		} while(dbc(X,Y,px,py)<=minDist || !phy->isPointFree(X,Y,ENEMY_SIZE));

		enemyManPtr->add(X, Y, ENEMY_NORMAL_SPEED, 1, ENEMY_ATTACK_TYPE_NONE, ENEMY_MOVING_TYPE_TOWARDS_HERO, rand()%2/*ENEMY_ROLE_GUARD*/, ENEMY_VISUAL_TYPE_ELLIPSE);
	}
}

//void EVENT_MANAGER::spawnEnemy(void) {
//	//int n = rand()%enemyManPtr->getEnemyMultiplier()+1;
//
//	int n;
//	int m=enemyManPtr->getEnemyMultiplier();
//
//	if(m>0) {
//		n=rand()%m+1;
//	} else {
//		n=1;
//	}
//
//	//int n = rand()%enemyManPtr->getEnemyMultiplier()
//
//	int r;
//	double px = playerPtr->getX(), py = playerPtr->getY();
//
//	// center -> random 4 sides
//	if( px<RESOLUTION_X-PLAYER_OUT_OF_MAP_SAFE_OFFSET && py<RESOLUTION_Y-PLAYER_OUT_OF_MAP_SAFE_OFFSET && px>PLAYER_OUT_OF_MAP_SAFE_OFFSET && py>PLAYER_OUT_OF_MAP_SAFE_OFFSET ) {
//		r = rand()%4;
//	// left -> right,bottom,top
//	} else if( px<PLAYER_OUT_OF_MAP_SAFE_OFFSET*3.0) {
//		while(true) {
//			r = rand()%4;
//			if(r != SIDE_LEFT) break;
//		}
//	// right -> left,bottom,top
//	} else if( px>RESOLUTION_X-PLAYER_OUT_OF_MAP_SAFE_OFFSET*3.0) {
//		while(true) {
//			r = rand()%4;
//			if(r != SIDE_RIGHT) break;
//		}
//	// top -> right,bottom,left
//	} else if( py<PLAYER_OUT_OF_MAP_SAFE_OFFSET*3.0) {
//		while(true) {
//			r = rand()%4;
//			if(r != SIDE_TOP) break;
//		}
//	// bottom -> right,left,top
//	} else if( py>RESOLUTION_Y-PLAYER_OUT_OF_MAP_SAFE_OFFSET*3.0) {
//		while(true) {
//			r = rand()%4;
//			if(r != SIDE_BOTTOM) break;
//		}
//	}
//
//	double safeOffset = 0.0; //50
//
//	for(int i=0; i<n; i++) {
//		//int r=rand()%4;
//		double x, y;
//
//		switch(r) {
//		case SIDE_TOP:
//			x = rand()%RESOLUTION_X;
//			y = -safeOffset;
//			break;
//
//		case SIDE_BOTTOM:
//			x = rand()%RESOLUTION_X;
//			y = RESOLUTION_Y + safeOffset;
//			break;
//
//		case SIDE_LEFT:
//			x = -safeOffset;
//			y = rand()%RESOLUTION_Y;
//			break;
//
//		case SIDE_RIGHT:
//			x = RESOLUTION_X + safeOffset;
//			y = rand()%RESOLUTION_Y;
//			break;
//		}
//
//		enemyManPtr->add(x, y, 50+rand()%(n*10)/*rand()%10+20*/, rand()%(int)2+1, rand()%2+1/*ENEMY_ATTACK_TYPE_NONE*/, ENEMY_MOVING_TYPE_TOWARDS_HERO, ENEMY_VISUAL_TYPE_ELLIPSE);
//	}
//}

void EVENT_MANAGER::updateEvents(double deltaTime) {
	for(std::vector<EVENT>::iterator i=eventList.begin(); i!=eventList.end(); ++i) {
		if(i->getDuration() >= i->getLastingTime()) {
			execute(*i);
			
			switch(i->getEventType()) {
			case EVENT_TYPE_INFINITE:
				i->startAgain();
				break;

			case EVENT_TYPE_SIMPLE:
				i->completeEvent();
				break;
			}
		}

		i->increaseTime(deltaTime);
	}

	std::vector<EVENT>::iterator i = eventList.begin();
	while(i!=eventList.end()) {
		if(i->isCompleted()) {
			eventList.erase(i);
			i=eventList.begin();
		} else {
			++i;
		}
	}
}