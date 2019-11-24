#include "physicsManager.h"

double intersectCoords[DEBUGVAR_INTERSECTS_COUNT_MAX];
int count;

bool PHYSICS_MANAGER::checkForPlacementCollision(double X,double Y,double W,double H) {
	bool free=true;

	for(std::list<BLOCK>::iterator it=blocksList.begin(); it!=blocksList.end(); ++it) {
		if(it->rectCollision(X,Y,W,H)) {
			free=false;
		}
	}

	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
		double x = i->getX();
		double y = i->getY();
		double w = i->getSize();
		double h = i->getSize();
		//bool BLOCK::rectCollision(double X, double Y, double W, double H) {
		//return ;
		//}

		if( i->isAlive() && 
			X-W<x+w/2 && Y-H<y+h/2 && X+W>x-w/2 && Y+H>y-h/2 ) {
			free=false;
		}
		
		
		//if((i->isAlive())&&(i->distance(go)<i->getSize()+go->getSize())) {
		//	free=false;
		//}
	}

	return free;
}

bool PHYSICS_MANAGER::checkForPlacementCollision(GameObject *go) {
	const bool checkForBlocksCollision = true;
	
	if(go!=playerPtr) {
		if(playerPtr->distance(go)<playerPtr->getSize()+go->getSize()) {
			return(true);
		}
	}
	
	if(checkForBlocksCollision) {
		for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
			if(i->isCoordInBlock(go->getX(),go->getY(),go->getSize())) {
				return(true);
			}
			
			//if(i->isGOinBlock(go->itSelf())) {
			//	return(true);
			//}
		}
	}

	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
		if((i->itSelf()!=go)&&(i->isAlive())&&(i->distance(go)<i->getSize()+go->getSize())) {
			return(true);
		}
	}

	return(false);
}

void PHYSICS_MANAGER::processNoises(double deltaTime) {
	for(std::vector<NOISE>::iterator i=noisesVector.begin(); i!=noisesVector.end(); ++i) {
		i->increaseNoiseRadius(deltaTime);
		for(std::list<ENEMY>::iterator j=enemiesList->begin(); j!=enemiesList->end(); ++j) {

			//double d = /* - j->getSize()*/;


			if(   dbc(    i-> getX(), i-> getY(), j-> getX(), j-> getY()    )   <=  i->getRadius()   ) {

				if(j->getCurrentTarget()==ENEMY_CURRENT_TARGET_PATROL) {
					if(j->getRole()==ENEMY_ROLE_GUARD) {
						j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
					} else {
						j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
					}
				}

				//switch(j->getRole()) {
				//	case ENEMY_ROLE_NEUTRAL:
				//	switch(j->getCurrentTarget()) {
				//		case ENEMY_CURRENT_TARGET_PATROL:
				//		j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
				//		break;
				//	}
				//	break;
				//	case ENEMY_ROLE_GUARD:
				//	switch(j->getCurrentTarget()) {
				//		case ENEMY_CURRENT_TARGET_PATROL:
				//		if(!isVision(playerPtr,j->itSelf(),intersectCoords,&count)) {
				//			j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
				//		} else {
				//			j->setCurrentTarget(ENEMY_CURRENT_TARGET_ATTACK_PLAYER);
				//		}
				//		break;
				//	}
				//	break;
				//}

			}
		}
	}
}

void PHYSICS_MANAGER::moveMissiles(double deltaTime) {
	for(std::list<MISSILE>::iterator i=missilesList->begin(); i!=missilesList->end(); ++i) {
		i->move(deltaTime);
	}
}

void PHYSICS_MANAGER::movePlayer(double deltaTime, const int playerDir) {
	playerPtr->move(deltaTime, playerDir);
}

bool PHYSICS_MANAGER::isPointFree(double X, double Y, double R = 0) {
	bool r = true;

	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
		if(dbc(i->getX(), i->getY(), X, Y)<i->getSize()) {
			r = false;
		}
	}

	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
		if(i->isCoordInBlock(X,Y,R)) {
			r = false;
		}
	}

	return r;
}

bool PHYSICS_MANAGER::isVision(GameObject *A, GameObject *B) {
	double ax = A->getX();
	double ay = A->getY();
	double bx = B->getX();
	double by = B->getY();
	
	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
		if(i->checkForIntersection(ax,ay,bx,by)) {
			return(true);
		}
	}

	return false;
}

int PHYSICS_MANAGER::isVisionSmart(GameObject *A, GameObject *B, double *coords, int *count) {
	//bool vis = true;

	int r = -1;
	double ax = A->getX();
	double ay = A->getY();
	double bx = B->getX();
	double by = B->getY();
	
	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {

		//if() {
			
			
			r = i->checkForIntersection(ax,ay,bx,by,coords,count);
			if( r != -1 ) break;

			//vis = false;
		//}

	}

	return r;
	//return vis;
}

//void PHYSICS_MANAGER::offset(std::list<BLOCK>::iterator it) {
//
//}

void PHYSICS_MANAGER::enemyMoveTo(std::list<ENEMY>::iterator it, double deltaTime, double X, double Y) {

	
	
	it->move(deltaTime, X, Y);

	//for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
	//	i->offset(it);
	//}

	//if(checkForPlacementCollision(it->itSelf())) {
	//	it->restoreXY();
	//}

	double tx,ty;
	int t=it->getCurrentTarget();

	if(t==ENEMY_CURRENT_TARGET_ATTACK_PLAYER) {
		tx = playerPtr->getX();
		ty = playerPtr->getY();

		if(checkForPlacementCollision(it->itSelf())) {
			it->restoreXY();

			int a=180;
			double d=dbc(tx,ty,it->getX(),it->getY());//it->distance(playerPtr);

			for(int j=0; j<360; j+=10) {
				it->correct(deltaTime, X, Y, j);
				if(!checkForPlacementCollision(it->itSelf())) {
					if(dbc(tx,ty,it->getX(),it->getY())<d) {
						d=dbc(tx,ty,it->getX(),it->getY());
						a=j;
					}
				}
			}

			if(a!=180) {
				it->correct(deltaTime, X, Y, a);
			} else {
				it->restoreXY();
			}
		}


	} else {
		tx = it->getToX();
		ty = it->getToY();

		if(checkForPlacementCollision(it->itSelf())) {
			it->restoreXY();

			int a=180;
			//double d=dbc(tx,ty,it->getX(),it->getY());//it->distance(playerPtr);

			for(int j=0; j<360; j+=10) {
				it->correct(deltaTime, X, Y, j);
				if(!checkForPlacementCollision(it->itSelf())) {
					//if(dbc(tx,ty,it->getX(),it->getY())<d) {
						//d=dbc(tx,ty,it->getX(),it->getY());
						a=j;
					//}
				}
			}

			if(a!=180) {
				it->correct(deltaTime, X, Y, a);
			} else {
				it->restoreXY();
			}
		}
	}

	// rewrite this moment
	//if(checkForPlacementCollision(it->itSelf())) {
	//	it->restoreXY();

	//	int a=180;
	//	//double d=dbc(tx,ty,it->getX(),it->getY());//it->distance(playerPtr);

	//	for(int j=0; j<360; j+=36) {
	//		it->correct(deltaTime, X, Y, j);
	//		if(!checkForPlacementCollision(it->itSelf())) {
	//			//if(dbc(tx,ty,it->getX(),it->getY())<d) {
	//				//d=dbc(tx,ty,it->getX(),it->getY());
	//				a=j;
	//			//}
	//		}
	//	}

	//	if(a!=180) {
	//		it->correct(deltaTime, X, Y, a);
	//	} else {
	//		it->restoreXY();
	//	}
	//}


	//switch(it->getCurrentTarget()) {
	//case ENEMY_CURRENT_TARGET_PATROL:
	//	tx = it->getToX();
	//	ty = it->getToY();
	//	break;
	//}

	//double tx = it->getToX(),
	//	   ty = it->getToY();

	//if(it->getCurrentTarget() == ENEMY_CURRENT_TARGET_ATTACK_PLAYER) {
		//if(checkForPlacementCollision(it->itSelf())) {
		//	it->restoreXY();

		//	int a=180;
		//	double d=it->distance(playerPtr);

		//	for(int j=0; j<360; j+=30) {
		//		it->correct(deltaTime, X, Y, j);
		//		if(!checkForPlacementCollision(it->itSelf())) {
		//			if(it->distance(playerPtr)<d) {
		//				d=it->distance(playerPtr);
		//				a=j;
		//			}
		//		}
		//	}

		//	if(a!=180) {
		//		it->correct(deltaTime,  X, Y, a);
		//	} else {
		//		it->restoreXY();
		//	}
	//	}
	//} else if(it->getCurrentTarget() == ENEMY_CURRENT_TARGET_SEARCH_PLAYER ||
		//it->getCurrentTarget() == ENEMY_CURRENT_TARGET_ESCAPE ||
		//it->getCurrentTarget() == ENEMY_CURRENT_TARGET_PATROL) {

		//if(checkForPlacementCollision(it->itSelf())) {
		//	it->restoreXY();

		//	int a=180;
		//	double d=dbc(tx,ty,it->getX(),it->getY());//it->distance(playerPtr);

		//	for(int j=0; j<360; j+=30) {
		//		it->correct(deltaTime, X, Y, j);
		//		if(!checkForPlacementCollision(it->itSelf())) {
		//			if(dbc(tx,ty,it->getX(),it->getY())<d) {
		//				d=dbc(tx,ty,it->getX(),it->getY());
		//				a=j;
		//			}
		//		}
		//	}

		//	if(a!=180) {
		//		it->correct(deltaTime,  X, Y, a);
		//	} else {
		//		it->restoreXY();
		//	}
		//}
	//}


}

//bool PHYSICS_MANAGER::isRectCollision(double X, double Y, double W, double H) {
//	bool b = false;
//	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
//		double x = i->getX();
//		double y = i->getY();
//		b = X-W<x+w/2 && Y-H<y+h/2 && X+W>x-w/2 && Y+H>y-h/2
//	}
//
//	return X-W<x+w/2 && Y-H<y+h/2 && X+W>x-w/2 && Y+H>y-h/2;
//}

bool isRectCollision(double X,double Y,double x,double y,double w,double h) {
	//XY - 1; xywh - 2
	return X<x+w/2 && Y<y+h/2 && X>x-w/2 && Y>y-h/2;
}

//void PHYSICS_MANAGER::findWayToPlayer(std::list<ENEMY>::iterator it, double px, double py) {
//
//}

void PHYSICS_MANAGER::computeRandomPointToPatrol(std::list<ENEMY>::iterator it) {
	double _x,_y;
	do {
		_x=rand()%RESOLUTION_X;
		_y=rand()%RESOLUTION_Y;
	} while(!(isPointFree(_x,_y,it->getSize())));
	it->setTo(_x,_y);
}

void PHYSICS_MANAGER::processEnemies(double deltaTime) {
	double px = playerPtr->getX(),
		   py = playerPtr->getY();

	double _x,_y,_a;
	int side;

	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
		if(i->isAlive()) {
			
			///================///================///================///================

			if(DEBUGVAR_ALLOW_ENEMIES_SEE_EACH_OTHER) {
				for(std::list<ENEMY>::iterator j=enemiesList->begin(); j!=enemiesList->end(); ++j) {
					if(i!=j) {
						int it = i->getCurrentTarget();
						int jt = j->getCurrentTarget();
						int ir = i->getRole();
						int jr = j->getRole();
						
						if(ir==ENEMY_ROLE_GUARD) {
							if(isVision(i->itSelf(),j->itSelf()) && (it==ENEMY_CURRENT_TARGET_SEARCH_PLAYER || it==ENEMY_CURRENT_TARGET_ATTACK_PLAYER)) {
								if(jt==ENEMY_CURRENT_TARGET_PATROL) {
									if(j->getRole()==ENEMY_ROLE_GUARD) {
										j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
									} else if(j->getRole()==ENEMY_ROLE_NEUTRAL) {
										j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
									}
								}
							}
						} else {
							if(isVision(i->itSelf(),j->itSelf()) && it==ENEMY_CURRENT_TARGET_ESCAPE) {
								if(jt==ENEMY_CURRENT_TARGET_PATROL) {
									if(j->getRole()==ENEMY_ROLE_GUARD) {
										j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
									} else if(j->getRole()==ENEMY_ROLE_NEUTRAL) {
										j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
									}
								}
							}
						}

						//if(isVision(i->itSelf(),j->itSelf()) && (it==ENEMY_CURRENT_TARGET_SEARCH_PLAYER || it==ENEMY_CURRENT_TARGET_ATTACK_PLAYER)) {
						//	if(jt==ENEMY_CURRENT_TARGET_PATROL) {
						//		if(j->getRole()==ENEMY_ROLE_GUARD) {
						//			j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
						//		} else if(j->getRole()==ENEMY_ROLE_NEUTRAL) {
						//			j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
						//		}
						//	}
						//}
					}
				}
			}

			///================///================///================///================

			if(i->isWounded()) {
				i->updateWound(deltaTime);
			}

			double x = i->getX();
			double y = i->getY();

			switch(i->getCurrentTarget()) {
				case ENEMY_CURRENT_TARGET_PATROL:
					if(dbc(x,y,i->getToX(),i->getToY())<i->getSize()) {
						computeRandomPointToPatrol(i);
					} else {
						enemyMoveTo(i,deltaTime,i->getToX(),i->getToY());
					}
					break;

				case ENEMY_CURRENT_TARGET_SEARCH_PLAYER:
					count = 0;
					side = isVisionSmart(i->itSelf(), playerPtr, intersectCoords, &count);

					if(side == -1) {
						i->setCurrentTarget(ENEMY_CURRENT_TARGET_ATTACK_PLAYER);
						//i->NotComputedTo();
					} else {
						if(!i->isComputedTo()) {
							double lx1 = intersectCoords[0],
									ly1 = intersectCoords[1];
							double lx2 = intersectCoords[2],
									ly2 = intersectCoords[3];
							double lx3 = intersectCoords[4],
									ly3 = intersectCoords[5];
							double lx4 = intersectCoords[6],
									ly4 = intersectCoords[7];

							i->setPointXY(0, lx1, ly1);
							i->setPointXY(1, lx2, ly2);
							i->setPointXY(2, lx3, ly3);
							i->setPointXY(3, lx4, ly4);

							double a;
							double s = i->getSize()*2;

							double cx = (lx1+lx2)/2,
									cy = (ly1+ly2)/2;
							double cx2 = (lx3+lx4)/2,
									cy2 = (ly3+ly4)/2;

							if(DEBUGVAR_INCLUDE_ENEMIES_VISION) {
								if(dbc(x,y,cx,cy)<dbc(x,y,cx2,cy2)) {
									i->setPlayerCoords(cx,cy);
								} else {
									i->setPlayerCoords(cx2,cy2);
								}
							}

							// not absolutely right algorithm
							// rewrite when will free of other coding
							// 45 degress not only to +
							// so to - too
							// compute this later

							if(dbc(cx,cy,x,y)<dbc(cx2,cy2,x,y)) {
								if(dbc(px,py,lx1,ly1)<dbc(px,py,lx2,ly2)) {
									a=abc(lx2,ly2,lx1,ly1)     +45*DEGTORAD;
									i->setTo(lx1+s*cos(a),ly1+s*sin(a));
								} else {
									a=abc(lx1,ly1,lx2,ly2)     +45*DEGTORAD;
									i->setTo(lx2+s*cos(a),ly2+s*sin(a));
								}
							} else {
								if(dbc(px,py,lx3,ly3)<dbc(px,py,lx4,ly4)) {
									a=abc(lx4,ly4,lx3,ly3)     +45*DEGTORAD;
									i->setTo(lx3+s*cos(a),ly3+s*sin(a));
								} else {
									a=abc(lx3,ly3,lx4,ly4)     +45*DEGTORAD;
									i->setTo(lx4+s*cos(a),ly4+s*sin(a));
								}
							}

							i->computed();
						} else {
							if(dbc(x,y,i->getToX(),i->getToY())>i->getSize()/2) {
								enemyMoveTo(i, deltaTime, i->getToX(), i->getToY());
							} else {
								i->NotComputedTo();
							}
						}
					}
					break;

				case ENEMY_CURRENT_TARGET_ATTACK_PLAYER:
					//i->run();

					side = isVisionSmart(i->itSelf(), playerPtr, intersectCoords, &count);

					if(side == -1) {
						if(i->distance(playerPtr) > i->getSize()+playerPtr->getSize()+ATTACK_RANGE_MELEE) {
							enemyMoveTo(i,deltaTime,px,py);
						}
					} else {
						i->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
					}
					break;

				case ENEMY_CURRENT_TARGET_ESCAPE:
					_a = abc(px, py, x,y);
					_x=px + FAR_DISTANCE*2 * cos(_a), _y=py + FAR_DISTANCE*2 * sin(_a);
					enemyMoveTo(i,deltaTime,_x,_y);
					break;
			}

			if(i->distance(playerPtr) > FAR_DISTANCE) {
				i->kill();
			}
		}
	}
}

void PHYSICS_MANAGER::removeFarBlocks(double X, double Y, double d) {
	for(std::list<BLOCK>::iterator it=blocksList.begin(); it!=blocksList.end(); ++it) {
		if(dbc(X,Y,it->getX(),it->getY())>d) {
			it->toDelete();
		}
	}

	std::list<BLOCK>::iterator it=blocksList.begin();
	while(it!=blocksList.end()) {
		if(it->isToDelete()) {
			blocksList.erase(it); it=blocksList.begin();
		} else ++it;
	}
}

void PHYSICS_MANAGER::removeNoises(void) {
	std::vector<NOISE>::iterator it=noisesVector.begin();
	while(it!=noisesVector.end()) {
		if(it->isToDelete()) {
			noisesVector.erase(it);
			it=noisesVector.begin();
		} else {
			++it;
		}
	}
}

void PHYSICS_MANAGER::setCameraOffsetValue(double X, double Y) {
	offsetFromCenterX = X;
	offsetFromCenterY = Y;
}

void PHYSICS_MANAGER::deposeGameObjectsFromCenter(/*double offsetX, double offsetY*/) {
	//offsetFromCenterX = offsetX;
	//offsetFromCenterY = offsetY;
	
	double offsetX1 = offsetFromCenterX,
		     offsetY1 = offsetFromCenterY;

	for(std::list<BLOCK>::iterator it=blocksList.begin(); it!=blocksList.end(); ++it) {
		it->setCameraOffset(offsetX1,offsetY1);
	}
	for(std::list<ENEMY>::iterator it=enemiesList->begin(); it!=enemiesList->end(); ++it) {
		it->setCameraOffset(offsetX1,offsetY1);
	}
	for(std::list<MISSILE>::iterator it=missilesList->begin(); it!=missilesList->end(); ++it) {
		it->setCameraOffset(offsetX1,offsetY1);
	}
	for(std::vector<NOISE>::iterator it=noisesVector.begin(); it!=noisesVector.end(); ++it) {
		it->setCameraOffset(offsetX1,offsetY1);
	}
	fxPtr->setCameraOffset(offsetX1,offsetY1);
	playerPtr->setCameraOffset(offsetX1,offsetY1);
}

void PHYSICS_MANAGER::deposeGameObjects(double X, double Y) {
	for(std::list<BLOCK>::iterator it=blocksList.begin(); it!=blocksList.end(); ++it) {
		it->depose(X, Y);
	}

	for(std::list<ROAD>::iterator it=roadsList.begin(); it!=roadsList.end(); ++it) {
		it->depose(X, Y);
	}

	for(std::list<ENEMY>::iterator it=enemiesList->begin(); it!=enemiesList->end(); ++it) {
		it->depose(X, Y);
	}

	//for(std::list<SHELL>::iterator it=shells.begin(); it!=shells->end(); ++it) {
	//	it->depose(X, Y);
	//}
	deposeNoises(X, Y);
	fxPtr->depose(X, Y);
}

// функция проверяет, пересекаются ли координаты новой дороги с постройками
bool PHYSICS_MANAGER::col(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	double rx[4]={x1,x2,x3,x4};
	double ry[4]={y1,y2,y3,y4};

	for(std::list<BLOCK>::iterator it=blocksList.begin();it!=blocksList.end();++it) {

		//for(int i=0;i<4;i++) {
		//	if(isIntersection(rx[i],ry[i],rx[j],ry[j],) {
		//		return true;
		//	}
		//}
	}

	return false;
}

void PHYSICS_MANAGER::placeRoadByPlayerDirection(const int playerDir) {
	const double offset = 50.0;
	const double maxX = RESOLUTION_X+offset;
	const double maxY = RESOLUTION_Y;
	const double minX = -offset;
	const double minY = -offset;
	
	double ax,ay,bx,by;
	double cx,cy,dx,dy;

	ax=ay=bx=by=cx=cy=dx=dy=0.0;

	double roadSize = 50;

	switch(playerDir) {
	case PLAYER_DIRECTION_E:
		ax = maxX;
		ay = minY;
		bx = maxX;
		by = maxY;
		cx = ax + roadSize;
		cy = ay;
		dx = bx + roadSize;
		dy = by;
		
		if(!col(ax,ay,bx,by,dx,dy,cx,cy)) {
			createRoad(ax,ay,bx,by,cx,cy,dx,dy);
		}
		break;
	case PLAYER_DIRECTION_W:
		ax = minX;
		ay = minY;
		bx = minX;
		by = maxY;
		cx = ax - roadSize;
		cy = ay;
		dx = bx - roadSize;
		dy = by;
		if(!col(ax,ay,bx,by,dx,dy,cx,cy)) {
			createRoad(ax,ay,bx,by,cx,cy,dx,dy);
		}
		break;
	case PLAYER_DIRECTION_N:
		ax = minX;
		ay = minY;
		bx = maxX;
		by = minY;
		cx = ax;
		cy = ay - roadSize;
		dx = bx;
		dy = by - roadSize;
		if(!col(ax,ay,bx,by,dx,dy,cx,cy)) {
			createRoad(ax,ay,bx,by,cx,cy,dx,dy);
		}
		break;
	case PLAYER_DIRECTION_S:
		ax = minX;
		ay = maxY;
		bx = maxX;
		by = maxY;
		cx = ax;
		cy = ay + roadSize;
		dx = bx;
		dy = by + roadSize;
		if(!col(ax,ay,bx,by,dx,dy,cx,cy)) {
			createRoad(ax,ay,bx,by,cx,cy,dx,dy);
		}
		break;
	}
}

void PHYSICS_MANAGER::placeBlockByPlayerDirection(const int playerDir) {
	const double offset = 50.0;
	const double maxX = RESOLUTION_X+offset;
	const double maxY = RESOLUTION_Y;
	const double minX = -offset;
	const double minY = -offset;
	
	double x,y;
	double px = playerPtr->getX(), py = playerPtr->getY();
	double a;

	switch(playerDir) {
	case PLAYER_DIRECTION_E:
		x=maxX;
		y=rand()%(int)maxY;
		break;
	case PLAYER_DIRECTION_W:
		x=minX;
		y=rand()%(int)maxY;
		break;
	case PLAYER_DIRECTION_N:
		x=rand()%(int)maxX;
		y=minY;
		break;
	case PLAYER_DIRECTION_S:
		x=rand()%(int)maxX;
		y=maxX;
		break;
	case PLAYER_DIRECTION_NW:
		x=minX;
		y=minY;
		break;
	case PLAYER_DIRECTION_NE:
		x=maxX;
		y=minY;
		break;
	case PLAYER_DIRECTION_SE:
		x=maxX;
		y=maxY;
		break;
	case PLAYER_DIRECTION_WS:
		x=minX;
		y=maxY;
		break;
	default:
		x=y=0;
		break;
	}

	double w=rand()%100+50,h=rand()%100+50;

	if(checkForPlacementCollision(x,y,w,h)) {
		placeBlock(x,y,w,h);
	}
}

void PHYSICS_MANAGER::moveAll(double deltaTime, const int playerDir) {
	movePlayer(deltaTime, playerDir);

	if(checkForPlacementCollision(playerPtr)) {
		correctPlayerPlacement(playerDir, deltaTime);
	}

	if(DEBUGVAR_ALLOW_INFINITE_MAP) {
		// depose blocks
		const double safe = PLAYER_OUT_OF_MAP_SAFE_OFFSET;
		if(playerPtr->getX() > RESOLUTION_X - safe) {
			deposeGameObjects((RESOLUTION_X-safe)-playerPtr->getX(),0.00);
			playerPtr->setXY((RESOLUTION_X-safe),playerPtr->getY());
			if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
				placeBlockByPlayerDirection(playerDir);
			}

			if(getRoadsCount() < MAXIMAL_ROADS_AT_MAP) {
				placeRoadByPlayerDirection(playerDir);
			}
		}
		if(playerPtr->getY() > RESOLUTION_Y - safe) {
			deposeGameObjects(0.0,(RESOLUTION_Y-safe)-playerPtr->getY());
			playerPtr->setXY(playerPtr->getX(),(RESOLUTION_Y-safe));
			if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
				placeBlockByPlayerDirection(playerDir);
			}

			if(getRoadsCount() < MAXIMAL_ROADS_AT_MAP) {
				placeRoadByPlayerDirection(playerDir);
			}
		}
		if(playerPtr->getX() < safe) {
			deposeGameObjects(safe-playerPtr->getX(),0.00);
			playerPtr->setXY((safe),playerPtr->getY());
			
			if(getRoadsCount() < MAXIMAL_ROADS_AT_MAP) {
				placeRoadByPlayerDirection(playerDir);
			}

			if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
				placeBlockByPlayerDirection(playerDir);
			}
		}
		if(playerPtr->getY() < safe) {
			deposeGameObjects(0.0,safe-playerPtr->getY());
			playerPtr->setXY(playerPtr->getX(),(safe));
			if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
				placeBlockByPlayerDirection(playerDir);
			}

			if(getRoadsCount() < MAXIMAL_ROADS_AT_MAP) {
				placeRoadByPlayerDirection(playerDir);
			}
		}

		//*create dynamic map
		//if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
		//	placeBlockByPlayerDirection(playerDir);
		//}

		removeFarBlocks(playerPtr->getX(),playerPtr->getY(),FAR_DISTANCE);
	} else {
		if(playerPtr->getX() > RESOLUTION_X || playerPtr->getY() > RESOLUTION_Y || playerPtr->getX()<0 || playerPtr->getY()<0 ) {
			playerPtr->restoreXY();
		}
	}

	moveMissiles(deltaTime);
	processEnemies(deltaTime);

	//mMan.move(deltaTime*timeFactor);
	//player.move(deltaTime*timeFactor, keys.getPlayerDirection());
	//enemyMan.process(deltaTime*timeFactor);
}

void PHYSICS_MANAGER::correctPlayerPlacement(const int playerDir, double deltaTime) {
	playerPtr->restoreXY();

	switch(playerDir) {
		case PLAYER_DIRECTION_N: {
			playerPtr->move(deltaTime, PLAYER_DIRECTION_NW);
			if(checkForPlacementCollision(playerPtr)) {
				playerPtr->restoreXY();
				playerPtr->move(deltaTime, PLAYER_DIRECTION_NE);
				if(checkForPlacementCollision(playerPtr)) {
					playerPtr->restoreXY();
				}
			}
			break;
		}
		case PLAYER_DIRECTION_E: {
			playerPtr->move(deltaTime, PLAYER_DIRECTION_NE);
			if(checkForPlacementCollision(playerPtr)) {
				playerPtr->restoreXY();
				playerPtr->move(deltaTime, PLAYER_DIRECTION_SE);
				if(checkForPlacementCollision(playerPtr)) {
					playerPtr->restoreXY();
				}
			}
			break;
		}
		case PLAYER_DIRECTION_S: {
			playerPtr->move(deltaTime, PLAYER_DIRECTION_WS);
			if(checkForPlacementCollision(playerPtr)) {
				playerPtr->restoreXY();
				playerPtr->move(deltaTime, PLAYER_DIRECTION_SE);
				if(checkForPlacementCollision(playerPtr)) {
					playerPtr->restoreXY();
				}
			}
			break;
		}
		case PLAYER_DIRECTION_W: {
			playerPtr->move(deltaTime, PLAYER_DIRECTION_NW);
			if(checkForPlacementCollision(playerPtr)) {
				playerPtr->restoreXY();
				playerPtr->move(deltaTime, PLAYER_DIRECTION_WS);
				if(checkForPlacementCollision(playerPtr)) {
					playerPtr->restoreXY();
				}
			}
			break;
		}
		case PLAYER_DIRECTION_NW: {
			playerPtr->move(deltaTime, PLAYER_DIRECTION_W);
			if(checkForPlacementCollision(playerPtr)) {
				playerPtr->restoreXY();
				playerPtr->move(deltaTime, PLAYER_DIRECTION_S);
				if(checkForPlacementCollision(playerPtr)) {
					playerPtr->restoreXY();
				}
			}
			break;
		}
		case PLAYER_DIRECTION_NE: {
			playerPtr->move(deltaTime, PLAYER_DIRECTION_N);
			if(checkForPlacementCollision(playerPtr)) {
				playerPtr->restoreXY();
				playerPtr->move(deltaTime, PLAYER_DIRECTION_E);
				if(checkForPlacementCollision(playerPtr)) {
					playerPtr->restoreXY();
				}
			}
			break;
		}
		case PLAYER_DIRECTION_SE: {
			playerPtr->move(deltaTime, PLAYER_DIRECTION_E);
			if(checkForPlacementCollision(playerPtr)) {
				playerPtr->restoreXY();
				playerPtr->move(deltaTime, PLAYER_DIRECTION_S);
				if(checkForPlacementCollision(playerPtr)) {
					playerPtr->restoreXY();
				}
			}
			break;
		}
		case PLAYER_DIRECTION_WS: {
			playerPtr->move(deltaTime, PLAYER_DIRECTION_W);
			if(checkForPlacementCollision(playerPtr)) {
				playerPtr->restoreXY();
				playerPtr->move(deltaTime, PLAYER_DIRECTION_S);
				if(checkForPlacementCollision(playerPtr)) {
					playerPtr->restoreXY();
				}
			}
			break;
		}
		//default:
	}
}

//inline bool isCollision(GameObject *go1, GameObject *go2) {
//	if(dbo(go1->itSelf(),go2->itSelf())<go1->getSize()+go2->getSize()) {
//		return true;
//	}
//	return false;
//}
//
//void PHYSICS_MANAGER::correctEnemies(void) {
//
//	for(std::list<ENEMY>::iterator iEnemy=enemiesList->begin(); iEnemy!=enemiesList->end(); ++iEnemy) {
//		// collisions with other enemies
//		for(std::list<ENEMY>::iterator iEnemy2=enemiesList->begin(); iEnemy2!=enemiesList->end(); ++iEnemy2) {
//			if(iEnemy!=iEnemy2) {
//				if(isCollision(iEnemy->itSelf(), iEnemy2->itSelf())) {
//					iEnemy->restoreOldXY();
//				}
//			}
//		}
//	}
//}

//check if collision exists in list
bool PHYSICS_MANAGER::checkIfCollisionExists(const GameObject *obj, const MISSILE *proj) {
	for (std::list<COLLISION>::iterator idxColl = collisionsList.begin(); idxColl != collisionsList.end(); ++idxColl) {
		if (idxColl->getSecondObjectPtr() == proj && idxColl->getFirstObjectPtr() == obj) {
			//check existed
			idxColl->checkNextTime();
			return true;
		}
	}
	return false;
}

//check for new collisions:
void PHYSICS_MANAGER::checkCollisions(void) {
	for(std::list<MISSILE>::iterator idMissile=missilesList->begin(); idMissile!=missilesList->end(); ++idMissile) {
		switch(idMissile->getTargetType()) {
			case MISSILE_TARGET_TYPE_ENEMIES:
				for(std::list<ENEMY>::iterator idEnemy=enemiesList->begin(); idEnemy!=enemiesList->end(); ++idEnemy) {
					if(idMissile->distance(idEnemy->itSelf()) <= (idMissile->getSize()+idEnemy->getSize())) {
						if(!checkIfCollisionExists(idEnemy->itSelf(), dynamic_cast<MISSILE*>(idMissile->itSelf()))) { //i->itSelf()
							//MessageBox(0, 0, 0, 0);
							COLLISION c(idEnemy->itSelf(), dynamic_cast<MISSILE*>(idMissile->itSelf()));
							collisionsList.push_back(c);
							c.~COLLISION();
						}
					}
				}
				break;
			case MISSILE_TARGET_TYPE_HERO:
				// *два условия объеденить в одно
				if(idMissile->distance(playerPtr) <= (idMissile->getSize()+playerPtr->getSize())) {
					if(!checkIfCollisionExists(playerPtr, dynamic_cast<MISSILE*>(idMissile->itSelf()))) { //i->itSelf()
						//MessageBox(0, 0, 0, 0);
						COLLISION c(playerPtr, dynamic_cast<MISSILE*>(idMissile->itSelf()));
						collisionsList.push_back(c);
						c.~COLLISION();
					}
				}
				break;
		}
		for(std::list<BLOCK>::iterator idBlock=blocksList.begin(); idBlock!=blocksList.end(); ++idBlock) {
			if(idBlock->isCoordInBlock(idMissile->getX(), idMissile->getY(), idMissile->getSize())) {
				idMissile->setMissileUnused();
			}
		}
	}
}

//deal damage for enemies etc
void PHYSICS_MANAGER::processNewCollisions(void) {
	for(std::list<COLLISION>::iterator idColl=collisionsList.begin(); idColl!=collisionsList.end(); ++idColl) {
		if(idColl->isItNew()) {
			//if(rand()%10>2) {
				if(rand()%2==0) {
					fxPtr->addBlood(idColl->getFirstObjectPtr()->getX()+idColl->getFirstObjectPtr()->getSize()*cos(idColl->getSecondObjectPtr()->getAngle()), idColl->getFirstObjectPtr()->getY()+idColl->getFirstObjectPtr()->getSize()*sin(idColl->getSecondObjectPtr()->getAngle()), idColl->getSecondObjectPtr()->getAngle(), idColl->getFirstObjectPtr()->getSize()/(rand()%2+3), idColl->getSecondObjectPtr()->getSpeed()/15.0, FX_VISUAL_TYPE_ELLIPSE/*, this*/);
				} else {
					fxPtr->addBlood(idColl->getFirstObjectPtr()->getX()+idColl->getFirstObjectPtr()->getSize()*cos(idColl->getSecondObjectPtr()->getAngle()), idColl->getFirstObjectPtr()->getY()+idColl->getFirstObjectPtr()->getSize()*sin(idColl->getSecondObjectPtr()->getAngle()), idColl->getSecondObjectPtr()->getAngle(), idColl->getFirstObjectPtr()->getSize()/(rand()%2+3), idColl->getSecondObjectPtr()->getSpeed()/10.0, FX_VISUAL_TYPE_ELLIPSE/*, this*/);
				}
			
				if(idColl->getSecondObjectPtr()->getPenCount()!=-1) {
					idColl->getSecondObjectPtr()->pen();
				}
			//}

			//std::list<ENEMY>::iterator temp = dynamic_cast<ENEMY*>(idColl);
			//B* my_b = dynamic_cast<B*>(my_a);

			//idColl->getFirstObjectPtr()->
			idColl->getFirstObjectPtr()->takeDamage(idColl->getSecondObjectPtr()->getDamage());//(/*idColl->getSecondObjectPtr()->getDamage()*/3.0);

			//actions with this game object
			idColl->makeOld();
			idColl->checkNextTime();
		}
	}
}

//delete old collisions
void PHYSICS_MANAGER::deleteOldCollisions() {
  std::list<COLLISION>::iterator idxColl = collisionsList.begin();
  while (idxColl != collisionsList.end())
  {
    if (!idxColl->isCheck())
    {
      collisionsList.erase(idxColl);
      idxColl = collisionsList.begin();
    }
    else
      ++idxColl;
  }

  //uncheck remaining
  for (idxColl = collisionsList.begin(); idxColl != collisionsList.end(); ++idxColl)
	  idxColl->uncheck();
}

void PHYSICS_MANAGER::cleanUpMissiles(void) {
	for(std::list<MISSILE>::iterator idMissile=missilesList->begin(); idMissile!=missilesList->end(); ++idMissile) {
		if(idMissile->getPenCount()==0 || idMissile->getX()<0 || idMissile->getY()<0 || idMissile->getX()>RESOLUTION_X || idMissile->getY()>RESOLUTION_Y) {
			idMissile->setMissileUnused();
		}
	}

  //delete them
	std::list<MISSILE>::iterator i = missilesList->begin();
	while (i != missilesList->end()) {
		if (i->isUnused())
		{
		missilesList->erase(i);
		i = missilesList->begin();
		}
		else
		++i;
	}
}

//void PHYSICS_MANAGER::processEnemies(double deltaTime) {
//	double px = playerPtr->getX(),
//		   py = playerPtr->getY();
//
//	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
//		if(i->isAlive()) {
//			if(i->getRole()==ENEMY_ROLE_GUARD) {
//				if(isVision(i->itSelf(), playerPtr, intersectCoords)) {
//					if(i->distance(playerPtr) > i->getSize()+playerPtr->getSize()+ATTACK_RANGE_MELEE) {
//						enemyMoveTo(i,deltaTime,px,py);
//					}
//				} else if(DEBUGVAR_ALLOW_BOT_WAY_SEARCHING) {
//					if(dbc(px, py, intersectCoords[0], intersectCoords[1]) < dbc(px, py, intersectCoords[2], intersectCoords[3])) {
//						// lxy1
//						double a = abc(intersectCoords[2], intersectCoords[3],intersectCoords[0], intersectCoords[1]);
//						double lx1 = intersectCoords[0] + i->getSize() * cos( a );
//						double ly1 = intersectCoords[1] + i->getSize() * sin( a );
//						enemyMoveTo(i,deltaTime,lx1,ly1);
//						//i->move(deltaTime, lx1, ly1);
//						//if(checkForPlacementCollision(i->itSelf())) {
//						//	i->restoreXY();
//
//						//	int a=180;
//						//	double d=i->distance(playerPtr);
//
//						//	for(int j=0; j<360; j+=10) {
//						//		i->correct(deltaTime, lx1, ly1, j);
//						//		if(!checkForPlacementCollision(i->itSelf())) {
//						//			if(i->distance(playerPtr)<d) {
//						//				d=i->distance(playerPtr);
//						//				a=j;
//						//			}
//						//		}
//						//	}
//
//						//	if(a!=180) {
//						//		i->correct(deltaTime, lx1, ly1, a);
//						//	} else {
//						//		i->restoreXY();
//						//	}
//						//}
//					} else {
//						// lxy2
//						double a = abc(intersectCoords[0], intersectCoords[1],intersectCoords[2], intersectCoords[3]);
//						double lx1 = intersectCoords[2] + i->getSize() * cos(  a );
//						double ly1 = intersectCoords[3] + i->getSize() * sin(  a );
//						enemyMoveTo(i,deltaTime,lx1,ly1);
//						//i->move(deltaTime, lx1,ly1);
//						//if(checkForPlacementCollision(i->itSelf())) {
//						//	i->restoreXY();
//
//						//	int a=180;
//						//	double d=i->distance(playerPtr);
//
//						//	for(int j=0; j<360; j+=10) {
//						//		i->correct(deltaTime, lx1,ly1, j);
//						//		if(!checkForPlacementCollision(i->itSelf())) {
//						//			if(i->distance(playerPtr)<d) {
//						//				d=i->distance(playerPtr);
//						//				a=j;
//						//			}
//						//		}
//						//	}
//
//						//	if(a!=180) {
//						//		i->correct(deltaTime, lx1,ly1, a);
//						//	} else {
//						//		i->restoreXY();
//						//	}
//						//}
//					}
//				}
//			} else if(i->getRole()==ENEMY_ROLE_NEUTRAL) {
//				
//				if(dbc(i->getX(),i->getY(),i->getToX(),i->getToY())<i->getSize()) {
//					double _x,_y;
//					do {
//						_x=rand()%RESOLUTION_X;
//						_y=rand()%RESOLUTION_Y;
//					} while(!(isPointFree(_x,_y,i->getSize())));
//					i->setTo(_x,_y);
//				} else {
//					enemyMoveTo(i,deltaTime,i->getX(),i->getY());
//					//i->move(deltaTime,i->getToX(),i->getToY());
//					//if(checkForPlacementCollision(i->itSelf())) {
//					//	i->restoreXY();
//
//					//	int a=180;
//					//	double d=i->distance(playerPtr);
//
//					//	for(int j=0; j<360; j+=10) {
//					//		i->correct(deltaTime, i->getToX(),i->getToY(), j);
//					//		if(!checkForPlacementCollision(i->itSelf())) {
//					//			if(i->distance(playerPtr)<d) {
//					//				d=i->distance(playerPtr);
//					//				a=j;
//					//			}
//					//		}
//					//	}
//
//					//	if(a!=180) {
//					//		i->correct(deltaTime, i->getToX(),i->getToY(), a);
//					//	} else {
//					//		i->restoreXY();
//					//	}
//					//}
//				}
//			}
//
//			if(i->distance(playerPtr) > FAR_DISTANCE) {
//				i->kill();
//			}
//		}
//	}
//}