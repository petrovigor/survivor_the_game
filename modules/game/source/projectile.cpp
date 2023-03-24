#include "projectile.h"
#include "physicsManager.h"

Projectile::Projectile(float newX, float newY, float newSpeed, float newAngle)
  : GameObject( PhysicsManager::instance().generateUniqueGameObjectId(), newX, newY, newSpeed, newAngle, GameObjectVisualType::Square)
{ }
