#ifndef __CROSSWAY_H
#define __CROSSWAY_H

#define _CRT_SECURE_NO_WARNINGS       1
#define _CRT_NON_CONFORMING_SWPRINTFS 1

#include <Windows.h>
#include <vector>
#include "road.h"
#include "routine.h"

class e4_crossway {
private:
	float x, y;
	float cx, cy;
	int sourceDirection; //from which direction crossway was unfolded
	std::vector<e4_road> roads;
	//float px, py;
	int roadCount;
	bool render;
	bool flag[4];
	bool unfolded;
	bool opened;
	bool unused;
	//e4_road *roads;

public:
	e4_crossway(float x, float y, int roadCount);
	e4_crossway(float x, float y, int sourceDir, bool dummyVar); //for closed crossways

	void init(float x, float y, int roadCount);
	void setCameraCoordinates(float cx, float cy);
	void checkRender(void);
	void offset(float dx, float dy);
	void draw(HDC hdc);
	int getRoadsCount(void);

	bool presumeCollisionRectange(float x, float y, float hw, float hh);

	void Open(void);
	void Unfold(void);
	bool isOpened(void);
	bool isUnfolded(void);
	void toDelete(void);
	bool isToDelete(void);

	void deleteFarRoads(void);
	//void updatePlayerCoordinates(float px, float py);

	const std::vector<e4_road> & getRoadList();

	float getX(void);
	float getY(void);

	~e4_crossway(void);
};

#endif
