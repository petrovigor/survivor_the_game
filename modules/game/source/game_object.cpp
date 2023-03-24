#include "game_object.h"
#include <math.h>

GameObject::GameObject()
	: p(0, 0)
	, id(-1)
{
  visualType = GameObjectVisualType::Square;
	angle = speed = 0.0f;
	cameraOffsetX = cameraOffsetY = 0.0f;
}

GameObject::GameObject(uint32_t _id, worldPoint _p, float _speed, float _angle, GameObjectVisualType _vt) :
	id(_id),
	p(_p),
	speed(_speed),
	angle(_angle),
	visualType(_vt),
	cameraOffsetX(0.f),
	cameraOffsetY(0.f)
{ }

GameObject::GameObject(uint32_t _id, float32 _x, float32 _y, float32 _speed, float32 _angle, GameObjectVisualType _vt) :
	id(_id),
	p(_x, _y),
	speed(_speed),
	angle(_angle),
	visualType(_vt),
	cameraOffsetX(0.f),
	cameraOffsetY(0.f)
{ }

GameObject::~GameObject() {};

void GameObject::processPhysics(float32 dt) {
	p.p.x += speed * cos(angle) * dt;
	p.p.y += speed * sin(angle) * dt;
}

void GameObject::setCameraOffset(float32 x, float32 y) {
  cameraOffsetX = x;
  cameraOffsetY = y;
}



//void GameObject::depose(float32 dx, float32 dy) {
//  //p.p.x += dx;
//  //p.p.y += dy;
//}


float32 GameObject::getX() const noexcept { return p.p.x; }
float32 GameObject::getY() const noexcept { return p.p.y; }
uint32_t GameObject::getId() const noexcept { return id; }
worldPoint GameObject::getP() const noexcept { return p; }


void GameObject::draw(HDC bhdc, const worldPoint &playerPosition) {
	constexpr float32 s = 15.0f;

	//const float32 ratio = 600.0f / 800.0f;
	//const float32 worldCenterOffsetWidth = 800.0f / 2.0f;
	//const float32 worldCenterOffsetHeight = 600.0f / 2.0f;
	//const float32 newX = worldCenterOffsetWidth - (s / 2.0f); //p.p.x + cameraOffsetX + worldCenterOffsetWidth*ratio;
	//const float32 newY = worldCenterOffsetHeight - (s / 2.0f); //p.p.y + cameraOffsetY + worldCenterOffsetHeight;


	const float32 newX = (p.p.x - playerPosition.p.x + cameraOffsetX) - (s / 2.0f);
	const float32 newY = (p.p.y - playerPosition.p.y + cameraOffsetY) - (s / 2.0f);

	switch(visualType) {
  case GameObjectVisualType::Ellipse:
		Ellipse(bhdc, newX - s, newY - s, newX + s, newY + s);
		break;

	case GameObjectVisualType::Square:
		Rectangle(bhdc, newX - s, newY - s, newX + s, newY + s);
		break;
	}
}