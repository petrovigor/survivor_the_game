#include "physicsManager.h"
#include "game_object.h"
#include "player.h"
#include "block.h"
#include "projectile.h"

#include <iostream>

PhysicsManager& PhysicsManager::instance() {
  static PhysicsManager instance;
  return instance;
}

void PhysicsManager::updateWorldPhysics(float dt) {
  for(auto go : gos) {
    go->processPhysics(dt);
  }
}

void PhysicsManager::renderWorld(HDC bhdc) {
  for(auto go : gos) {
    go->draw(bhdc);
  }
}

void PhysicsManager::deposeObjects(float dx, float dy) {
  for(auto go : gos) {
    go->depose(dx, dy);
  }
}

void PhysicsManager::setCameraOffset(float offsetX, float offsetY) {
  for(auto go : gos) {
    go->setCameraOffset(offsetX, offsetY);
  }
}

Player* PhysicsManager::getPlayer() {
  return reinterpret_cast<Player*>( gos.front( ).get() );
}

float PhysicsManager::getMouseWorldX() const noexcept {
  return mouseWorldX;
}

float PhysicsManager::getMouseWorldY() const noexcept {
  return mouseWorldY;
}

void PhysicsManager::createPlayer(float x, float y) {
  gos.emplace_back( std::shared_ptr<GameObject>( new GameObject(x, y, 80.f, 0.f, GameObjectVisualType::Ellipse) ) );
  std::cout << "goes total: " << gos.size() << std::endl;
}

void PhysicsManager::createBlock(float x, float y, float w, float h) {
  gos.emplace_back( std::make_shared<GameObject>(x, y, 0.f, 0.f, GameObjectVisualType::Ellipse) );
  std::cout << "goes total: " << gos.size() << std::endl;
}

void PhysicsManager::createProjectile(float x, float y, float speed, float angle) {
  gos.emplace_back( std::make_shared<GameObject>(x, y, speed, angle, GameObjectVisualType::Ellipse) );
  std::cout << "goes total: " << gos.size() << std::endl;
}

void PhysicsManager::setMouseAt(float worldX, float worldY) {
  mouseWorldX = worldX;
  mouseWorldY = worldY;
}
