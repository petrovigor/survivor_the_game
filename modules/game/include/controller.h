#pragma once

const char KEY_MOVE_UP = 'W';
const char KEY_MOVE_DOWN = 'S';
const char KEY_MOVE_LEFT = 'A';
const char KEY_MOVE_RIGHT = 'D';

class Controller {
public:
  Controller(const Controller&) = delete;
  Controller& operator= (const Controller) = delete;

  static Controller& instance();

	bool isLMBpressed() const noexcept;
	bool isRMBpressed() const noexcept;

	bool isPressed(const char c) const noexcept;

	void keyDown(const char c);
	void keyUp(const char c);

	void leftMouseButtonDown();
	void leftMouseButtonUp();
	void rightMouseButtonDown();
	void rightMouseButtonUp();

private:
	Controller();

	bool lmb;
	bool rmb;
	bool keys[256];

};
