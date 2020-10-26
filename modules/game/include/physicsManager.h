#pragma once

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
	Player *playerPtr;
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
	bool checkIfCollisionExists(const GameObject *f, const MISSILE *s);

	float offsetFromCenterY,offsetFromCenterX;

public:
	void init(std::list<ENEMY> *e, std::list<MISSILE> *m, Player *p, FX_MANAGER *f, HPEN *ptr, HPEN *newNoisePenPtr, HPEN *newRoadPenPtr) {
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

	bool col(float,float,float,float,float,float,float,float);

	void createRoad(float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy) {
		if(DEBUGVAR_INCLUDE_ROADS) roadsList.push_back(ROAD(ax,ay,bx,by,cx,cy,dx,dy,roadPenPtr));
	}

	void setCameraOffsetValue(float X, float Y);
	float getCameraOffsetX() {return offsetFromCenterX;}
	float getCameraOffsetY() {return offsetFromCenterY;}

	void createNoise(int newX, int newY, int newRadius) {
		noisesVector.push_back(NOISE(newX,newY,newRadius,noisePenPtr));
	}

	void processNoises(float deltaTime);

	void drawNoises(HDC bhdc) {
		for(std::vector<NOISE>::iterator i=noisesVector.begin(); i!=noisesVector.end(); ++i) {
			i->draw(bhdc);
		}
	}

	void drawRoads(HDC bhdc) {
		for(std::list<ROAD>::iterator i=roadsList.begin(); i!=roadsList.end(); ++i) {
		}
	}

	void deposeNoises(float X, float Y) {
		for(std::vector<NOISE>::iterator i=noisesVector.begin(); i!=noisesVector.end(); ++i) {
			i->depose(X, Y);
		}
	}

	void removeNoises();

	void setGOheight(float h) {
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

	void computeRandomPointToPatrol(std::list<ENEMY>::iterator);
	void enemyMoveTo(std::list<ENEMY>::iterator,float,float,float);
	void placeBlockByPlayerDirection(const int);
	void placeRoadByPlayerDirection(const int);
	void removeFarBlocks(float,float,float);
	void deposeGameObjects(float offsetX, float offsetY);
	
	
	void deposeGameObjectsFromCenter();


	bool checkForPlacementCollision(float,float,float,float);
	void correctPlayerPlacement(const int playerDir, float deltaTime);
	void movePlayer(float deltaTime, const int playerDir);
	void processEnemies(float deltaTime);
	void moveMissiles(float deltaTime);
	void moveAll(float deltaTime, const int playerDir);
	bool checkForPlacementCollision(GameObject *go);
	bool isPointFree(float X, float Y, float R);

	void removeBlocks() {blocksList.clear();}

	void placeBlock(float newX, float newY, float newW, float newH) {
		if(DEBUGVAR_INCLUDE_BLOCKS) blocksList.push_back(BLOCK(newX,newY,newW,newH,penPtr));
	}

	int isVisionSmart(GameObject *A, GameObject *B, float *coords, int *count);
	bool isVision(GameObject *A, GameObject *B);

	void drawBlocks(HDC bhdc) {
		for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
			i->draw(bhdc);
		}
	}

	void computeShadows(HDC bhdc, float x, float y) {
		for(std::list<BLOCK>::iterator i=blocksList.begin(); i!=blocksList.end(); ++i) {
			i->computeShadows(bhdc, x, y);
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
