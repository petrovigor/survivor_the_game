#if 0

#pragma once

#include <vector>
#include "game_object.h"

class PhysicsManager {
public:
  PhysicsManager() { }
  ~PhysicsManager() { }

  void createPlayer(int x, int y) {
    const auto ptr = createGameObject( x, y, 15, 20, 0 );

    _GameObjects.emplace_back( ptr );
    _player = ptr;
  }

  void createNPC(int x, int y) {
    const auto ptr = createGameObject( x, y, 15, 20, 0 );

    _GameObjects.emplace_back( ptr );
    _enemies.emplace_back( ptr );
  }

  void createProjectile(int x, int y) {
    const auto ptr = createGameObject( x, y, 3, 20, 0 );

    _GameObjects.emplace_back( ptr );
    _projectiles.emplace_back( ptr );
  }

private:
  std::vector<std::shared_ptr<GameObject>> _GameObjects; //strong pointers

  std::vector<std::weak_ptr<GameObject>>   _enemies;
  std::vector<std::weak_ptr<GameObject>>   _projectiles;
  std::weak_ptr<GameObject>                _player;

};

#endif //0
