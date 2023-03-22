#pragma once

#include <windows.h>
#include <vector>
#include <memory>
#include "types.h"
#include "point.h"

class GameObject;
class Player;
struct ray;

class PhysicsManager final {
public:
  static PhysicsManager& instance();

  PhysicsManager(const PhysicsManager&) = delete;
  PhysicsManager& operator= (const PhysicsManager) = delete;

  void updateWorldPhysics(float32 dt);
  void renderWorld(HDC bhdc);

  void createPlayer(worldPoint _where);
  void createBlock(worldPoint _where, float32 w, float32 h);
  void createProjectile(worldPoint _where, float32 speed, float32 angle);

  void deposeObjects(float32 dx, float32 dy);
  void setCameraOffset(float32 offsetX, float32 offsetY);
  void setMouseAt(worldPoint _where);

  Player* getPlayer();
  float getMouseWorldX() const noexcept;
  float getMouseWorldY() const noexcept;

  GameObject* rayCast(worldPoint _whereFrom, float32 distance, worldPoint _whereTo);
  GameObject* rayCast(worldPoint _whereFrom, float32 distance, float32 angle);

  //эта функция конвертит точки экрана [0,640] / [0,480]
  //в пространство мира, так, как если бы он не двигался камерой (cameraOffset)
  // то есть от [-320,320] / [-240/240]
  //пространство мира начинается в центре и должно совпадать с (0,0) - точка спавна игрока
  inline worldPoint screenToWorld(const screenPoint &sp, int screenWidth, int screenHeight)
  {
    const int screenX = sp.p.x;
    const int screenY = sp.p.y;

    //const float32 widthHalf = (static_cast<float32>(screenWidth) / 2.0f);
    //const float32 heightHalf = (static_cast<float32>(screenHeight) / 2.0f);

    return { static_cast<float32>(screenX), static_cast<float32>(screenY) };

    //return { static_cast<float32>(screenX) + widthHalf, static_cast<float32>(screenY) + heightHalf };

    //return {
    //  static_cast<float32>(screenX - widthHalf) + widthHalf,
    //  static_cast<float32>(screenY - heightHalf) + heightHalf
    //};
  }

private:
  PhysicsManager();

private:
  float32 mouseWorldX, mouseWorldY;
  std::unique_ptr<ray> debug_ray;

  std::vector<std::unique_ptr<GameObject>> gos; //strong pointers

  //world settings:
  bool movable_camera;
};
