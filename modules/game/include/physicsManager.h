#pragma once

#include <Windows.h>
#include <vector>
#include <memory>
#include "types.h"
#include "point.h"
#include "grid.h"

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
  void createCar(cell_indices cell_from, cell_indices cell_to, float32 speed);
  void createProjectile(worldPoint _where, float32 speed, float32 angle);

  //void deposeObjects(float32 dx, float32 dy);
  void setCameraOffset(float32 offsetX, float32 offsetY);
  void moveMouseWorldSpace(worldPoint _where);

  Player* getPlayer();
  GameObject* getPlayerAsGO();

  GameObject* getGOById(uint32_t id);

  worldPoint getPlayerPos();

  worldPoint getCenterOfCell(cell_indices cell);

  void left_mouse_click();

  worldPoint getMouseTargetPoint();

  //float getMouseWorldX() const noexcept;
  //float getMouseWorldY() const noexcept;

  GameObject* rayCast(worldPoint _whereFrom, float32 distance, worldPoint _whereTo);
  GameObject* rayCast(worldPoint _whereFrom, float32 distance, float32 angle);

  //эта функция конвертит точки экрана [0,800] / [0,600]
  //в пространство мира, так, как если бы он не двигался камерой (cameraOffset)
  // то есть от [-400,-300] / [400/300]
  //пространство мира начинается в центре и должно совпадать с (0,0) - точка спавна игрока
  worldPoint screenToWorld(screenPoint sp, worldPoint playerPos, int screenWidth, int screenHeight);

  //функция используется для рисования, чтоб перевести из мировых координат в экранные
  //если камера обращена на объект в мире, мы его нарисуем (он будет в диапазоне [0,800]x[0,600])
  screenPoint worldToScreen(worldPoint wp, worldPoint playerPos);

  uint32_t generateUniqueGameObjectId();
  void create_grid(uint32_t cells_width, uint32_t cells_height, world_units_t cell_size);

private:
  PhysicsManager();
  ~PhysicsManager();

private:
  uint32_t go_id_generator;
  worldPoint mouseWorldPoint;
  //float32 mouseWorldX, mouseWorldY;

  grid cells;

  std::unique_ptr<ray> debug_ray;

  std::vector<std::unique_ptr<GameObject>> gos; //strong pointers

  //move to abstract draw manager (render engine)
  HPEN black_pen;
  HPEN gray_pen;



  //camera settings:
  float32 cameraOffsetX, cameraOffsetY;
  bool movable_camera; //camera settings;
};
