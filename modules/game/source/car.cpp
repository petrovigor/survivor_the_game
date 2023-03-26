#include "car.h"
#include "physicsManager.h"
#include "utils.h"

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
	auto &phys = PhysicsManager::instance();
	const auto &point_from = p;
	const auto &point_to = phys.getCenterOfCell(cell_target);
	const auto a = abp(point_from, point_to);
	const auto dist_dt = dt * speed;
	const auto new_p = offsetPoint(point_from, dist_dt, a);

	p = new_p;
}

