#ifndef __EVENT_H
#define __EVENT_H

const int EVENT_TYPE_SIMPLE = 0,
	      EVENT_TYPE_INFINITE = 1;

const int EVENT_ACTION_ALLOW_SHOOTING = 1,//for shots
	      EVENT_ACTION_RELOADING = 2,
		  EVENT_ACTION_SPAWN_ENEMY = 3,
		  EVENT_ACTION_INCREASE_ENEMY_MULTIPLIER = 4,
		  EVENT_ACTION_ALLOW_CASTING = 5;

class EVENT {
private:
	int eventType;
	int eventAction;
	double lastingTime; //max time
	double duration; //tmp time
	bool completed;

public:
	EVENT(const int newEventType, const int newEventAction, double newLastingTime) {
		completed = false;
		eventType = newEventType;
		eventAction = newEventAction;
		lastingTime = newLastingTime;
		duration = 0.0;
	}

	void completeEvent() {completed = true;}
	void increaseTime(double delta) {duration += delta;}
	void startAgain(void) {duration -= lastingTime;}
	int getEventType(void) {return eventType;}
	int getEventAction(void) {return eventAction;}
	double getLastingTime(void) {return lastingTime;}
	double getDuration(void) {return duration;}
	bool isCompleted(void) {return completed;}
};

#endif