#ifndef __PHYSICS_H
#define __PHYSICS_H

#ifndef WRN
#define WRN //warning
#endif

#ifndef DBG
#define DBG //debug only
#endif

#include <vector>
#include "player.h"
#include "keyboard.h"
#include "block.h"
#include "missile.h"
#include "crossway.h"
//#include "camera.h"

class e4_physics {
private:
	e4_player *ptrPlayer;
	e4_keyboard *ptrKeyboard;
	//e4_camera *ptrCamera;

	std::vector<e4_block> blockList;
	std::vector<e4_missile> missileList;
	std::vector<e4_crossway> crosswayList;

	float camX, camY;

public:
	e4_physics(void);

	void init(e4_player *pptr, e4_keyboard *kptr/*, e4_camera *cptr*/);

	void updatePlayerDirection(void);
	void processPhysics(float deltaTime);

	void addBlock(e4_block b);
	void addBlocksByPlayerDirection(void);
	void removeBlocks(void);
	void drawBlocks(HDC memDC);
	void deleteFarBlocks(void);
	int getBlockCount(void);

	void addMissile(e4_missile m);
	void removeMissiles(void);
	void drawMissiles(HDC memDC);
	void processMissiles(float deltaTime);
	int getMissilesCount(void);

	void addCrossway(e4_crossway cw);
	void removeCrossways(void);
	void processCrossways(void);
	void drawCrossways(HDC memDC);
	int getCrosswaysCount(void);
	int getRoadsCount(void);

	void processCollisions(void);
	bool processPlayerCollisions(void);
	void processUnusedObjects(void);

	void setCameraCoordinates(float cx, float cy);
	void offsetObjects(float dx, float dy);

	//DBG int missilesToRender;
	//DBG int missilesNotToRender;

	//DBG int getUnrenderedMissiles(void);
	//DBG int getRenderedMissiles(void);

	void checkRender(void);

	bool presumeCollisionRectangle(float x, float y, float hw, float hh);
};

#endif