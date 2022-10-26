#include "physicsManager.h"
#include "game_object.h"
#include "player.h"
#include "block.h"
#include "projectile.h"

#include <iostream>

PhysicsManager::PhysicsManager()
{
}

PhysicsManager& PhysicsManager::instance() {
  static PhysicsManager instance;
  return instance;
}

void PhysicsManager::updateWorldPhysics(float dt) {
  for(auto& go : gos) {
    go->processPhysics(dt);
  }
}

void PhysicsManager::renderWorld(HDC bhdc) {
  for(auto& go : gos) {
    go->draw(bhdc);
  }
}

void PhysicsManager::deposeObjects(float dx, float dy) {
  for(auto& go : gos) {
    go->depose(dx, dy);
  }
}

void PhysicsManager::setCameraOffset(float offsetX, float offsetY) {
  for(auto& go : gos) {
    go->setCameraOffset(offsetX, offsetY);
  }
}

Player* PhysicsManager::getPlayer() {
  return nullptr; //reinterpret_cast<Player*>( gos.front( ).get() );
}

float PhysicsManager::getMouseWorldX() const noexcept {
  return mouseWorldX;
}

float PhysicsManager::getMouseWorldY() const noexcept {
  return mouseWorldY;
}

void PhysicsManager::createPlayer(float x, float y) {

  GameObject* player = new Player(x, y, 80.f);

  std::unique_ptr<GameObject> playerPtr{ player };

  gos.push_back(std::move(playerPtr));
  std::cout << "goes total: " << gos.size() << std::endl;
}

void PhysicsManager::createBlock(float x, float y, float w, float h) {
  GameObject* block = new Block(x, y, w, h);

  std::unique_ptr<GameObject> blockPtr{ block };

  gos.push_back(std::move(blockPtr));

  std::cout << "goes total: " << gos.size() << std::endl;
}

void PhysicsManager::createProjectile(float x, float y, float speed, float angle) {

  GameObject* proj = new Projectile(x, y, speed, angle);

  std::unique_ptr<GameObject> projPtr{ proj };

  gos.push_back(std::move(projPtr));

  std::cout << "goes total: " << gos.size() << std::endl;
}

void PhysicsManager::setMouseAt(float worldX, float worldY) {
  mouseWorldX = worldX;
  mouseWorldY = worldY;
}
