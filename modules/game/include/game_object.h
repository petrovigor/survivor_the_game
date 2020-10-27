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

  //GameObject(int _x, int _y, int _size, int _speed, int _angle);

	//GameObject *itSelf(void);

	float getX() const noexcept;
	float getY() const noexcept;
	//void setXY(float x, float y);
	//void setSpeed(float newSpeed);
	//float getSpeed(void);
	//float getSize(void);
	//void setSize(float value);
	//float getAngle(void);

	//void backupXY(void);
	//void restoreXY(void);

	//float distance(GameObject *obj);

	//float getAngleAt(GameObject *obj);

  void setCameraOffset(float x, float y);
  virtual void depose(float dx, float dy);
  virtual void processPhysics(float dt);
  virtual void draw(HDC bhdc);

	//virtual void takeDamage(float damage);
};


