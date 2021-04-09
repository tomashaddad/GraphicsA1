#include "Keyboard.h"
#include <iostream>

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

bool Keyboard::anyKeyIsPressed() {
	for (auto i = 0; i < key_states.size(); ++i) {
		if (key_states[i]) {
			std::cout << i << std::endl;
			return true;
		}
	}
}