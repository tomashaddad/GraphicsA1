#include "Keyboard.h"
#include <cctype>

Keyboard::Keyboard()
	: key_states_{ false } {}

// Max value of an unsigned char is 255 so no if check needed
void Keyboard::setKeyState(unsigned char key, bool state) {
	key = std::toupper(key);
	key_states_[key] = state;
}

bool Keyboard::getKeyState(unsigned char key) {
	key = std::toupper(key);
	return key_states_[key];
}

bool Keyboard::anyKeyIsPressed() {
	for (auto &key : key_states_)
	{
		if (key)
		{
			return true;
		}
	}
	return false;
}