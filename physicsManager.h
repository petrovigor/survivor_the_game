#ifndef __PHYSICS_MANAGER_H
#define __PHYSICS_MANAGER_H

#include <list>
#include "enemy.h"
#include "missile.h"
#include "collision.h"
#include "player.h"
#include "fxManager.h"
#include "block.h"
#include "noise.h"
#include "road.h"

class PHYSICS_MANAGER {
private:
	PLAYER *playerPtr;
	FX_MANAGER *fxPtr;

	HPEN *penPtr;
	HPEN *noisePenPtr;
	HPEN *roadPenPtr;

	int dx[4], dy[4];

	std::list<COLLISION> collisionsList;
	std::list<MISSILE> *missilesList;
	std::list<ENEMY> *enemiesList;

	std::list<ROAD> roadsList;
	std::list<BLOCK> blocksList;
	std::vector<NOISE> noisesVector;

	void checkCollisions(void);
	void processNewCollisions(void);
	void deleteOldCollisions(void);
	bool checkIfCollisionExists(const GAME_OBJECT *f, const MISSILE *s);

	double offsetFromCenterY,offsetFromCenterX;

public:
	void init(std::list<ENEMY> *e, std::list<MISSILE> *m, PLAYER *p, FX_MANAGER *f, HPEN *ptr, HPEN *newNoisePenPtr, HPEN *newRoadPenPtr) {
		playerPtr = p;
		enemiesList = e;
		missilesList = m;
		fxPtr = f;
		penPtr = ptr;
		roadPenPtr = newRoadPenPtr;
		noisePenPtr = newNoisePenPtr;
		offsetFromCenterX = 0;
		offsetFromCenterY = 0;
		dx[0] = -1;
		dy[0] = 0;
		dx[1] = 0;
		dy[1] = -1;
		dx[2] = 1;
		dy[2] = 0;
		dx[3] = 0;
		dy[3] = 1;
	}

	std::list<BLOCK> *getBlocksListPtr() {return &blocksList;}

	bool col(double,double,double,double,double,double,double,double);

	void createRoad(double ax,double ay,double bx,double by,double cx,double cy,double dx,double dy) {
		if(DEBUGVAR_INCLUDE_ROADS) roadsList.push_back(ROAD(ax,ay,bx,by,cx,cy,dx,dy,roadPenPtr));
	}

	void setCameraOffsetValue(double X, double Y);
	double getCameraOffsetX() {return offsetFromCenterX;}
	double getCameraOffsetY() {return offsetFromCenterY;}

	void createNoise(int newX, int newY, int newRadius) {
		noisesVector.push_back(NOISE(newX,newY,newRadius,noisePenPtr));
	}

	void processNoises(double deltaTime);

	void drawNoises(HDC bhdc) {
		for(std::vector<NOISE>::iterator i=noisesVector.begin(); i!=noisesVector.end(); ++i) {
			i->draw(bhdc);
		}
	}

	void drawRoads(HDC bhdc) {
		for(std::list<ROAD>::iterator i=roadsList.begin(); i!=roadsList.end(); ++i) {
			i->draw(bhdc);
		}
	}

	void deposeNoises(double X, double Y) {
		for(std::vector<NOISE>::iterator i=noisesVector.begin(); i!=noisesVector.end(); ++i) {
			i->depose(X, Y);
		}
	}

	void removeNoises();

	void setGOheight(double h) {
		playerPtr->setHeight(h);
		for(std::list<MISSILE>::iterator i=missilesList->begin(); i!=missilesList->end(); ++i) {
			i->setHeight(h);
		}
		for(std::list<ENEMY>::iterator i=enemiesList->begin(); i!=enemiesList->end(); ++i) {
			i->setHeight(h);
		}
		for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
			i->setHeight(h);
		}
	}

	//void findWayToPlayer(std::list<ENEMY>::iterator,double,double);
	void computeRandomPointToPatrol(std::list<ENEMY>::iterator);
	void enemyMoveTo(std::list<ENEMY>::iterator,double,double,double);
	void placeBlockByPlayerDirection(const int);
	void placeRoadByPlayerDirection(const int);
	void removeFarBlocks(double,double,double);
	void deposeGameObjects(double offsetX, double offsetY);
	
	
	void deposeGameObjectsFromCenter();


	bool checkForPlacementCollision(double,double,double,double);
	void correctPlayerPlacement(const int playerDir, double deltaTime);
	void movePlayer(double deltaTime, const int playerDir);
	void processEnemies(double deltaTime);
	void moveMissiles(double deltaTime);
	void moveAll(double deltaTime, const int playerDir);
	bool checkForPlacementCollision(GAME_OBJECT *go);
	bool isPointFree(double X, double Y, double R);
	//bool checkCoordsForPlacementCollision(double X, double Y);

	void removeBlocks() {blocksList.clear();}

	void placeBlock(double newX, double newY, double newW, double newH) {
		if(DEBUGVAR_INCLUDE_BLOCKS) blocksList.push_back(BLOCK(newX,newY,newW,newH,penPtr));
	}

	int isVisionSmart(GAME_OBJECT *A, GAME_OBJECT *B, double *coords, int *count);
	bool isVision(GAME_OBJECT *A, GAME_OBJECT *B);

	void drawBlocks(HDC bhdc) {
		for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
			i->draw(bhdc);
		}
	}

	// draw dynamic shadows
	void computeShadows(HDC bhdc, double x, double y) {
		for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
			//first point of block (x1/y1)
			//MoveToEx(bhdc, playerPtr->getX(), playerPtr->getY(), 0);
			//LineTo(bhdc, 

			i->computeShadows(bhdc, x, y);
			//i->computeShadows(bhdc, playerPtr->getX(), playerPtr->getY());
		}
	}

	void processCollisions(void) {
		checkCollisions();
		processNewCollisions();
		deleteOldCollisions();
	}

	void correctEnemies();

	void cleanUpMissiles();

	int getCollisionsCount(void) {return collisionsList.size();}
	int getBlocksCount(void) {return blocksList.size();}
	int getRoadsCount(void) {return roadsList.size();}
	int getShellsCount(void) {return fxPtr->getShellsList()->size();}
};

#endif