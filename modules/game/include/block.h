#pragma once

#include "types.h"
#include "game_object.h"
#include "point.h"

class Block final : public GameObject {
private:
  float32 width, height;
	//float32 bx[4], by[4];


public:
	Block(float32 newX, float32 newY, float32 newW, float32 newH);

  void draw(HDC bhdc, const worldPoint &wp) override;
	//void depose(float32 x, float32 y) override;

};
