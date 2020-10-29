#pragma once

#include "game_object.h"

class Player final : public GameObject {
private:
  bool attacking;
  bool isCooldown;
  float attackTargetX;
  float attackTargetY;
  float cooldown;

public:
  Player(float _x, float _y, float _speed);

  void attack(float targetX, float targetY);
  void processPhysics(float dt) override;

};
