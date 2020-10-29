#pragma once

#include <windows.h>
#include <vector>
#include <memory>
#include <mutex>

class GameObject;
class Player;

class PhysicsManager {
public:
  static PhysicsManager& instance();

  PhysicsManager(const PhysicsManager&) = delete;
  PhysicsManager& operator= (const PhysicsManager) = delete;

  void updateWorldPhysics(float dt);
  void renderWorld(HDC bhdc);
  
  void createPlayer(float x, float y);
  void createBlock(float x, float y, float w, float h);
  void createProjectile(float x, float y, float speed, float angle);

  void deposeObjects(float dx, float dy);
  void setCameraOffset(float offsetX, float offsetY);
  void setMouseAt(float worldX, float worldY);

  Player* getPlayer();
  float getMouseWorldX() const noexcept;
  float getMouseWorldY() const noexcept;

private:
  PhysicsManager() = default;

  float mouseWorldX, mouseWorldY;

  std::vector<std::shared_ptr<GameObject>> gos; //strong pointers
};
