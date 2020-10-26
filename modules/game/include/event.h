#pragma once

const int EVENT_TYPE_SIMPLE = 0,
	      EVENT_TYPE_INFINITE = 1;

const int EVENT_ACTION_ALLOW_SHOOTING = 1,
	      EVENT_ACTION_RELOADING = 2,
		  EVENT_ACTION_SPAWN_ENEMY = 3,
		  EVENT_ACTION_INCREASE_ENEMY_MULTIPLIER = 4,
		  EVENT_ACTION_ALLOW_CASTING = 5;

class EVENT {
private:
	int eventType;
	int eventAction;
	float lastingTime;
	float duration;
	bool completed;

public:
	EVENT(const int newEventType, const int newEventAction, float newLastingTime) {
		completed = false;
		eventType = newEventType;
		eventAction = newEventAction;
		lastingTime = newLastingTime;
		duration = 0.0;
	}

	void completeEvent() {completed = true;}
	void increaseTime(float delta) {duration += delta;}
	void startAgain(void) {duration -= lastingTime;}
	int getEventType(void) {return eventType;}
	int getEventAction(void) {return eventAction;}
	float getLastingTime(void) {return lastingTime;}
	float getDuration(void) {return duration;}
	bool isCompleted(void) {return completed;}
};
