#pragma once

#include "singleton.h"

const char KEY_MOVE_UP = 'W';
const char KEY_MOVE_DOWN = 'S';
const char KEY_MOVE_LEFT = 'A';
const char KEY_MOVE_RIGHT = 'D';

class Keyboard : public Singleton<Keyboard> {
private:
	bool lmb;
	bool rmb;
	bool keys[256];

public:
	Keyboard();

	bool isLMBpressed() const noexcept;
	bool isRMBpressed() const noexcept;

	bool isPressed(const char c) const noexcept;

	void keyDown(const char c);
	void keyUp(const char c);

	void leftMouseButtonDown();
	void leftMouseButtonUp();
	void rightMouseButtonDown();
	void rightMouseButtonUp();
};
