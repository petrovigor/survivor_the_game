#ifndef __CAMERA_H
#define __CAMERA_H

#define CAMERA_RATE (0.5f)

#include "player.h"
#include "physics.h"

class e4_camera {
private:
	float x, y;
	float rate;
	e4_physics *physicsPtr;
	e4_player *playerPtr;

public:
	e4_camera(void);

	void init(e4_physics *physicsPtr, e4_player *playerPtr);
	void moveCamera(float dx, float dy);
	void setCameraRate(float rate);

	float getX(void);
	float getY(void);
};

#endif