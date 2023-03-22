#include "physicsManager.h"
#include "game_object.h"
#include "player.h"
#include "block.h"
#include "projectile.h"
#include "utils.h"
#include "ray.h"

#include <iostream>

PhysicsManager::PhysicsManager()
{
  movable_camera = false;
}

PhysicsManager& PhysicsManager::instance() {
  static PhysicsManager instance;
  return instance;
}

void PhysicsManager::updateWorldPhysics(float32 dt) {
  for(auto& go : gos) {
    go->processPhysics(dt);
  }
}

void PhysicsManager::renderWorld(HDC bhdc) {
  for(auto& go : gos) {
    go->draw(bhdc);
  }
  if(debug_ray)
  {
    debug_ray->draw(bhdc);
  }
}

void PhysicsManager::deposeObjects(float32 dx, float32 dy) {
  for(auto& go : gos) {
    go->depose(dx, dy);
  }
  if(debug_ray)
  {
    debug_ray->depose(dx, dy);
  }
}

void PhysicsManager::setCameraOffset(float32 offsetX, float32 offsetY) {
  if(!movable_camera)
    return;

  for(auto& go : gos) {
    go->setCameraOffset(offsetX, offsetY);
  }
  if(debug_ray)
  {
    debug_ray->setCameraOffset(offsetX, offsetY);
  }
}

Player* PhysicsManager::getPlayer() {
  if(!gos.empty())
  {
    return nullptr;
    //return static_cast<
  }

  return nullptr; //reinterpret_cast<Player*>( gos.front( ).get() );
}

float PhysicsManager::getMouseWorldX() const noexcept {
  return mouseWorldX;
}

float PhysicsManager::getMouseWorldY() const noexcept {
  return mouseWorldY;
}

void PhysicsManager::createPlayer(worldPoint _where) {

  GameObject* player = new Player(_where.p.x, _where.p.y, 80.f);

  std::unique_ptr<GameObject> playerPtr{ player };

  gos.emplace_back(std::move(playerPtr));
  std::cout << "goes total: " << gos.size() << std::endl;
}

void PhysicsManager::createBlock(worldPoint _where, float32 w, float32 h) {
  GameObject* block = new Block(_where.p.x, _where.p.y, w, h);

  std::unique_ptr<GameObject> blockPtr{ block };

  gos.emplace_back(std::move(blockPtr));

  std::cout << "goes total: " << gos.size() << std::endl;
}

void PhysicsManager::createProjectile(worldPoint _where, float32 speed, float32 angle) {

  GameObject* proj = new Projectile(_where.p.x, _where.p.y, speed, angle);

  std::unique_ptr<GameObject> projPtr{ proj };

  gos.emplace_back(std::move(projPtr));

  std::cout << "goes total: " << gos.size() << std::endl;
}

GameObject* PhysicsManager::rayCast(worldPoint _whereFrom, float32 distance, worldPoint _whereTo)
{
  const float32 a = abc(_whereFrom, _whereTo);
  return rayCast(_whereFrom, distance, a);
}

GameObject* PhysicsManager::rayCast(worldPoint _whereFrom, float32 distance, float32 angle)
{
  GameObject* ans = nullptr;



  return ans;
}

void PhysicsManager::setMouseAt(worldPoint _where) {
  if(!debug_ray)
  {
    debug_ray = std::make_unique<ray>(0, 0, mouseWorldX, mouseWorldY);
  }
  if(!gos.empty())
  {
    GameObject &pl = *gos[0].get();
    debug_ray->x1 = pl.getX();
    debug_ray->y1 = pl.getY();
    debug_ray->x2 = _where.p.x;
    debug_ray->y2 = _where.p.y;

    std::cout << "World x=" << debug_ray->x2 << " / y=" << debug_ray->y2 << std::endl;

    //std::cout << "ray world x2 y2: " << debug_ray->x2 << "     " << debug_ray->y2 << "       " << gos.size() << std::endl;
  }
}
