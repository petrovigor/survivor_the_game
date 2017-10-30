#ifndef __KEYS_H
#define __KEYS_H

const int KEYS_COUNT = 256;
const char KEY_MOVE_UP = 'W';
const char KEY_MOVE_DOWN = 'S';
const char KEY_MOVE_LEFT = 'A';
const char KEY_MOVE_RIGHT = 'D';

class KEYS {
private:
	bool lmb;
	bool rmb;
	bool keys[256];

public:
	KEYS() {
		for(int i=0; i<KEYS_COUNT; i++) {
			keys[i] = false;
		}

		lmb = false;
		rmb = false;
	}

	//read access
	int getPlayerDirection();

	bool isLMBpressed(void) {return lmb;}
	bool isRMBpressed(void) {return rmb;}

	bool isPressed(const char c) {
		return keys[c];
	}

	//write acess
	void keyDown(const char c) {keys[c] = true;}
	void keyUp(const char c) {keys[c] = false;}

	void leftMouseButtonDown(void) {lmb = true;}
	void leftMouseButtonUp(void) {lmb = false;}
	void rightMouseButtonDown(void) {rmb = true;}
	void rightMouseButtonUp(void) {rmb = false;}
};

#endif