#include "player.h"
#include "physicsManager.h"
#include "utils.h"
#include "controller.h"

#include <iostream>
#include <math.h>
#include <Windows.h>

Player::Player(float _x, float _y, float _speed)
  : GameObject(0u, _x, _y, _speed, 0.f, 15.0f, GameObjectVisualType::Ellipse)
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


void Player::draw(HDC bhdc, worldPoint playerPosition) {
  auto &phys = PhysicsManager::instance();
  const auto playerDrawPoint = phys.worldToScreen(p, worldPoint{});

  //std::cout << "

  constexpr int s = 15;
  const int newX = playerDrawPoint.p.x - playerPosition.p.x; //playerDrawPoint.p.x; //400 - 0+ cox;// + (p.p.x + cameraOffsetX) - (s / 2.0f);
  const int newY = playerDrawPoint.p.y - playerPosition.p.y; //playerDrawPoint.p.y; //300 - 0+ coy;// + (p.p.y + cameraOffsetY) - (s / 2.0f);

  //std::cout << "player xy: " << newX << ", " << newY << std::endl;

  switch(visualType) {
  case GameObjectVisualType::Ellipse:
    Ellipse(bhdc, newX - s, newY - s, newX + s, newY + s);
    break;

  case GameObjectVisualType::Square:
    Rectangle(bhdc, newX - s, newY - s, newX + s, newY + s);
    break;
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
    p.p.x -= dist;
	} else if(!v && h > 0) {
    p.p.x += dist;
	} else if(!h && v < 0) {
    p.p.y -= dist;
	} else if(!h && v > 0) {
    p.p.y += dist;
	} else if(h > 0 && v > 0) {
    p.p.x += proection;
    p.p.y += proection;
	} else if(h > 0 && v < 0) {
    p.p.x += proection;
    p.p.y -= proection;
	} else if(h < 0 && v < 0) {
    p.p.x -= proection;
    p.p.y -= proection;
	} else if(h < 0 && v > 0) {
    p.p.x -= proection;
    p.p.y += proection;
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

  //if(p.p.x > boundsX) {
  //  phys.deposeObjects( boundsX - p.p.x, 0.f );
  //}
  //if(p.p.y > boundsY) {
  //  phys.deposeObjects( 0.f, boundsY - p.p.y );
  //}
  //if(p.p.x < lastX) {
  //  phys.deposeObjects( lastX - p.p.x, 0.f );
  //}
  //if(p.p.y < lastY) {
  //  phys.deposeObjects( 0.f, lastY - p.p.y );
  //}

  //process player attacking mechanism

  if(isCooldown) {
    cooldown -= dt;
    if(cooldown <= 0.f) {
      isCooldown = false;
    }
  }

  if(attacking) {

    std::cout << "attacking" << std::endl;
    phys.createProjectile(p, 50.f, abc(p.p.x, p.p.y, attackTargetX, attackTargetY), 4.0f);

    attacking = false;
    cooldown = 1.5f;
    isCooldown = true;
  }

}
