#include "Keyboard.h"
#include <cctype>

Keyboard::Keyboard()
	: key_states{ false } {}

void Keyboard::setKeyState(unsigned char key, bool state) {
	key = std::toupper(key);
	if (0 <= key && key < 256) {
		key_states[key] = state;
	}
}

bool Keyboard::getKeyState(unsigned char key) {
	key = std::toupper(key);
	return key_states[key];
}

bool Keyboard::anyKeyIsPressed() {
	for (auto i = 0; i < key_states.size(); ++i) {
		if (key_states[i]) {
			return true;
		}
	}
}