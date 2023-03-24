#include "physicsManager.h"
#include "game_object.h"
#include "player.h"
#include "block.h"
#include "projectile.h"
#include "utils.h"
#include "ray.h"

#include <iostream>

PhysicsManager::PhysicsManager()
  : cameraOffsetX(0)
  , cameraOffsetY(0)
{
  movable_camera = true;
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
  const worldPoint playerPos = getPlayerPos();

  //std::cout << "renderWorld: " << static_cast<float>(playerPos.p.x) << " & " << static_cast<float>(playerPos.p.y) << std::endl;

  for(auto& go : gos) {
    go->draw(bhdc, playerPos);
  }
  if(debug_ray)
  {
    debug_ray->draw(bhdc, playerPos);
  }
}
//
//void PhysicsManager::deposeObjects(float32 dx, float32 dy) {
//#if 0
//  for(auto& go : gos) {
//   //go->depose(dx, dy);
//  }
//  if(debug_ray)
//  {
//    //debug_ray->depose(dx, dy);
//  }
//#endif //0
//}

void PhysicsManager::setCameraOffset(float32 offsetX, float32 offsetY) {
  if(!movable_camera)
    return;

  cameraOffsetX = offsetX;
  cameraOffsetY = offsetY;

  for(auto& go : gos) {
    go->setCameraOffset(offsetX, offsetY);
  }
  if(debug_ray)
  {
    debug_ray->setCameraOffset(offsetX, offsetY);
  }
}

worldPoint PhysicsManager::getPlayerPos()
{
  const GameObject* player = getPlayerAsGO();

  if(!player)
  {
    return worldPoint(0, 0);
  }
  else
  {
    return player->getP();
  }
}

GameObject* PhysicsManager::getGOById(uint32_t id)
{
  for(const auto& go : gos)
  {
    if(go->getId() == id)
      return go.get();
  }

  return nullptr;
}


uint32_t PhysicsManager::generateUniqueGameObjectId()
{
  return ++go_id_generator;
}


GameObject* PhysicsManager::getPlayerAsGO() {
  return getGOById(0);
}

Player* PhysicsManager::getPlayer() {
  return static_cast<Player*>(getPlayerAsGO());
  //if(!gos.empty())
  //{
  //
  //  //return static_cast<
  //}

  //return nullptr; //reinterpret_cast<Player*>( gos.front( ).get() );
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
  const float32 a = abp(_whereFrom, _whereTo);
  return rayCast(_whereFrom, distance, a);
}

GameObject* PhysicsManager::rayCast(worldPoint _whereFrom, float32 distance, float32 angle)
{
  GameObject* ans = nullptr;



  return ans;
}

void PhysicsManager::moveMouseWorldSpace(worldPoint _where) {
  if(!debug_ray.get())
  {
    debug_ray = std::make_unique<ray>(0, 0, 0, 0);
  }
  if(!gos.empty())
  {
    GameObject *player = getPlayerAsGO();
    if(!player)
      return;

    debug_ray->x1 = player->getX();
    debug_ray->y1 = player->getY();
    debug_ray->x2 = _where.p.x;
    debug_ray->y2 = _where.p.y;



    //std::cout << "World x=" << debug_ray->x2 << " / y=" << debug_ray->y2 << std::endl;


    std::cout << "ray world: " << debug_ray->x1 << ", " << debug_ray->y1 << " |||| " << debug_ray->x2 << "     " << debug_ray->y2 << std::endl; //<< "       " << gos.size() << std::endl;
  }
}
