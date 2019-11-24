#include "physics.h"

e4_physics::e4_physics(void) {
	ptrPlayer = nullptr;
	ptrKeyboard = nullptr;
	camX = 0.0f;
	camY = 0.0f;
	//DBG missilesToRender = missilesNotToRender = 0;
}

void e4_physics::init(e4_player *pptr, e4_keyboard *kptr/*, e4_camera *cptr*/) {
	ptrPlayer = pptr;
	ptrKeyboard = kptr;
	//ptrCamera = cptr;
}

void e4_physics::addBlock(e4_block b) {
	//blockList.push_back(b);
}

void e4_physics::addMissile(e4_missile m) {
	missileList.push_back(m);
}

void e4_physics::addCrossway(e4_crossway r) {
	crosswayList.push_back(r);
}

void e4_physics::removeBlocks(void) {
	blockList.clear();
}

void e4_physics::removeMissiles(void) {
	missileList.clear();
}

void e4_physics::removeCrossways(void) {
	crosswayList.clear();
}

void e4_physics::processCrossways(void) {
	std::vector<e4_crossway_data> data;
	std::vector<e4_road>::iterator rit;
	std::vector<e4_crossway>::iterator cwit;
	std::vector<e4_road> rlist;

	for(cwit = crosswayList.begin(); cwit != crosswayList.end(); ++cwit) {
		rlist = cwit->getRoadList();

		if(  !(cwit->isUnfolded()) &&   cwit->isOpened()   ) {

			for(rit = rlist.begin(); rit != rlist.end(); ++rit) {
				switch(rit->getDirection()) {
				case A:
					data.push_back(e4_crossway_data(rit->getX(), rit->getY() - rit->getRange() - ROAD_SIZE, C));
					break;
				case B:
					data.push_back(e4_crossway_data(rit->getX() + rit->getRange() + ROAD_SIZE, rit->getY(), D));
					break;
				case C:
					data.push_back(e4_crossway_data(rit->getX(), rit->getY() + rit->getRange() + ROAD_SIZE, A));
					break;
				case D:
					data.push_back(e4_crossway_data(rit->getX() - rit->getRange() - ROAD_SIZE, rit->getY(), B));
					break;
				}
			}

			cwit->Unfold();
		} else if(   !(cwit->isOpened()) && !(cwit->isUnfolded())      ) {
			if(DistanceBetweenCoords(320.0f, 240.0f, cwit->getX(), cwit->getY()) <= 700.0f) {
				cwit->Open();
				cwit->init(cwit->getX(), cwit->getY(), rand()%3+1);
			}
		}
	}

	for(std::vector<e4_crossway_data>::iterator p = data.begin(); p != data.end(); ++p) {
		addCrossway(e4_crossway(p->x, p->y, p->sourceDir, false));
	}

	for(cwit = crosswayList.begin(); cwit != crosswayList.end(); ++cwit) {
		cwit->deleteFarRoads();
	}

	// remove unused crossways
	cwit = crosswayList.begin();
	while(cwit != crosswayList.end()) {
		if(cwit->isToDelete()) {
			crosswayList.erase(cwit);
			cwit = crosswayList.begin();
		} else {
			++cwit;
		}
	}
}

void e4_physics::drawBlocks(HDC memDC) {
	float px = ptrPlayer->getX(),
		  py = ptrPlayer->getY();

	for(std::vector<e4_block>::iterator it = blockList.begin(); it != blockList.end(); ++it) {
		it -> draw(memDC, px, py);
	}
}

void e4_physics::drawMissiles(HDC memDC) {
	for(std::vector<e4_missile>::iterator it = missileList.begin(); it != missileList.end(); ++it) {
		it -> draw(memDC);
	}
}

void e4_physics::drawCrossways(HDC memDC) {
	for(std::vector<e4_crossway>::iterator it = crosswayList.begin(); it != crosswayList.end(); ++it) {
		it -> draw(memDC);
	}
}

void e4_physics::processMissiles(float deltaTime) {
	for(std::vector<e4_missile>::iterator it = missileList.begin(); it != missileList.end(); ++it) {
		if(it -> isActive()) {
			it -> move(deltaTime);
		}
	}
}

void e4_physics::setCameraCoordinates(float cx, float cy) {
	camX = cx;
	camY = cy;

	ptrPlayer->setCameraCoordinates(cx, cy);

	for(std::vector<e4_missile>::iterator it = missileList.begin(); it != missileList.end(); ++it) {
		it->setCameraCoordinates(cx, cy);
	}

	for(std::vector<e4_block>::iterator it = blockList.begin(); it != blockList.end(); ++it) {
		it->setCameraCoordinates(cx, cy);
	}

	//for(std::vector<e4_road>::iterator it = roadList.begin(); it != roadList.end(); ++it) {
	//	it -> setCameraCoordinates(cx, cy);
	//}

	for(std::vector<e4_crossway>::iterator it = crosswayList.begin(); it != crosswayList.end(); ++it) {
		it->setCameraCoordinates(cx, cy);
	}
}

void e4_physics::updatePlayerDirection(void) {
	int x = 0,
		y = 0;

	if(ptrKeyboard->isKey('A')) {
		x--;
	}

	if(ptrKeyboard->isKey('D')) {
		x++;
	}

	if(ptrKeyboard->isKey('W')) {
		y--;
	}

	if(ptrKeyboard->isKey('S')) {
		y++;
	}

	if(x == 0 && y == 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_IDLE);
		return;
	}

	if(x > 0 && y == 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_E);
		return;
	}

	if(x < 0 && y == 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_W);
		return;
	}

	if(x == 0 && y > 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_S);
		return;
	}

	if(x == 0 && y < 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_N);
		return;
	}

	if(x > 0 && y > 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_SE);
		return;
	}

	if(x < 0 && y < 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_NW);
		return;
	}

	if(x > 0 && y < 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_NE);
		return;
	}

	if(x < 0 && y > 0) {
		ptrPlayer->setDirection(PLAYER_DIRECTION_SW);
		return;
	}
}

void e4_physics::processCollisions(void) {
	float x, y;

	for(std::vector<e4_missile>::iterator m = missileList.begin(); m != missileList.end(); ++m) {
		if(m -> isActive()) {
			x = m->getX();
			y = m->getY();

			if(DistanceBetweenCoords(x, y, ptrPlayer->getX(), ptrPlayer->getY()) > 1000.0f) {
				m->deactivate();
				continue;
			}

			//if(x < 25 || x > 615 || y < 25 || y > 455) {
			//	m->deactivate();
			//	continue;
			//}

			for(std::vector<e4_block>::iterator b = blockList.begin(); b != blockList.end(); ++b) {
				if(b->isCoordInBlock(x, y, m->getRadius(), m->getRadius())) {
					m->deactivate();
				}
			}
		}
	}
}

void e4_physics::processUnusedObjects(void) {
	WRN

	for(std::vector<e4_missile>::iterator m = missileList.begin(); m != missileList.end(); ++m) {
		if(!(m->isActive())) {
			missileList.erase(m);
			m = missileList.begin();

			if(m == missileList.end()) {
				break;
			}
		}
	}
}

void e4_physics::offsetObjects(float dx, float dy) {
	for(std::vector<e4_block>::iterator b = blockList.begin(); b != blockList.end(); ++b) {
		b->offset(dx, dy);
	}

	for(std::vector<e4_missile>::iterator m = missileList.begin(); m != missileList.end(); ++m) {
		m->offset(dx, dy);
	}

	for(std::vector<e4_crossway>::iterator cw = crosswayList.begin(); cw != crosswayList.end(); ++cw) {
		cw->offset(dx, dy);
	}
}

void e4_physics::checkRender(void) {
	for(std::vector<e4_block>::iterator b = blockList.begin(); b != blockList.end(); ++b) {
		b->checkRender();
	}

	for(std::vector<e4_missile>::iterator m = missileList.begin(); m != missileList.end(); ++m) {
		m->checkRender();
	}

	for(std::vector<e4_crossway>::iterator cw = crosswayList.begin(); cw != crosswayList.end(); ++cw) {
		cw->checkRender();
	}
}

bool e4_physics::processPlayerCollisions(void) {
	float px = ptrPlayer->getX(),
		  py = ptrPlayer->getY(),
		  r = ptrPlayer->getRadius();

	for(std::vector<e4_block>::iterator b = blockList.begin(); b != blockList.end(); ++b) {
		if(b->isCoordInBlock(px, py, r, r)) {
			//ptrPlayer->restoreXY();
			return true;
		}
	}

	return false;
}

int e4_physics::getCrosswaysCount(void) {
	return crosswayList.size();
}

int e4_physics::getRoadsCount(void) {
	int c = 0;

	for(std::vector<e4_crossway>::iterator it = crosswayList.begin(); it != crosswayList.end(); ++it) {
		c += (it->getRoadsCount());
	}

	return c;
}

void e4_physics::addBlocksByPlayerDirection(void) {
	DBG const int maximalBlocksAtMap = 9;

	if(getBlockCount() >= maximalBlocksAtMap) {
		return;
	}

	int dir = ptrPlayer->getDirection();

	float x = 0.0f;
	float y = 0.0f;

	switch(dir) {
	case PLAYER_DIRECTION_IDLE:
		return;
		
	case PLAYER_DIRECTION_N:
	    x = (float)(rand()%640);
	    y = 0.0f;
		break;

	case PLAYER_DIRECTION_S:
	    x = (float)(rand()%640);
	    y = 480.0f;
		break;

	case PLAYER_DIRECTION_W:
	    x = 0.0f;
	    y = (float)(rand()%480);
		break;

	case PLAYER_DIRECTION_E:
	    x = 640.0f;
	    y = (float)(rand()%480);
		break;

	case PLAYER_DIRECTION_NE:
	case PLAYER_DIRECTION_SE:
	case PLAYER_DIRECTION_NW:
	case PLAYER_DIRECTION_SW:
	    x = (float)(rand()%640);
	    y = (float)(rand()%480);
		break;
	}

	float hw = (float)(rand()%200+100);
	float hh = (float)(rand()%200+100);

	if(!(presumeCollisionRectangle(x, y, hw, hh))) {
		addBlock(e4_block(x, y, hw, hh, BLOCK_TYPE_DEFAULT));
	}

		/*&&
		ptrPlayer->getX() - ptrPlayer->getRadius() > b.getX() + b.getHalfWidth()*/

		//blockList.push_back(b);
	//} else {
	//	b.~b();
	//}

	//if( presumeCollisionRectangle(b.getX(), b.getY(), b.getHalfWidth(), b.getHalfHeight()) ) {
		//blockList.push_back(b);
	//} else {
	//	b.~b();

	//} else {

	//	b.~b();

	//}

	
}

void e4_physics::processPhysics(float deltaTime) {
	const float cx = (640.0f / 2.0f);
	const float cy = (480.0f / 2.0f);
	
	ptrPlayer->move(deltaTime);

	if(!processPlayerCollisions()) {
		offsetObjects(cx - ptrPlayer->getX(), cy - ptrPlayer->getY());
		addBlocksByPlayerDirection();
	}

	ptrPlayer->setXY(cx, cy);

	processMissiles(deltaTime);
	processCollisions();
	processUnusedObjects();
	
	deleteFarBlocks();
	processCrossways();
	checkRender();

	//DBG

	//missilesToRender = 0;

	//for(std::vector<e4_missile>::iterator m = missileList.begin(); m != missileList.end(); ++m) {
	//	if(m->isToRender()) {
	//		++missilesToRender;
	//	}
	//}
}

int e4_physics::getMissilesCount(void) {
	return missileList.size();
}

int e4_physics::getBlockCount(void) {
	return blockList.size();
}

//DBG int e4_physics::getRenderedMissiles(void) {
//	return missilesToRender;
//}
//
//DBG int e4_physics::getUnrenderedMissiles(void) {
//	return missilesNotToRender;
//}

//inline void placeBlocksByCount(int c) {
//}

void e4_physics::deleteFarBlocks(void) {
	//delete old blocks (far distance from player)

	std::vector<e4_block>::iterator b;

	for(b = blockList.begin(); b != blockList.end(); ++b) {
		if( DistanceBetweenCoords( 320.0f, 240.0f, b->getX(), b->getY()) >= 1000.0f ) {
			b->toDelete();
		}
	}

	b = blockList.begin();
	while(b != blockList.end()) {
		if(b->isToDelete()) {
			blockList.erase(b);
			b = blockList.begin();
		} else {
			++b;
		}
	}
}

bool e4_physics::presumeCollisionRectangle(float x, float y, float hw, float hh) {
	// check if player not collides with rectangle

	const float px = 320.0f; // Player ALWAYS
	const float py = 240.0f; // AT MAP CENTER
	const float pr = ptrPlayer->getRadius();

	if( px-pr < x+hw && px+pr > x-hw && py-pr < y+hh && py+pr > y-hh ) {
		//player collision detected
		return true;
	}

	//additional size to block width and height when placing
	const float safeWIDTH = 50.0f;

	for(std::vector<e4_block>::iterator it = blockList.begin(); it != blockList.end(); ++it) {
		if(it->isCoordInBlock(x, y, hw+safeWIDTH, hh+safeWIDTH)) {
			//block collision detected
			return true;
		}
	}

	for(std::vector<e4_crossway>::iterator it = crosswayList.begin(); it != crosswayList.end(); ++it) {
		if(it->presumeCollisionRectange(x, y, hw+safeWIDTH, hh+safeWIDTH)) {
			//crossway collision detected
			return true;
		}
	}

	//no collision detected
	return false;
}