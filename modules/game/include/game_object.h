#pragma once

#include <Windows.h>

enum class GameObjectVisualType {
  Square  = 1,
  Ellipse = 2
};

class GameObject {
protected:
	bool alive;
	float x, y;
	float oldX, oldY;
	float size;
	float maxSize;
	float speed;
	float angle;
	float height;

  GameObjectVisualType visualType;
	float cameraOffsetX, cameraOffsetY;

public:
	GameObject();
  virtual ~GameObject();

  GameObject(int _x, int _y, int _size, int _speed, int _angle);

	GameObject *itSelf(void);

	float getX(void);
	float getY(void);
	void setXY(float newX, float newY);
	void setSpeed(float newSpeed);
	float getSpeed(void);
	float getSize(void);
	void setSize(float value);
	float getAngle(void);
	void setHeight(float h);
	void setCameraOffset(float X,float Y);

	void backupXY(void);
	void restoreXY(void);

	float distance(GameObject *obj);

	float getAngleAt(GameObject *obj);

  virtual void draw(HDC bhdc);

	virtual void takeDamage(float damage);
};
