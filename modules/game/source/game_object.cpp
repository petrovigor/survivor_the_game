#include "game_object.h"
#include <math.h>

GameObject::GameObject() {
  visualType = GameObjectVisualType::Square;
	x = y = angle = speed = 0.0f;
	cameraOffsetX = cameraOffsetY = 0.0f;
}

GameObject::GameObject(float _x, float _y, float _speed, float _angle, GameObjectVisualType _vt) :
  x(_x),
  y(_y),
  speed(_speed),
  angle(_angle),
  visualType(_vt),
  cameraOffsetX(0.f),
  cameraOffsetY(0.f)
{ }

GameObject::~GameObject() {};

void GameObject::processPhysics(float dt) {
	x += speed * cos(angle) * dt;
	y += speed * sin(angle) * dt;
}

void GameObject::setCameraOffset(float x, float y) {
  cameraOffsetX = x;
  cameraOffsetY = y;
}

void GameObject::depose(float dx, float dy) {
  x += dx;
  y += dy;
}

void GameObject::draw(HDC bhdc) {
	const float s = 15.0f;
	const float newX = x + cameraOffsetX;
	const float newY = y + cameraOffsetY;

	switch(visualType) {
  case GameObjectVisualType::Ellipse:
		Ellipse(bhdc, newX - s, newY - s, newX + s, newY + s);
		break;

	case GameObjectVisualType::Square:
		Rectangle(bhdc, newX - s, newY - s, newX + s, newY + s);
		break;
	}
}