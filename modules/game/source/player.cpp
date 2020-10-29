#include "player.h"
#include "physicsManager.h"
#include "utils.h"
#include "controller.h"

#include <iostream>

Player::Player(float _x, float _y, float _speed)
  : GameObject(_x, _y, _speed, 0.f, GameObjectVisualType::Ellipse)
  , attacking(false)
  , isCooldown(false)
  , cooldown(0.f)
  , attackTargetX(0.f)
  , attackTargetY(0.f)
{ }

void Player::attack(float targetX, float targetY) {
  if(!isCooldown) {
    attacking = true;
    attackTargetX = targetX;
    attackTargetY = targetY;
  }
}

void Player::processPhysics(float dt) {
  const auto& keys = Controller::instance();

	int v, h;
	v = h = 0;

	if(keys.isPressed(KEY_MOVE_LEFT)) {
		--h;
	}

	if(keys.isPressed(KEY_MOVE_RIGHT)) {
		++h;
	}

	if(keys.isPressed(KEY_MOVE_UP)) {
		--v;
	}

	if(keys.isPressed(KEY_MOVE_DOWN)) {
		++v;
	}

  float dist = speed * dt;
  float proection = dist / sqrt(float(2));

	if(!v && h < 0) {
    x -= dist;
	} else if(!v && h > 0) {
    x += dist;
	} else if(!h && v < 0) {
    y -= dist;
	} else if(!h && v > 0) {
    y += dist;
	} else if(h > 0 && v > 0) {
    x += proection;
    y += proection;
	} else if(h > 0 && v < 0) {
    x += proection;
    y -= proection;
	} else if(h < 0 && v < 0) {
    x -= proection;
    y -= proection;
	} else if(h < 0 && v > 0) {
    x -= proection;
    y += proection;
	}

  //when hero going out of last 10% of the map
  //we need to depose all game objects render coordinates
  //to imitate infinite map

  const float map_bounds_percent = 0.1f;

  const float window_width = 800.0f;
  const float window_height = 600.0f;

  const float lastX = (window_width * map_bounds_percent);
  const float lastY = (window_height * map_bounds_percent);

  const float boundsX = window_width - lastX;
  const float boundsY = window_height - lastY;

  auto& phys = PhysicsManager::instance();

  if(x > boundsX) {
    phys.deposeObjects( boundsX - x, 0.f );
  }
  if(y > boundsY) {
    phys.deposeObjects( 0.f, boundsY - y );
  }
  if(x < lastX) {
    phys.deposeObjects( lastX - x, 0.f );
  }
  if(y < lastY) {
    phys.deposeObjects( 0.f, lastY - y );
  }

  //process player attacking mechanism

  if(isCooldown) {
    cooldown -= dt;
    if(cooldown <= 0.f) {
      isCooldown = false;
    }
  }

  if(attacking) {
    
    std::cout << "attacking" << std::endl;
    phys.createProjectile(x, y, 50.f, abc(x, y, attackTargetX, attackTargetY));

    attacking = false;
    cooldown = 1.5f;
    isCooldown = true;
  }

}
