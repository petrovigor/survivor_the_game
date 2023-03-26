#pragma once

#include "types.h"
#include "point.h"
#include <Windows.h>
//#include "hdc_declaration.h"

//#include <cstdint>
//#include <Windows.h>

enum class GameObjectVisualType {
  Square  = 1,
  Ellipse = 2
};

class GameObject {
protected:
  uint32_t id;
  worldPoint p;
  float32 speed;
  float32 angle;
  float32 size;

  GameObjectVisualType visualType;
	//float cameraOffsetX, cameraOffsetY;

public:
	GameObject();
  GameObject(uint32_t id, worldPoint _p, float32 speed, float32 angle, GameObjectVisualType vt);
  GameObject(uint32_t id, float32 x, float32 y, float32 speed, float32 angle, float32 size_, GameObjectVisualType vt);
  virtual ~GameObject();

  float32 getX() const noexcept;
  float32 getY() const noexcept;
  worldPoint getP() const noexcept;
  uint32_t getId() const noexcept;

  //void setCameraOffset(float32 x, float32 y);
  //virtual void depose(float32 dx, float32 dy);
  virtual void processPhysics(float32 dt);
  virtual void draw(HDC bhdc, worldPoint playerPosition);

};


