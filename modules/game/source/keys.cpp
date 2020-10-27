#include "defines.h"
#include "keys.h"

Keyboard::Keyboard() {
	for(int i = 0; i < 256; i++) {
		keys[i] = false;
	}

	lmb = false;
	rmb = false;
}

bool Keyboard::isLMBpressed() const noexcept {
  return lmb;
}

bool Keyboard::isRMBpressed() const noexcept {
  return rmb;
}

bool Keyboard::isPressed(const char c) const noexcept {
	return keys[c];
}

void Keyboard::keyDown(const char c) {
  keys[c] = true;
}

void Keyboard::keyUp(const char c) {
  keys[c] = false;
}

void Keyboard::leftMouseButtonDown() {
  lmb = true;
}

void Keyboard::leftMouseButtonUp() {
  lmb = false;
}

void Keyboard::rightMouseButtonDown() {
  rmb = true;
}

void Keyboard::rightMouseButtonUp() {
  rmb = false;
}
