#pragma once

#include <windows.h>
#include <vector>
#include "event.h"
#include "player.h"
#include "enemyManager.h"
#include "physicsManager.h"

class EVENT_MANAGER {
private:
	std::vector<EVENT> eventList;
	Player *playerPtr;
	ENEMY_MANAGER *enemyManPtr;
	PHYSICS_MANAGER *phy;

public:
	void initEventManager(Player *newPlayerPtr, ENEMY_MANAGER *newEnemyManagerPtr, PHYSICS_MANAGER *pt) {playerPtr = newPlayerPtr; enemyManPtr = newEnemyManagerPtr; phy=pt;}

	void addEvent(const int newEventType, const int newEventAction, float newLastingTime) {
		eventList.push_back(EVENT(newEventType, newEventAction, newLastingTime));
	}

	void execute(EVENT e) {
		switch(e.getEventAction()) {
		case EVENT_ACTION_ALLOW_SHOOTING:
			playerPtr->allowShooting();
			break;

		case EVENT_ACTION_RELOADING:
			playerPtr->getCurrentWeapon()->reloaded();
			playerPtr->finishReloading();
			playerPtr->allowShooting();
			break;

		case EVENT_ACTION_SPAWN_ENEMY:
			spawnEnemy();
			break;

		case EVENT_ACTION_INCREASE_ENEMY_MULTIPLIER:
			increaseEnemyMultiplier();
			break;

		case EVENT_ACTION_ALLOW_CASTING:
			allowCasting();
			break;
		}
	}

	void updateEvents(float deltaTime);
	void removeEvents(void) {eventList.clear();}
	int getEventCount(void) {return eventList.size();}
	void spawnEnemy(void);
	void increaseEnemyMultiplier(void);
	void allowCasting(void);
};
