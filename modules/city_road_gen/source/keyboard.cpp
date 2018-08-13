#include "keyboard.h"

e4_keyboard::e4_keyboard() {
	for(int i=0; i<256; i++)
		keys[i] = false;
}

bool e4_keyboard::isKey(char key) {
	return keys[key];
}

void e4_keyboard::setKey(char key, bool flag) {
	keys[key] = flag;
}