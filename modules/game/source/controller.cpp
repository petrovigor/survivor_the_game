#include "controller.h"

Controller::Controller() {
	for(int i = 0; i < 256; i++) {
		keys[i] = false;
	}

	lmb = false;
	rmb = false;
}

Controller& Controller::instance() {
  static Controller instance;
  return instance;
}

bool Controller::isLMBpressed() const noexcept {
  return lmb;
}

bool Controller::isRMBpressed() const noexcept {
  return rmb;
}

bool Controller::isPressed(const char c) const noexcept {
	return keys[c];
}

void Controller::keyDown(const char c) {
  keys[c] = true;
}

void Controller::keyUp(const char c) {
  keys[c] = false;
}

void Controller::leftMouseButtonDown() {
  lmb = true;
}

void Controller::leftMouseButtonUp() {
  lmb = false;
}

void Controller::rightMouseButtonDown() {
  rmb = true;
}

void Controller::rightMouseButtonUp() {
  rmb = false;
}
