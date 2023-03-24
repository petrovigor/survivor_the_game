#pragma once

#include "game_object.h"

class Player final : public GameObject {
private:
  bool attacking;
  bool isCooldown;
  float32 attackTargetX;
  float32 attackTargetY;
  float32 cooldown;

public:
  Player(float32 _x, float32 _y, float32 _speed);

  void attack(float32 targetX, float32 targetY);
  void draw(HDC bhdc, const worldPoint &playerPos, float32 cox, float32 coy)override;
  void processPhysics(float32 dt) override;

};
