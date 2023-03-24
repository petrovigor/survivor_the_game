#pragma once

#include "game_object.h"

class Car final : public GameObject {
private:
  uint32_t cell_target;

public:
  Car(uint32_t cell_at, uint32_t cell_to, float32 _speed);

  void draw(HDC bhdc, const worldPoint &playerPos, float32 cox, float32 coy) override;
  void processPhysics(float32 dt) override;

};
