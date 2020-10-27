#include "physicsManager.h"
#include "game_object.h"
#include "player.h"
#include "block.h"

PhysicsManager& PhysicsManager::instance() {
  static PhysicsManager instance;
  return instance;
}

void PhysicsManager::updateWorldPhysics(float dt) {
  for(auto &go : gos) {
    go->processPhysics(dt);
  }
}

void PhysicsManager::renderWorld(HDC bhdc) {
  for(auto &go : gos) {
    go->draw(bhdc);
  }
}

void PhysicsManager::createPlayer(float x, float y) {
  const auto ptr = std::shared_ptr<GameObject>(new Player(x, y, 80.f));

  gos.emplace_back( ptr );
  //_player = ptr;
}

void PhysicsManager::createBlock(float x, float y, float w, float h) {
  const auto ptr = std::shared_ptr<GameObject>(new BLOCK(x, y, w, h));

  gos.emplace_back( ptr );
}

void PhysicsManager::deposeObjects(float dx, float dy) {
  for(auto &go : gos) {
    go->depose(dx, dy);
  }
}

//void PhysicsManager::createNPC(float x, float y) {
//  const auto ptr = createGameObject( x, y, 15, 20, 0 );
//
//  _GameObjects.emplace_back( ptr );
//  _enemies.emplace_back( ptr );
//}
//
//void PhysicsManager::createProjectile(float x, float y) {
//  const auto ptr = createGameObject( x, y, 3, 20, 0 );
//
//  _GameObjects.emplace_back( ptr );
//  _projectiles.emplace_back( ptr );
//}

//
////bool PhysicsManager::checkForPlacementCollision(float X,float Y,float W,float H) {
////	bool free=true;
////
////	for(std::list<BLOCK>::iterator it=blocksList.begin(); it!=blocksList.end(); ++it) {
////		if(it->rectCollision(X,Y,W,H)) {
////			free=false;
////		}
////	}
////
////	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
////		float x = i->getX();
////		float y = i->getY();
////		float w = i->getSize();
////		float h = i->getSize();
////		//bool BLOCK::rectCollision(float X, float Y, float W, float H) {
////		//return ;
////		//}
////
////		if( i->isAlive() && 
////			X-W<x+w/2 && Y-H<y+h/2 && X+W>x-w/2 && Y+H>y-h/2 ) {
////			free=false;
////		}
////		
////		
////		//if((i->isAlive())&&(i->distance(go)<i->getSize()+go->getSize())) {
////		//	free=false;
////		//}
////	}
////
////	return free;
////}
//
//void PhysicsManager::addMissile(float newX, float newY, float newAngle, float newSpeed, float newDamage, const int newTargetType, float newMissileSize, int newPenCount) {
//  gos.push_back(MISSILE(newX, newY, newSpeed, newDamage, newAngle, newTargetType, newMissileSize, newPenCount, nullptr, nullptr));
//}
//
////bool PhysicsManager::checkForPlacementCollision(GameObject *go) {
////	const bool checkForBlocksCollision = true;
////	
////	if(go!=playerPtr) {
////		if(playerPtr->distance(go)<playerPtr->getSize()+go->getSize()) {
////			return(true);
////		}
////	}
////	
////	if(checkForBlocksCollision) {
////		for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
////			if(i->isCoordInBlock(go->getX(),go->getY(),go->getSize())) {
////				return(true);
////			}
////			
////			//if(i->isGOinBlock(go->itSelf())) {
////			//	return(true);
////			//}
////		}
////	}
////
////	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
////		if((i->itSelf()!=go)&&(i->isAlive())&&(i->distance(go)<i->getSize()+go->getSize())) {
////			return(true);
////		}
////	}
////
////	return(false);
////}
//
////void PhysicsManager::processNoises(float deltaTime) {
////	for(std::vector<NOISE>::iterator i=noisesVector.begin(); i!=noisesVector.end(); ++i) {
////		i->increaseNoiseRadius(deltaTime);
////		for(std::list<ENEMY>::iterator j=enemiesList->begin(); j!=enemiesList->end(); ++j) {
////
////			//float d = /* - j->getSize()*/;
////
////
////			if(   dbc(    i-> getX(), i-> getY(), j-> getX(), j-> getY()    )   <=  i->getRadius()   ) {
////
////				if(j->getCurrentTarget()==ENEMY_CURRENT_TARGET_PATROL) {
////					if(j->getRole()==ENEMY_ROLE_GUARD) {
////						j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
////					} else {
////						j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
////					}
////				}
////
////				//switch(j->getRole()) {
////				//	case ENEMY_ROLE_NEUTRAL:
////				//	switch(j->getCurrentTarget()) {
////				//		case ENEMY_CURRENT_TARGET_PATROL:
////				//		j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
////				//		break;
////				//	}
////				//	break;
////				//	case ENEMY_ROLE_GUARD:
////				//	switch(j->getCurrentTarget()) {
////				//		case ENEMY_CURRENT_TARGET_PATROL:
////				//		if(!isVision(playerPtr,j->itSelf(),intersectCoords,&count)) {
////				//			j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
////				//		} else {
////				//			j->setCurrentTarget(ENEMY_CURRENT_TARGET_ATTACK_PLAYER);
////				//		}
////				//		break;
////				//	}
////				//	break;
////				//}
////
////			}
////		}
////	}
////}
//
//void PhysicsManager::movePlayer(float deltaTime, const int playerDir) {
//	playerPtr->move(deltaTime, playerDir);
//}
//
//bool PhysicsManager::isPointFree(float X, float Y, float R = 0) {
//	bool r = true;
//
//	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
//		if(dbc(i->getX(), i->getY(), X, Y)<i->getSize()) {
//			r = false;
//		}
//	}
//
//	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
//		if(i->isCoordInBlock(X,Y,R)) {
//			r = false;
//		}
//	}
//
//	return r;
//}
//
//bool PhysicsManager::isVision(GameObject *A, GameObject *B) {
//	float ax = A->getX();
//	float ay = A->getY();
//	float bx = B->getX();
//	float by = B->getY();
//	
//	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
//		if(i->checkForIntersection(ax,ay,bx,by)) {
//			return(true);
//		}
//	}
//
//	return false;
//}
//
//int PhysicsManager::isVisionSmart(GameObject *A, GameObject *B, float *coords, int *count) {
//	//bool vis = true;
//
//	int r = -1;
//	float ax = A->getX();
//	float ay = A->getY();
//	float bx = B->getX();
//	float by = B->getY();
//	
//	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
//
//		//if() {
//			
//			
//			r = i->checkForIntersection(ax,ay,bx,by,coords,count);
//			if( r != -1 ) break;
//
//			//vis = false;
//		//}
//
//	}
//
//	return r;
//	//return vis;
//}
//
////void PhysicsManager::offset(std::list<BLOCK>::iterator it) {
////
////}
//
//void PhysicsManager::enemyMoveTo(std::list<ENEMY>::iterator it, float deltaTime, float X, float Y) {
//
//	
//	
//	it->move(deltaTime, X, Y);
//
//	//for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
//	//	i->offset(it);
//	//}
//
//	//if(checkForPlacementCollision(it->itSelf())) {
//	//	it->restoreXY();
//	//}
//
//	float tx,ty;
//	int t=it->getCurrentTarget();
//
//	if(t==ENEMY_CURRENT_TARGET_ATTACK_PLAYER) {
//		tx = playerPtr->getX();
//		ty = playerPtr->getY();
//
//		if(checkForPlacementCollision(it->itSelf())) {
//			it->restoreXY();
//
//			int a=180;
//			float d=dbc(tx,ty,it->getX(),it->getY());//it->distance(playerPtr);
//
//			for(int j=0; j<360; j+=10) {
//				it->correct(deltaTime, X, Y, j);
//				if(!checkForPlacementCollision(it->itSelf())) {
//					if(dbc(tx,ty,it->getX(),it->getY())<d) {
//						d=dbc(tx,ty,it->getX(),it->getY());
//						a=j;
//					}
//				}
//			}
//
//			if(a!=180) {
//				it->correct(deltaTime, X, Y, a);
//			} else {
//				it->restoreXY();
//			}
//		}
//
//
//	} else {
//		tx = it->getToX();
//		ty = it->getToY();
//
//		if(checkForPlacementCollision(it->itSelf())) {
//			it->restoreXY();
//
//			int a=180;
//			//float d=dbc(tx,ty,it->getX(),it->getY());//it->distance(playerPtr);
//
//			for(int j=0; j<360; j+=10) {
//				it->correct(deltaTime, X, Y, j);
//				if(!checkForPlacementCollision(it->itSelf())) {
//					//if(dbc(tx,ty,it->getX(),it->getY())<d) {
//						//d=dbc(tx,ty,it->getX(),it->getY());
//						a=j;
//					//}
//				}
//			}
//
//			if(a!=180) {
//				it->correct(deltaTime, X, Y, a);
//			} else {
//				it->restoreXY();
//			}
//		}
//	}
//
//	// rewrite this moment
//	//if(checkForPlacementCollision(it->itSelf())) {
//	//	it->restoreXY();
//
//	//	int a=180;
//	//	//float d=dbc(tx,ty,it->getX(),it->getY());//it->distance(playerPtr);
//
//	//	for(int j=0; j<360; j+=36) {
//	//		it->correct(deltaTime, X, Y, j);
//	//		if(!checkForPlacementCollision(it->itSelf())) {
//	//			//if(dbc(tx,ty,it->getX(),it->getY())<d) {
//	//				//d=dbc(tx,ty,it->getX(),it->getY());
//	//				a=j;
//	//			//}
//	//		}
//	//	}
//
//	//	if(a!=180) {
//	//		it->correct(deltaTime, X, Y, a);
//	//	} else {
//	//		it->restoreXY();
//	//	}
//	//}
//
//
//	//switch(it->getCurrentTarget()) {
//	//case ENEMY_CURRENT_TARGET_PATROL:
//	//	tx = it->getToX();
//	//	ty = it->getToY();
//	//	break;
//	//}
//
//	//float tx = it->getToX(),
//	//	   ty = it->getToY();
//
//	//if(it->getCurrentTarget() == ENEMY_CURRENT_TARGET_ATTACK_PLAYER) {
//		//if(checkForPlacementCollision(it->itSelf())) {
//		//	it->restoreXY();
//
//		//	int a=180;
//		//	float d=it->distance(playerPtr);
//
//		//	for(int j=0; j<360; j+=30) {
//		//		it->correct(deltaTime, X, Y, j);
//		//		if(!checkForPlacementCollision(it->itSelf())) {
//		//			if(it->distance(playerPtr)<d) {
//		//				d=it->distance(playerPtr);
//		//				a=j;
//		//			}
//		//		}
//		//	}
//
//		//	if(a!=180) {
//		//		it->correct(deltaTime,  X, Y, a);
//		//	} else {
//		//		it->restoreXY();
//		//	}
//	//	}
//	//} else if(it->getCurrentTarget() == ENEMY_CURRENT_TARGET_SEARCH_PLAYER ||
//		//it->getCurrentTarget() == ENEMY_CURRENT_TARGET_ESCAPE ||
//		//it->getCurrentTarget() == ENEMY_CURRENT_TARGET_PATROL) {
//
//		//if(checkForPlacementCollision(it->itSelf())) {
//		//	it->restoreXY();
//
//		//	int a=180;
//		//	float d=dbc(tx,ty,it->getX(),it->getY());//it->distance(playerPtr);
//
//		//	for(int j=0; j<360; j+=30) {
//		//		it->correct(deltaTime, X, Y, j);
//		//		if(!checkForPlacementCollision(it->itSelf())) {
//		//			if(dbc(tx,ty,it->getX(),it->getY())<d) {
//		//				d=dbc(tx,ty,it->getX(),it->getY());
//		//				a=j;
//		//			}
//		//		}
//		//	}
//
//		//	if(a!=180) {
//		//		it->correct(deltaTime,  X, Y, a);
//		//	} else {
//		//		it->restoreXY();
//		//	}
//		//}
//	//}
//
//
//}
//
////bool PhysicsManager::isRectCollision(float X, float Y, float W, float H) {
////	bool b = false;
////	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
////		float x = i->getX();
////		float y = i->getY();
////		b = X-W<x+w/2 && Y-H<y+h/2 && X+W>x-w/2 && Y+H>y-h/2
////	}
////
////	return X-W<x+w/2 && Y-H<y+h/2 && X+W>x-w/2 && Y+H>y-h/2;
////}
//
//bool isRectCollision(float X,float Y,float x,float y,float w,float h) {
//	//XY - 1; xywh - 2
//	return X<x+w/2 && Y<y+h/2 && X>x-w/2 && Y>y-h/2;
//}
//
////void PhysicsManager::findWayToPlayer(std::list<ENEMY>::iterator it, float px, float py) {
////
////}
//
//void PhysicsManager::computeRandomPointToPatrol(std::list<ENEMY>::iterator it) {
//	float _x,_y;
//	do {
//		_x=rand()%RESOLUTION_X;
//		_y=rand()%RESOLUTION_Y;
//	} while(!(isPointFree(_x,_y,it->getSize())));
//	it->setTo(_x,_y);
//}
//
//void PhysicsManager::processEnemies(float deltaTime) {
//	float px = playerPtr->getX(),
//		   py = playerPtr->getY();
//
//	float _x,_y,_a;
//	int side;
//
//	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
//		if(i->isAlive()) {
//			
//			///================///================///================///================
//
//			if(DEBUGVAR_ALLOW_ENEMIES_SEE_EACH_OTHER) {
//				for(std::list<ENEMY>::iterator j=enemiesList->begin(); j!=enemiesList->end(); ++j) {
//					if(i!=j) {
//						int it = i->getCurrentTarget();
//						int jt = j->getCurrentTarget();
//						int ir = i->getRole();
//						int jr = j->getRole();
//						
//						if(ir==ENEMY_ROLE_GUARD) {
//							if(isVision(i->itSelf(),j->itSelf()) && (it==ENEMY_CURRENT_TARGET_SEARCH_PLAYER || it==ENEMY_CURRENT_TARGET_ATTACK_PLAYER)) {
//								if(jt==ENEMY_CURRENT_TARGET_PATROL) {
//									if(j->getRole()==ENEMY_ROLE_GUARD) {
//										j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
//									} else if(j->getRole()==ENEMY_ROLE_NEUTRAL) {
//										j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
//									}
//								}
//							}
//						} else {
//							if(isVision(i->itSelf(),j->itSelf()) && it==ENEMY_CURRENT_TARGET_ESCAPE) {
//								if(jt==ENEMY_CURRENT_TARGET_PATROL) {
//									if(j->getRole()==ENEMY_ROLE_GUARD) {
//										j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
//									} else if(j->getRole()==ENEMY_ROLE_NEUTRAL) {
//										j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
//									}
//								}
//							}
//						}
//
//						//if(isVision(i->itSelf(),j->itSelf()) && (it==ENEMY_CURRENT_TARGET_SEARCH_PLAYER || it==ENEMY_CURRENT_TARGET_ATTACK_PLAYER)) {
//						//	if(jt==ENEMY_CURRENT_TARGET_PATROL) {
//						//		if(j->getRole()==ENEMY_ROLE_GUARD) {
//						//			j->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
//						//		} else if(j->getRole()==ENEMY_ROLE_NEUTRAL) {
//						//			j->setCurrentTarget(ENEMY_CURRENT_TARGET_ESCAPE);
//						//		}
//						//	}
//						//}
//					}
//				}
//			}
//
//			///================///================///================///================
//
//			if(i->isWounded()) {
//				i->updateWound(deltaTime);
//			}
//
//			float x = i->getX();
//			float y = i->getY();
//
//			switch(i->getCurrentTarget()) {
//				case ENEMY_CURRENT_TARGET_PATROL:
//					if(dbc(x,y,i->getToX(),i->getToY())<i->getSize()) {
//						computeRandomPointToPatrol(i);
//					} else {
//						enemyMoveTo(i,deltaTime,i->getToX(),i->getToY());
//					}
//					break;
//
//				case ENEMY_CURRENT_TARGET_SEARCH_PLAYER:
//					count = 0;
//					side = isVisionSmart(i->itSelf(), playerPtr, intersectCoords, &count);
//
//					if(side == -1) {
//						i->setCurrentTarget(ENEMY_CURRENT_TARGET_ATTACK_PLAYER);
//						//i->NotComputedTo();
//					} else {
//						if(!i->isComputedTo()) {
//							float lx1 = intersectCoords[0],
//									ly1 = intersectCoords[1];
//							float lx2 = intersectCoords[2],
//									ly2 = intersectCoords[3];
//							float lx3 = intersectCoords[4],
//									ly3 = intersectCoords[5];
//							float lx4 = intersectCoords[6],
//									ly4 = intersectCoords[7];
//
//							i->setPointXY(0, lx1, ly1);
//							i->setPointXY(1, lx2, ly2);
//							i->setPointXY(2, lx3, ly3);
//							i->setPointXY(3, lx4, ly4);
//
//							float a;
//							float s = i->getSize()*2;
//
//							float cx = (lx1+lx2)/2,
//									cy = (ly1+ly2)/2;
//							float cx2 = (lx3+lx4)/2,
//									cy2 = (ly3+ly4)/2;
//
//							if(DEBUGVAR_INCLUDE_ENEMIES_VISION) {
//								if(dbc(x,y,cx,cy)<dbc(x,y,cx2,cy2)) {
//									i->setPlayerCoords(cx,cy);
//								} else {
//									i->setPlayerCoords(cx2,cy2);
//								}
//							}
//
//							// not absolutely right algorithm
//							// rewrite when will free of other coding
//							// 45 degress not only to +
//							// so to - too
//							// compute this later
//
//							if(dbc(cx,cy,x,y)<dbc(cx2,cy2,x,y)) {
//								if(dbc(px,py,lx1,ly1)<dbc(px,py,lx2,ly2)) {
//									a=abc(lx2,ly2,lx1,ly1)     +45*DEGTORAD;
//									i->setTo(lx1+s*cos(a),ly1+s*sin(a));
//								} else {
//									a=abc(lx1,ly1,lx2,ly2)     +45*DEGTORAD;
//									i->setTo(lx2+s*cos(a),ly2+s*sin(a));
//								}
//							} else {
//								if(dbc(px,py,lx3,ly3)<dbc(px,py,lx4,ly4)) {
//									a=abc(lx4,ly4,lx3,ly3)     +45*DEGTORAD;
//									i->setTo(lx3+s*cos(a),ly3+s*sin(a));
//								} else {
//									a=abc(lx3,ly3,lx4,ly4)     +45*DEGTORAD;
//									i->setTo(lx4+s*cos(a),ly4+s*sin(a));
//								}
//							}
//
//							i->computed();
//						} else {
//							if(dbc(x,y,i->getToX(),i->getToY())>i->getSize()/2) {
//								enemyMoveTo(i, deltaTime, i->getToX(), i->getToY());
//							} else {
//								i->NotComputedTo();
//							}
//						}
//					}
//					break;
//
//				case ENEMY_CURRENT_TARGET_ATTACK_PLAYER:
//					//i->run();
//
//					side = isVisionSmart(i->itSelf(), playerPtr, intersectCoords, &count);
//
//					if(side == -1) {
//						if(i->distance(playerPtr) > i->getSize()+playerPtr->getSize()+ATTACK_RANGE_MELEE) {
//							enemyMoveTo(i,deltaTime,px,py);
//						}
//					} else {
//						i->setCurrentTarget(ENEMY_CURRENT_TARGET_SEARCH_PLAYER);
//					}
//					break;
//
//				case ENEMY_CURRENT_TARGET_ESCAPE:
//					_a = abc(px, py, x,y);
//					_x=px + FAR_DISTANCE*2 * cos(_a), _y=py + FAR_DISTANCE*2 * sin(_a);
//					enemyMoveTo(i,deltaTime,_x,_y);
//					break;
//			}
//
//			if(i->distance(playerPtr) > FAR_DISTANCE) {
//				i->kill();
//			}
//		}
//	}
//}
//
//void PhysicsManager::removeFarBlocks(float X, float Y, float d) {
//	for(std::list<BLOCK>::iterator it=blocksList.begin(); it!=blocksList.end(); ++it) {
//		if(dbc(X,Y,it->getX(),it->getY())>d) {
//			it->toDelete();
//		}
//	}
//
//	std::list<BLOCK>::iterator it=blocksList.begin();
//	while(it!=blocksList.end()) {
//		if(it->isToDelete()) {
//			blocksList.erase(it); it=blocksList.begin();
//		} else ++it;
//	}
//}
//
//void PhysicsManager::removeNoises(void) {
//	std::vector<NOISE>::iterator it=noisesVector.begin();
//	while(it!=noisesVector.end()) {
//		if(it->isToDelete()) {
//			noisesVector.erase(it);
//			it=noisesVector.begin();
//		} else {
//			++it;
//		}
//	}
//}
//
//void PhysicsManager::setCameraOffsetValue(float X, float Y) {
//	offsetFromCenterX = X;
//	offsetFromCenterY = Y;
//}
//
//void PhysicsManager::deposeGameObjectsFromCenter(/*float offsetX, float offsetY*/) {
//	//offsetFromCenterX = offsetX;
//	//offsetFromCenterY = offsetY;
//	
//	float offsetX1 = offsetFromCenterX,
//		     offsetY1 = offsetFromCenterY;
//
//	for(std::list<BLOCK>::iterator it=blocksList.begin(); it!=blocksList.end(); ++it) {
//		it->setCameraOffset(offsetX1,offsetY1);
//	}
//	for(std::list<ENEMY>::iterator it=enemiesList->begin(); it!=enemiesList->end(); ++it) {
//		it->setCameraOffset(offsetX1,offsetY1);
//	}
//  for(auto &go : gos) {
//    go.setCameraOffset(offsetX1, offsetY1);
//  }
//	//for(std::list<MISSILE>::iterator it=missilesList->begin(); it!=missilesList->end(); ++it) {
//	//	it->setCameraOffset(offsetX1,offsetY1);
//	//}
//	for(std::vector<NOISE>::iterator it=noisesVector.begin(); it!=noisesVector.end(); ++it) {
//		it->setCameraOffset(offsetX1,offsetY1);
//	}
//	fxPtr->setCameraOffset(offsetX1,offsetY1);
//	playerPtr->setCameraOffset(offsetX1,offsetY1);
//}
//
//void PhysicsManager::deposeGameObjects(float X, float Y) {
//	for(std::list<BLOCK>::iterator it=blocksList.begin(); it!=blocksList.end(); ++it) {
//		it->depose(X, Y);
//	}
//
//	for(std::list<ROAD>::iterator it=roadsList.begin(); it!=roadsList.end(); ++it) {
//		it->depose(X, Y);
//	}
//
//	for(std::list<ENEMY>::iterator it=enemiesList->begin(); it!=enemiesList->end(); ++it) {
//		it->depose(X, Y);
//	}
//
//	//for(std::list<SHELL>::iterator it=shells.begin(); it!=shells->end(); ++it) {
//	//	it->depose(X, Y);
//	//}
//	deposeNoises(X, Y);
//	fxPtr->depose(X, Y);
//}
//
//// ������� ���������, ������������ �� ���������� ����� ������ � �����������
//bool PhysicsManager::col(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
//	float rx[4]={x1,x2,x3,x4};
//	float ry[4]={y1,y2,y3,y4};
//
//	for(std::list<BLOCK>::iterator it=blocksList.begin();it!=blocksList.end();++it) {
//
//		//for(int i=0;i<4;i++) {
//		//	if(isIntersection(rx[i],ry[i],rx[j],ry[j],) {
//		//		return true;
//		//	}
//		//}
//	}
//
//	return false;
//}
//
//void PhysicsManager::placeRoadByPlayerDirection(const int playerDir) {
//	const float offset = 50.0;
//	const float maxX = RESOLUTION_X+offset;
//	const float maxY = RESOLUTION_Y;
//	const float minX = -offset;
//	const float minY = -offset;
//	
//	float ax,ay,bx,by;
//	float cx,cy,dx,dy;
//
//	ax=ay=bx=by=cx=cy=dx=dy=0.0;
//
//	float roadSize = 50;
//
//	switch(playerDir) {
//	case PLAYER_DIRECTION_E:
//		ax = maxX;
//		ay = minY;
//		bx = maxX;
//		by = maxY;
//		cx = ax + roadSize;
//		cy = ay;
//		dx = bx + roadSize;
//		dy = by;
//		
//		if(!col(ax,ay,bx,by,dx,dy,cx,cy)) {
//			createRoad(ax,ay,bx,by,cx,cy,dx,dy);
//		}
//		break;
//	case PLAYER_DIRECTION_W:
//		ax = minX;
//		ay = minY;
//		bx = minX;
//		by = maxY;
//		cx = ax - roadSize;
//		cy = ay;
//		dx = bx - roadSize;
//		dy = by;
//		if(!col(ax,ay,bx,by,dx,dy,cx,cy)) {
//			createRoad(ax,ay,bx,by,cx,cy,dx,dy);
//		}
//		break;
//	case PLAYER_DIRECTION_N:
//		ax = minX;
//		ay = minY;
//		bx = maxX;
//		by = minY;
//		cx = ax;
//		cy = ay - roadSize;
//		dx = bx;
//		dy = by - roadSize;
//		if(!col(ax,ay,bx,by,dx,dy,cx,cy)) {
//			createRoad(ax,ay,bx,by,cx,cy,dx,dy);
//		}
//		break;
//	case PLAYER_DIRECTION_S:
//		ax = minX;
//		ay = maxY;
//		bx = maxX;
//		by = maxY;
//		cx = ax;
//		cy = ay + roadSize;
//		dx = bx;
//		dy = by + roadSize;
//		if(!col(ax,ay,bx,by,dx,dy,cx,cy)) {
//			createRoad(ax,ay,bx,by,cx,cy,dx,dy);
//		}
//		break;
//	}
//}
//
//void PhysicsManager::placeBlockByPlayerDirection(const int playerDir) {
//	const float offset = 50.0;
//	const float maxX = RESOLUTION_X+offset;
//	const float maxY = RESOLUTION_Y;
//	const float minX = -offset;
//	const float minY = -offset;
//	
//	float x,y;
//	float px = playerPtr->getX(), py = playerPtr->getY();
//	float a;
//
//	switch(playerDir) {
//	case PLAYER_DIRECTION_E:
//		x=maxX;
//		y=rand()%(int)maxY;
//		break;
//	case PLAYER_DIRECTION_W:
//		x=minX;
//		y=rand()%(int)maxY;
//		break;
//	case PLAYER_DIRECTION_N:
//		x=rand()%(int)maxX;
//		y=minY;
//		break;
//	case PLAYER_DIRECTION_S:
//		x=rand()%(int)maxX;
//		y=maxX;
//		break;
//	case PLAYER_DIRECTION_NW:
//		x=minX;
//		y=minY;
//		break;
//	case PLAYER_DIRECTION_NE:
//		x=maxX;
//		y=minY;
//		break;
//	case PLAYER_DIRECTION_SE:
//		x=maxX;
//		y=maxY;
//		break;
//	case PLAYER_DIRECTION_WS:
//		x=minX;
//		y=maxY;
//		break;
//	default:
//		x=y=0;
//		break;
//	}
//
//	float w=rand()%100+50,h=rand()%100+50;
//
//	if(checkForPlacementCollision(x,y,w,h)) {
//		placeBlock(x,y,w,h);
//	}
//}
//
//void PhysicsManager::moveAll(float deltaTime, const int playerDir) {
//	movePlayer(deltaTime, playerDir);
//
//	if(checkForPlacementCollision(playerPtr)) {
//		correctPlayerPlacement(playerDir, deltaTime);
//	}
//
//	if(DEBUGVAR_ALLOW_INFINITE_MAP) {
//		// depose blocks
//		const float safe = PLAYER_OUT_OF_MAP_SAFE_OFFSET;
//		if(playerPtr->getX() > RESOLUTION_X - safe) {
//			deposeGameObjects((RESOLUTION_X-safe)-playerPtr->getX(),0.00);
//			playerPtr->setXY((RESOLUTION_X-safe),playerPtr->getY());
//			if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
//				placeBlockByPlayerDirection(playerDir);
//			}
//
//			if(getRoadsCount() < MAXIMAL_ROADS_AT_MAP) {
//				placeRoadByPlayerDirection(playerDir);
//			}
//		}
//		if(playerPtr->getY() > RESOLUTION_Y - safe) {
//			deposeGameObjects(0.0,(RESOLUTION_Y-safe)-playerPtr->getY());
//			playerPtr->setXY(playerPtr->getX(),(RESOLUTION_Y-safe));
//			if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
//				placeBlockByPlayerDirection(playerDir);
//			}
//
//			if(getRoadsCount() < MAXIMAL_ROADS_AT_MAP) {
//				placeRoadByPlayerDirection(playerDir);
//			}
//		}
//		if(playerPtr->getX() < safe) {
//			deposeGameObjects(safe-playerPtr->getX(),0.00);
//			playerPtr->setXY((safe),playerPtr->getY());
//			
//			if(getRoadsCount() < MAXIMAL_ROADS_AT_MAP) {
//				placeRoadByPlayerDirection(playerDir);
//			}
//
//			if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
//				placeBlockByPlayerDirection(playerDir);
//			}
//		}
//		if(playerPtr->getY() < safe) {
//			deposeGameObjects(0.0,safe-playerPtr->getY());
//			playerPtr->setXY(playerPtr->getX(),(safe));
//			if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
//				placeBlockByPlayerDirection(playerDir);
//			}
//
//			if(getRoadsCount() < MAXIMAL_ROADS_AT_MAP) {
//				placeRoadByPlayerDirection(playerDir);
//			}
//		}
//
//		//*create dynamic map
//		//if(getBlocksCount() < MAXIMAL_BLOCKS_AT_MAP) {
//		//	placeBlockByPlayerDirection(playerDir);
//		//}
//
//		removeFarBlocks(playerPtr->getX(),playerPtr->getY(),FAR_DISTANCE);
//	} else {
//		if(playerPtr->getX() > RESOLUTION_X || playerPtr->getY() > RESOLUTION_Y || playerPtr->getX()<0 || playerPtr->getY()<0 ) {
//			playerPtr->restoreXY();
//		}
//	}
//
//	processEnemies(deltaTime);
//  updateWorldPhysics(deltaTime);
//
//	//mMan.move(deltaTime*timeFactor);
//	//player.move(deltaTime*timeFactor, keys.getPlayerDirection());
//	//enemyMan.process(deltaTime*timeFactor);
//}
//
//void PhysicsManager::correctPlayerPlacement(const int playerDir, float deltaTime) {
//	playerPtr->restoreXY();
//
//	switch(playerDir) {
//		case PLAYER_DIRECTION_N: {
//			playerPtr->move(deltaTime, PLAYER_DIRECTION_NW);
//			if(checkForPlacementCollision(playerPtr)) {
//				playerPtr->restoreXY();
//				playerPtr->move(deltaTime, PLAYER_DIRECTION_NE);
//				if(checkForPlacementCollision(playerPtr)) {
//					playerPtr->restoreXY();
//				}
//			}
//			break;
//		}
//		case PLAYER_DIRECTION_E: {
//			playerPtr->move(deltaTime, PLAYER_DIRECTION_NE);
//			if(checkForPlacementCollision(playerPtr)) {
//				playerPtr->restoreXY();
//				playerPtr->move(deltaTime, PLAYER_DIRECTION_SE);
//				if(checkForPlacementCollision(playerPtr)) {
//					playerPtr->restoreXY();
//				}
//			}
//			break;
//		}
//		case PLAYER_DIRECTION_S: {
//			playerPtr->move(deltaTime, PLAYER_DIRECTION_WS);
//			if(checkForPlacementCollision(playerPtr)) {
//				playerPtr->restoreXY();
//				playerPtr->move(deltaTime, PLAYER_DIRECTION_SE);
//				if(checkForPlacementCollision(playerPtr)) {
//					playerPtr->restoreXY();
//				}
//			}
//			break;
//		}
//		case PLAYER_DIRECTION_W: {
//			playerPtr->move(deltaTime, PLAYER_DIRECTION_NW);
//			if(checkForPlacementCollision(playerPtr)) {
//				playerPtr->restoreXY();
//				playerPtr->move(deltaTime, PLAYER_DIRECTION_WS);
//				if(checkForPlacementCollision(playerPtr)) {
//					playerPtr->restoreXY();
//				}
//			}
//			break;
//		}
//		case PLAYER_DIRECTION_NW: {
//			playerPtr->move(deltaTime, PLAYER_DIRECTION_W);
//			if(checkForPlacementCollision(playerPtr)) {
//				playerPtr->restoreXY();
//				playerPtr->move(deltaTime, PLAYER_DIRECTION_S);
//				if(checkForPlacementCollision(playerPtr)) {
//					playerPtr->restoreXY();
//				}
//			}
//			break;
//		}
//		case PLAYER_DIRECTION_NE: {
//			playerPtr->move(deltaTime, PLAYER_DIRECTION_N);
//			if(checkForPlacementCollision(playerPtr)) {
//				playerPtr->restoreXY();
//				playerPtr->move(deltaTime, PLAYER_DIRECTION_E);
//				if(checkForPlacementCollision(playerPtr)) {
//					playerPtr->restoreXY();
//				}
//			}
//			break;
//		}
//		case PLAYER_DIRECTION_SE: {
//			playerPtr->move(deltaTime, PLAYER_DIRECTION_E);
//			if(checkForPlacementCollision(playerPtr)) {
//				playerPtr->restoreXY();
//				playerPtr->move(deltaTime, PLAYER_DIRECTION_S);
//				if(checkForPlacementCollision(playerPtr)) {
//					playerPtr->restoreXY();
//				}
//			}
//			break;
//		}
//		case PLAYER_DIRECTION_WS: {
//			playerPtr->move(deltaTime, PLAYER_DIRECTION_W);
//			if(checkForPlacementCollision(playerPtr)) {
//				playerPtr->restoreXY();
//				playerPtr->move(deltaTime, PLAYER_DIRECTION_S);
//				if(checkForPlacementCollision(playerPtr)) {
//					playerPtr->restoreXY();
//				}
//			}
//			break;
//		}
//		//default:
//	}
//}
//
////inline bool isCollision(GameObject *go1, GameObject *go2) {
////	if(dbo(go1->itSelf(),go2->itSelf())<go1->getSize()+go2->getSize()) {
////		return true;
////	}
////	return false;
////}
////
////void PhysicsManager::correctEnemies(void) {
////
////	for(std::list<ENEMY>::iterator iEnemy=enemiesList->begin(); iEnemy!=enemiesList->end(); ++iEnemy) {
////		// collisions with other enemies
////		for(std::list<ENEMY>::iterator iEnemy2=enemiesList->begin(); iEnemy2!=enemiesList->end(); ++iEnemy2) {
////			if(iEnemy!=iEnemy2) {
////				if(isCollision(iEnemy->itSelf(), iEnemy2->itSelf())) {
////					iEnemy->restoreOldXY();
////				}
////			}
////		}
////	}
////}
//
////check if collision exists in list
//bool PhysicsManager::checkIfCollisionExists(const GameObject *obj, const MISSILE *proj) {
//	for (std::list<COLLISION>::iterator idxColl = collisionsList.begin(); idxColl != collisionsList.end(); ++idxColl) {
//		if (idxColl->getSecondObjectPtr() == proj && idxColl->getFirstObjectPtr() == obj) {
//			//check existed
//			idxColl->checkNextTime();
//			return true;
//		}
//	}
//	return false;
//}
//
////check for new collisions:
//void PhysicsManager::checkCollisions(void) {
//	//for(std::list<MISSILE>::iterator idMissile=missilesList->begin(); idMissile!=missilesList->end(); ++idMissile) {
//	//	switch(idMissile->getTargetType()) {
//	//		case MISSILE_TARGET_TYPE_ENEMIES:
//	//			for(std::list<ENEMY>::iterator idEnemy=enemiesList->begin(); idEnemy!=enemiesList->end(); ++idEnemy) {
//	//				if(idMissile->distance(idEnemy->itSelf()) <= (idMissile->getSize()+idEnemy->getSize())) {
//	//					if(!checkIfCollisionExists(idEnemy->itSelf(), dynamic_cast<MISSILE*>(idMissile->itSelf()))) { //i->itSelf()
//	//						//MessageBox(0, 0, 0, 0);
//	//						COLLISION c(idEnemy->itSelf(), dynamic_cast<MISSILE*>(idMissile->itSelf()));
//	//						collisionsList.push_back(c);
//	//						c.~COLLISION();
//	//					}
//	//				}
//	//			}
//	//			break;
//	//		case MISSILE_TARGET_TYPE_HERO:
//	//			// *��� ������� ���������� � ����
//	//			if(idMissile->distance(playerPtr) <= (idMissile->getSize()+playerPtr->getSize())) {
//	//				if(!checkIfCollisionExists(playerPtr, dynamic_cast<MISSILE*>(idMissile->itSelf()))) { //i->itSelf()
//	//					//MessageBox(0, 0, 0, 0);
//	//					COLLISION c(playerPtr, dynamic_cast<MISSILE*>(idMissile->itSelf()));
//	//					collisionsList.push_back(c);
//	//					c.~COLLISION();
//	//				}
//	//			}
//	//			break;
//	//	}
//	//	for(std::list<BLOCK>::iterator idBlock=blocksList.begin(); idBlock!=blocksList.end(); ++idBlock) {
//	//		if(idBlock->isCoordInBlock(idMissile->getX(), idMissile->getY(), idMissile->getSize())) {
//	//			idMissile->setMissileUnused();
//	//		}
//	//	}
//	//}
//}
//
////deal damage for enemies etc
//void PhysicsManager::processNewCollisions(void) {
//	for(std::list<COLLISION>::iterator idColl=collisionsList.begin(); idColl!=collisionsList.end(); ++idColl) {
//		if(idColl->isItNew()) {
//			//if(rand()%10>2) {
//				if(rand()%2==0) {
//					fxPtr->addBlood(idColl->getFirstObjectPtr()->getX()+idColl->getFirstObjectPtr()->getSize()*cos(idColl->getSecondObjectPtr()->getAngle()), idColl->getFirstObjectPtr()->getY()+idColl->getFirstObjectPtr()->getSize()*sin(idColl->getSecondObjectPtr()->getAngle()), idColl->getSecondObjectPtr()->getAngle(), idColl->getFirstObjectPtr()->getSize()/(rand()%2+3), idColl->getSecondObjectPtr()->getSpeed()/15.0, FX_VISUAL_TYPE_ELLIPSE/*, this*/);
//				} else {
//					fxPtr->addBlood(idColl->getFirstObjectPtr()->getX()+idColl->getFirstObjectPtr()->getSize()*cos(idColl->getSecondObjectPtr()->getAngle()), idColl->getFirstObjectPtr()->getY()+idColl->getFirstObjectPtr()->getSize()*sin(idColl->getSecondObjectPtr()->getAngle()), idColl->getSecondObjectPtr()->getAngle(), idColl->getFirstObjectPtr()->getSize()/(rand()%2+3), idColl->getSecondObjectPtr()->getSpeed()/10.0, FX_VISUAL_TYPE_ELLIPSE/*, this*/);
//				}
//			
//				if(idColl->getSecondObjectPtr()->getPenCount()!=-1) {
//					idColl->getSecondObjectPtr()->pen();
//				}
//			//}
//
//			//std::list<ENEMY>::iterator temp = dynamic_cast<ENEMY*>(idColl);
//			//B* my_b = dynamic_cast<B*>(my_a);
//
//			//idColl->getFirstObjectPtr()->
//			idColl->getFirstObjectPtr()->takeDamage(idColl->getSecondObjectPtr()->getDamage());//(/*idColl->getSecondObjectPtr()->getDamage()*/3.0);
//
//			//actions with this game object
//			idColl->makeOld();
//			idColl->checkNextTime();
//		}
//	}
//}
//
////delete old collisions
//void PhysicsManager::deleteOldCollisions() {
//  std::list<COLLISION>::iterator idxColl = collisionsList.begin();
//  while (idxColl != collisionsList.end())
//  {
//    if (!idxColl->isCheck())
//    {
//      collisionsList.erase(idxColl);
//      idxColl = collisionsList.begin();
//    }
//    else
//      ++idxColl;
//  }
//
//  //uncheck remaining
//  for (idxColl = collisionsList.begin(); idxColl != collisionsList.end(); ++idxColl)
//	  idxColl->uncheck();
//}
//
//void PhysicsManager::cleanUpMissiles(void) {
//	//for(std::list<MISSILE>::iterator idMissile=missilesList->begin(); idMissile!=missilesList->end(); ++idMissile) {
//	//	if(idMissile->getPenCount()==0 || idMissile->getX()<0 || idMissile->getY()<0 || idMissile->getX()>RESOLUTION_X || idMissile->getY()>RESOLUTION_Y) {
//	//		idMissile->setMissileUnused();
//	//	}
//	//}
//
//  //delete them
//	//std::list<MISSILE>::iterator i = missilesList->begin();
//	//while (i != missilesList->end()) {
//	//	if (i->isUnused())
//	//	{
//	//	missilesList->erase(i);
//	//	i = missilesList->begin();
//	//	}
//	//	else
//	//	++i;
//	//}
//}
//
////void PhysicsManager::processEnemies(float deltaTime) {
////	float px = playerPtr->getX(),
////		   py = playerPtr->getY();
////
////	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
////		if(i->isAlive()) {
////			if(i->getRole()==ENEMY_ROLE_GUARD) {
////				if(isVision(i->itSelf(), playerPtr, intersectCoords)) {
////					if(i->distance(playerPtr) > i->getSize()+playerPtr->getSize()+ATTACK_RANGE_MELEE) {
////						enemyMoveTo(i,deltaTime,px,py);
////					}
////				} else if(DEBUGVAR_ALLOW_BOT_WAY_SEARCHING) {
////					if(dbc(px, py, intersectCoords[0], intersectCoords[1]) < dbc(px, py, intersectCoords[2], intersectCoords[3])) {
////						// lxy1
////						float a = abc(intersectCoords[2], intersectCoords[3],intersectCoords[0], intersectCoords[1]);
////						float lx1 = intersectCoords[0] + i->getSize() * cos( a );
////						float ly1 = intersectCoords[1] + i->getSize() * sin( a );
////						enemyMoveTo(i,deltaTime,lx1,ly1);
////						//i->move(deltaTime, lx1, ly1);
////						//if(checkForPlacementCollision(i->itSelf())) {
////						//	i->restoreXY();
////
////						//	int a=180;
////						//	float d=i->distance(playerPtr);
////
////						//	for(int j=0; j<360; j+=10) {
////						//		i->correct(deltaTime, lx1, ly1, j);
////						//		if(!checkForPlacementCollision(i->itSelf())) {
////						//			if(i->distance(playerPtr)<d) {
////						//				d=i->distance(playerPtr);
////						//				a=j;
////						//			}
////						//		}
////						//	}
////
////						//	if(a!=180) {
////						//		i->correct(deltaTime, lx1, ly1, a);
////						//	} else {
////						//		i->restoreXY();
////						//	}
////						//}
////					} else {
////						// lxy2
////						float a = abc(intersectCoords[0], intersectCoords[1],intersectCoords[2], intersectCoords[3]);
////						float lx1 = intersectCoords[2] + i->getSize() * cos(  a );
////						float ly1 = intersectCoords[3] + i->getSize() * sin(  a );
////						enemyMoveTo(i,deltaTime,lx1,ly1);
////						//i->move(deltaTime, lx1,ly1);
////						//if(checkForPlacementCollision(i->itSelf())) {
////						//	i->restoreXY();
////
////						//	int a=180;
////						//	float d=i->distance(playerPtr);
////
////						//	for(int j=0; j<360; j+=10) {
////						//		i->correct(deltaTime, lx1,ly1, j);
////						//		if(!checkForPlacementCollision(i->itSelf())) {
////						//			if(i->distance(playerPtr)<d) {
////						//				d=i->distance(playerPtr);
////						//				a=j;
////						//			}
////						//		}
////						//	}
////
////						//	if(a!=180) {
////						//		i->correct(deltaTime, lx1,ly1, a);
////						//	} else {
////						//		i->restoreXY();
////						//	}
////						//}
////					}
////				}
////			} else if(i->getRole()==ENEMY_ROLE_NEUTRAL) {
////				
////				if(dbc(i->getX(),i->getY(),i->getToX(),i->getToY())<i->getSize()) {
////					float _x,_y;
////					do {
////						_x=rand()%RESOLUTION_X;
////						_y=rand()%RESOLUTION_Y;
////					} while(!(isPointFree(_x,_y,i->getSize())));
////					i->setTo(_x,_y);
////				} else {
////					enemyMoveTo(i,deltaTime,i->getX(),i->getY());
////					//i->move(deltaTime,i->getToX(),i->getToY());
////					//if(checkForPlacementCollision(i->itSelf())) {
////					//	i->restoreXY();
////
////					//	int a=180;
////					//	float d=i->distance(playerPtr);
////
////					//	for(int j=0; j<360; j+=10) {
////					//		i->correct(deltaTime, i->getToX(),i->getToY(), j);
////					//		if(!checkForPlacementCollision(i->itSelf())) {
////					//			if(i->distance(playerPtr)<d) {
////					//				d=i->distance(playerPtr);
////					//				a=j;
////					//			}
////					//		}
////					//	}
////
////					//	if(a!=180) {
////					//		i->correct(deltaTime, i->getToX(),i->getToY(), a);
////					//	} else {
////					//		i->restoreXY();
////					//	}
////					//}
////				}
////			}
////
////			if(i->distance(playerPtr) > FAR_DISTANCE) {
////				i->kill();
////			}
////		}
////	}
////}
//
//void PhysicsManager::drawBlocks(HDC bhdc) {
//	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
//		i->draw(bhdc);
//	}
//}
//
//void PhysicsManager::computeShadows(HDC bhdc, float x, float y) {
//	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
//		i->computeShadows(bhdc, x, y);
//	}
//}
//
//void PhysicsManager::processCollisions(void) {
//	checkCollisions();
//	processNewCollisions();
//	deleteOldCollisions();
//}
//
//void PhysicsManager::setGOheight(float h) {
//	playerPtr->setHeight(h);
//	//for(std::list<MISSILE>::iterator i=missilesList->begin(); i!=missilesList->end(); ++i) {
//	//	i->setHeight(h);
//	//}
//	for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
//		i->setHeight(h);
//	}
//	for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
//		i->setHeight(h);
//	}
//}
//
//int PhysicsManager::getCollisionsCount() {return collisionsList.size();}
//int PhysicsManager::getBlocksCount() {return blocksList.size();}
//int PhysicsManager::getRoadsCount() {return roadsList.size();}
//int PhysicsManager::getShellsCount() {return fxPtr->getShellsList()->size();}
//
//void PhysicsManager::removeBlocks() {blocksList.clear();}
//
//void PhysicsManager::placeBlock(float newX, float newY, float newW, float newH) {
//	if(DEBUGVAR_INCLUDE_BLOCKS) blocksList.push_back(BLOCK(newX,newY,newW,newH,penPtr));
//}
//
//void PhysicsManager::drawNoises(HDC bhdc) {
//	for(std::vector<NOISE>::iterator i=noisesVector.begin(); i!=noisesVector.end(); ++i) {
//		i->draw(bhdc);
//	}
//}
//
//void PhysicsManager::drawRoads(HDC bhdc) {
//	for(std::list<ROAD>::iterator i=roadsList.begin(); i!=roadsList.end(); ++i) {
//	}
//}
//
//void PhysicsManager::deposeNoises(float X, float Y) {
//	for(std::vector<NOISE>::iterator i=noisesVector.begin(); i!=noisesVector.end(); ++i) {
//		i->depose(X, Y);
//	}
//}
//
//float PhysicsManager::getCameraOffsetX() {return offsetFromCenterX;}
//float PhysicsManager::getCameraOffsetY() {return offsetFromCenterY;}
//
//void PhysicsManager::createNoise(int newX, int newY, int newRadius) {
//	noisesVector.push_back(NOISE(newX,newY,newRadius,noisePenPtr));
//}
//
//void PhysicsManager::createRoad(float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy) {
//	if(DEBUGVAR_INCLUDE_ROADS) roadsList.push_back(ROAD(ax,ay,bx,by,cx,cy,dx,dy,roadPenPtr));
//}
//
//void PhysicsManager::init(std::list<ENEMY> *e, Player *p, FX_MANAGER *f, HPEN *ptr, HPEN *newNoisePenPtr, HPEN *newRoadPenPtr) {
//	playerPtr = p;
//	enemiesList = e;
//	fxPtr = f;
//	penPtr = ptr;
//	roadPenPtr = newRoadPenPtr;
//	noisePenPtr = newNoisePenPtr;
//	offsetFromCenterX = 0;
//	offsetFromCenterY = 0;
//	dx[0] = -1;
//	dy[0] = 0;
//	dx[1] = 0;
//	dy[1] = -1;
//	dx[2] = 1;
//	dy[2] = 0;
//	dx[3] = 0;
//	dy[3] = 1;
//}
//
//std::list<BLOCK> *PhysicsManager::getBlocksListPtr() {return &blocksList;}
