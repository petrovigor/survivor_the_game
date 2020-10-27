#include "game_object.h"
#include <math.h>

GameObject::GameObject() {
  visualType = GameObjectVisualType::Square;
	x = y = size = maxSize = angle = speed = oldX = oldY = 0.0;
	cameraOffsetX = cameraOffsetY = 0.0;
	alive = true;
	height = 1.0;
}

GameObject::~GameObject() {};

GameObject::GameObject(int _x, int _y, int _size, int _speed, int _angle)
  : x(_x)
  , y(_y)
  , size(_size)
  , speed(_speed)
  , angle(_angle)
{ }

GameObject *GameObject::itSelf(void) {return this;}

float GameObject::getX(void) {return x;}
float GameObject::getY(void) {return y;}
void GameObject::setXY(float newX, float newY) {x = newX; y = newY;}
void GameObject::setSpeed(float newSpeed) {speed = newSpeed;}
float GameObject::getSpeed(void) {return speed;}
float GameObject::getSize(void) {return size;}
void GameObject::setSize(float value) {size=value;}
float GameObject::getAngle(void) {return angle;}
void GameObject::setHeight(float h) {height=h;}
void GameObject::setCameraOffset(float X,float Y){cameraOffsetX=X;cameraOffsetY=Y;}

void GameObject::backupXY(void) {oldX = x; oldY = y;}
void GameObject::restoreXY(void) {x = oldX; y = oldY;}

float GameObject::distance(GameObject *obj) {
	float x1 = obj->getX();
	float y1 = obj->getY();
	float x2 = x;
	float y2 = y;

	float d=x2-x1;
	float d2=y2-y1;
	float result = sqrt(pow(x - obj->getX(), 2.0) + pow(y - obj->getY(), 2.0));

	return result;
}

float GameObject::getAngleAt(GameObject *obj) {
	return(atan2(obj->y - y, obj->x - x));
}

void GameObject::takeDamage(float damage) {};

void GameObject::draw(HDC bhdc) {
	//const float size = 5.0;
	//HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	//SelectObject(bhdc, pen );
	//SelectObject(bhdc, brush );

	//SelectObject(bhdc, *br);
	//SelectObject(bhdc, *pn);

	const float s = size * height;
	float newX = x+cameraOffsetX;
	float newY = y+cameraOffsetY;

	switch(visualType) {
  case GameObjectVisualType::Ellipse:
		Ellipse(bhdc, newX-s, newY-s, newX+s, newY+s);
		break;

	case GameObjectVisualType::Square:
		Rectangle(bhdc, newX-s, newY-s, newX+s, newY+s);
		break;
	}

	//if(!flag) {
	//	Rectangle(bhdc, x-size*2, y-size*2, x+size*2, y+size*2);
	//}

	//DeleteObject(pen);
	//DeleteObject(brush);
	//SelectObject(bhdc, NULL);
}