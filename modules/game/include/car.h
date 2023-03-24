#pragma once

#include "game_object.h"
#include "grid.h"

class Car final : public GameObject {
private:
  cell_indices cell_target;

public:
  Car(cell_indices cell_at, cell_indices cell_to, float32 _speed);

  //void draw(HDC bhdc, const worldPoint &playerPos, float32 cox, float32 coy) override;
  void processPhysics(float32 dt) override;

};
