#include "Keyboard.h"

Keyboard::Keyboard()
	: key_states{ false } {}

void Keyboard::setKeyState(unsigned char key, bool state) {
	if (0 <= key && key < 256) {
		key_states[key] = state;
	}
}

bool Keyboard::getKeyState(unsigned char key) {
	return key_states[key];
}