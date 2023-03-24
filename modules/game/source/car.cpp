#include "car.h"
#include "physicsManager.h"

#include <iostream>

Car::Car(cell_indices _cell_at, cell_indices _cell_to, float32 _speed)
	//: GameObject(PhysicsManager::instance().generateUniqueGameObjectId(),
{
	speed = _speed;
	cell_target = _cell_to;
	visualType = GameObjectVisualType::Square;
	p = PhysicsManager::instance().getCenterOfCell(_cell_at);

	std::cout << "car created at: " << p.p.x << " & " << p.p.y << std::endl;
}

//
//void Car::draw(HDC bhdc, const worldPoint &playerPos, float32 cox, float32 coy) {
//
//}


void Car::processPhysics(float32 dt) {

}

