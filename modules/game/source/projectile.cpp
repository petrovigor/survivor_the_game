#include "projectile.h"
#include "physicsManager.h"

Projectile::Projectile(float32 newX, float32 newY, float32 newSpeed, float32 newAngle, float32 _size)
  : GameObject( PhysicsManager::instance().generateUniqueGameObjectId(), newX, newY, newSpeed, newAngle, _size, GameObjectVisualType::Square)
{ }
