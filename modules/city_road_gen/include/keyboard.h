#ifndef __KEYBOARD_H
#define __KEYBOARD_H

class e4_keyboard {
private:
	bool keys[256];

public:
	e4_keyboard(void);

	bool isKey(char key);
	void setKey(char key, bool flag);
};

#endif