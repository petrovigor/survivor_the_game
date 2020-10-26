#pragma once

#include <vector>
#include "ability.h"

class ABILITY_MANAGER {
private:
	std::vector<ABILITY> list;
	PHYSICS_MANAGER *physicsManager;
	EVENT_MANAGER *eventMan;
	Player *playerPtr;
	FX_MANAGER *fx;

public:
	void init(PHYSICS_MANAGER* ptr, Player *newPlayerPtr, EVENT_MANAGER *eventManPtr, FX_MANAGER *fxManPtr) {
		physicsManager=ptr;
		playerPtr=newPlayerPtr;
		eventMan=eventManPtr;
		fx=fxManPtr;

		createAbility(ABILITY_ID_BLINK, ABILITY_CAST_TYPE_POINT, ABILITY_TARGET_TYPE_NONE, 0, 0, 0.0);
	}

	inline void createAbility(const int newAbilityId, const int newCastType, const int newTargetType, int newManaCost, int newCoolDown, double newCastTime) {
		list.push_back(ABILITY(newAbilityId, newCastType,newTargetType,newManaCost,newCoolDown,newCastTime));
	}

	ABILITY* getAbilityById(const int id) {
		return &list[id];
	}

	bool checkForRequirements(ABILITY *a, double targetX, double targetY) {
		bool result=true;

		switch(a->getAbilityId()) {
			case ABILITY_ID_BLINK:
				result = physicsManager->isPointFree(targetX, targetY, PLAYER_SIZE);
				break;
		}

		return result;
	}

	void endCasting(ABILITY *a, double targetX, double targetY) {
		switch(a->getAbilityId()) {
		case ABILITY_ID_BLINK:
			if(checkForRequirements(a, targetX, targetY)) {
				a->startCasting(targetX, targetY);
				playerPtr->denyCasting();
				eventMan->addEvent(EVENT_TYPE_SIMPLE, EVENT_ACTION_ALLOW_CASTING, a->getCastingTime());
			}

			break;
		}
	};

	void updateAbilitiesProcess(double deltaTime) {
		for(std::vector<ABILITY>::iterator i=list.begin(); i!=list.end(); ++i) {
			if(i->isTargeting()) {
				switch(i->getAbilityId()) {
					case ABILITY_ID_BLINK:
						//playerPtr->setAbilityCoords(i->getPointX(),i->getPointY());
						//playerPtr->setXY(i->getPointX(),i->getPointY());
						//fx->addFlash(playerPtr->getX(), playerPtr->getY(), 150.0, 0.10, FX_VISUAL_TYPE_ELLIPSE);
						//fx->addFlash(i->getPointX(),i->getPointY(), 150.0, 0.10, FX_VISUAL_TYPE_ELLIPSE);
						break;
				}
			}

			if(i->isCasting()) {
				i->increaseCastingTime(deltaTime);
				if(i->currentCastTime()>=i->getCastingTime()) {
					i->CastingEnd();

					switch(i->getAbilityId()) {
						case ABILITY_ID_BLINK:
							playerPtr->setXY(i->getPointX(),i->getPointY());
							//fx->addFlash(playerPtr->getX(), playerPtr->getY(), 150.0, 0.10, FX_VISUAL_TYPE_ELLIPSE);
							//fx->addFlash(i->getPointX(),i->getPointY(), 150.0, 0.10, FX_VISUAL_TYPE_ELLIPSE);
							break;
					}
				}
			}
		}
	}
};
