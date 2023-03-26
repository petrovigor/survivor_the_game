#pragma once

#include "game_object.h"

class Projectile : public GameObject {
public:
	Projectile(float32 x, float32 y, float32 speed, float32 angle, float32 size);

};
