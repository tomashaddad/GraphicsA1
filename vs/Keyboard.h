#ifndef I3D_KEYBOARD_H
#define I3D_KEYBOARD_H

#include "GlutHeaders.h"

class Keyboard {
public:
	Keyboard();
	void setKeyState(unsigned char key, bool state);
	bool getKeyState(unsigned char key);
private:
	bool key_states[256];
};

#endif I3D_KEYBOARD_H