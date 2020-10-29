#pragma once

#include "game_object.h"

class Block final : public GameObject {
private:
  float w, h;
	float bx[4], by[4];

public:
	Block(float newX, float newY, float newW, float newH);

  void draw(HDC bhdc) override;
	void depose(float x, float y) override;

};
