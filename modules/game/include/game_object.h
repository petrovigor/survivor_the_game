#pragma once

#include <Windows.h>

enum class GameObjectVisualType {
  Square  = 1,
  Ellipse = 2
};

class GameObject {
protected:
	float x, y;
	float speed;
	float angle;

  GameObjectVisualType visualType;
	float cameraOffsetX, cameraOffsetY;

public:
	GameObject();
  GameObject(float x, float y, float speed, float angle, GameObjectVisualType vt);
  virtual ~GameObject();

  void setCameraOffset(float x, float y);
  virtual void depose(float dx, float dy);
  virtual void processPhysics(float dt);
  virtual void draw(HDC bhdc);

};


