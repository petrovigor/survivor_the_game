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
	void init(std::list<ENEMY> *e, std::list<MISSILE> *m, Player *p, FX_MANAGER *f, HPEN *ptr, HPEN *newNoisePenPtr, HPEN *newRoadPenPtr);

	std::list<BLOCK> *getBlocksListPtr();

	bool col(float,float,float,float,float,float,float,float);

	void createRoad(float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy);

	void setCameraOffsetValue(float X, float Y);
	float getCameraOffsetX();
	float getCameraOffsetY();

	void createNoise(int newX, int newY, int newRadius);

	void processNoises(float deltaTime);

	void drawNoises(HDC bhdc);

	void drawRoads(HDC bhdc);

	void deposeNoises(float X, float Y);

	void removeNoises();

	void setGOheight(float h);

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

	void removeBlocks();

	void placeBlock(float newX, float newY, float newW, float newH);

	int isVisionSmart(GameObject *A, GameObject *B, float *coords, int *count);
	bool isVision(GameObject *A, GameObject *B);

	void drawBlocks(HDC bhdc);

	void computeShadows(HDC bhdc, float x, float y);

	void processCollisions(void);

	void correctEnemies();

	void cleanUpMissiles();

	int getCollisionsCount();
	int getBlocksCount();
	int getRoadsCount();
	int getShellsCount();
};
