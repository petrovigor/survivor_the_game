#include "projectile.h"

Projectile::Projectile(float newX, float newY, float newSpeed, float newAngle)
  : GameObject(newX, newY, newSpeed, newAngle, GameObjectVisualType::Square)
{ }
