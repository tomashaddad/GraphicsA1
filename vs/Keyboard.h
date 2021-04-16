#ifndef I3D_KEYBOARD_H
#define I3D_KEYBOARD_H

#include <array>

class Keyboard {
public:
	Keyboard();
	void setKeyState(unsigned char key, bool state);
	bool getKeyState(unsigned char key);
	bool anyKeyIsPressed();
private:
	std::array<bool, 256> key_states_;
};

#endif  // I3D_KEYBOARD_H