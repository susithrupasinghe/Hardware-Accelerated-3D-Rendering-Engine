#include "InputManager.h"

#include <memory>

InputManager InputManager::m_singleton;

InputManager::InputManager() {
	memset(m_bCurrentKeyStates, 0, sizeof(bool) * m_nKeyCount);
	memset(m_bPrevKeyStates, 0, sizeof(bool) * m_nKeyCount);
	memset(m_ksKeyboardKeys, 0, sizeof(KeyState) * m_nKeyCount);

	memset(m_bCurrentMouseKeyStates, 0, sizeof(bool) * m_nMouseKeyCount);
	memset(m_bPrevMouseKeyStates, 0, sizeof(bool) * m_nMouseKeyCount);
	memset(m_ksMouseKeys, 0, sizeof(KeyState) * m_nMouseKeyCount);
}

InputManager::~InputManager() {}

//Get the state of the keyboard key

InputManager::KeyState const & InputManager::GetKey(const KB_KEY & Key) const {
	return m_ksKeyboardKeys[static_cast<uint8_t>(Key)];
}

//Get the state of the mouse key

InputManager::KeyState const & InputManager::GetMouseButton(const M_BUTTON & Key) const {
	return m_ksMouseKeys[static_cast<uint8_t>(Key)];
}

//Get the normalized x coordinate of the mouse position

float const & InputManager::GetMouseXNorm() const {
	return m_fMousePosX;
}

//Get the normalized y coordinate of the mouse position

float const & InputManager::GetMouseYNorm() const {
	return m_fMousePosY;
}

//Get the x coordinate of the mouse position (not normalized)

short const & InputManager::GetMouseX() const {
	return m_nMousePosX;
}

//Get the y coordinate of the mouse position (not normalized)

short const & InputManager::GetMouseY() const {
	return m_nMousePosY;
}

//Get a refernce to the singleton 

InputManager & InputManager::GetSingleton() {
	return m_singleton;
}

//Process the inputs

void InputManager::ProcessInputs() {
	//First process Keyboard keys. Loop through every entry in m_bCurrentKeyStates and m_bPrevKeyStates
	//and compare them to determine if the particular key is just pressed, released or keep holding down
	for (unsigned short i = 0; i < m_nKeyCount; i++) {
		//Get the refference to the bool in m_bCurrentKeyStates array in index i
		const bool& currentKey = m_bCurrentKeyStates[i];
		//Get the refference to the bool in m_bPrevKeyStates array in index i
		bool& prevKey = m_bPrevKeyStates[i];
		//Get the refference to the element of m_ksKeyboardKeys array in index i
		KeyState& keyState = m_ksKeyboardKeys[i];

		//Set all states of the current key to false
		keyState.bPressed = false; keyState.bReleased = false;

		//Check if the current key equals to prev key
		if (currentKey != prevKey) {

			if (currentKey) {
				keyState.bPressed = !keyState.bHeld;
				keyState.bHeld = true;
			}
			else {
				keyState.bReleased = true;
				keyState.bHeld = false;
			}
		}

		prevKey = currentKey;
	}

	//Now process mouse keys.Loop through every entry in m_bCurrentMouseKeyStates and m_bPrevMouseKeyStates
	//and compare them to determine if the particular key is just pressed, released or keep holding down
	for (unsigned short i = 0; i < m_nMouseKeyCount; i++) {
		//Get the refference to the bool in m_bCurrentKeyStates array in index i
		const bool& currentKey = m_bCurrentMouseKeyStates[i];
		//Get the refference to the bool in m_bPrevKeyStates array in index i
		bool& prevKey = m_bPrevMouseKeyStates[i];
		//Get the refference to the element of m_ksKeyboardKeys array in index i
		KeyState& keyState = m_ksMouseKeys[i];

		//Set all states of the current key to false
		keyState.bPressed = false; keyState.bReleased = false;

		//Check if the current key equals to prev key
		if (currentKey != prevKey) {

			if (currentKey) {
				keyState.bPressed = !keyState.bHeld;
				keyState.bHeld = true;
			}
			else {
				keyState.bReleased = true;
				keyState.bHeld = false;
			}
		}

		prevKey = currentKey;
	}

	UpdateMouse();
}

//Calculate the normalized mouse coord and Update it

void InputManager::UpdateMouse() {
	//Calculate the normalized mouse positions
	m_fMousePosX = (float)m_nMousePosX / (float)m_nCurrentWindowWidth;
	m_fMousePosY = (float)m_nMousePosY / (float)m_nCurrentWindowHeight;


}
