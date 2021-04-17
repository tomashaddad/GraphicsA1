#include "Keyboard.h"
#include <cctype>

/* Since chars map to ints, this class sets the corresponding int position of
 * the char in the 256-member array to TRUE or FALSE, which is then used to
 * check for which keys are pressed
 */

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
	for (auto &key : key_states_) {
		if (key) {
			return true;
		}
	}
	return false;
}