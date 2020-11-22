#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <cstdint>


//Input manager responsible for keeping tracks of the mouse and keyboard inputs for all GameWindows.
//(Even though we are currently using a single window). We are implementing InputManager class as
//a singleton so we can access it from anywhere


//Scraped from https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-tvtt/261ddfb0-ce10-4380-9b7a-4b50f482b8ec
//KEY_VK_LBUTTON = 0x0001,
//KEY_VK_RBUTTON = 0x0002,
//KEY_VK_CANCEL = 0x0003,
//KEY_VK_BACK = 0x0008,
//KEY_VK_TAB = 0x0009,
//KEY_VK_CLEAR = 0x000C,
//KEY_VK_RETURN = 0x0D,
//KEY_VK_SHIFT = 0x10,
//KEY_VK_CONTROL = 0x11,
//KEY_VK_MENU = 0x12,
//KEY_VK_PAUSE = 0x0013,
//KEY_VK_CAPITAL = 0x0014,
//KEY_VK_ESCAPE = 0x001B,
//KEY_VK_SPACE = 0x0020,
//KEY_VK_PRIOR = 0x0021,
//KEY_VK_NEXT = 0x0022,
//KEY_VK_END = 0x0023,
//KEY_VK_HOME = 0x0024,
//KEY_VK_LEFT = 0x0025,
//KEY_VK_UP = 0x0026,
//KEY_VK_RIGHT = 0x0027,
//KEY_VK_DOWN = 0x0028,
//KEY_VK_SELECT = 0x0029,
//KEY_VK_PRINT = 0x002A,
//KEY_VK_EXECUTE = 0x002B,
//KEY_VK_SNAPSHOT = 0x002C,
//KEY_VK_INSERT = 0x002D,
//KEY_VK_DELETE = 0x002E,
//KEY_VK_HELP = 0x002F,
//KEY_VK_0 = 0x0030,
//KEY_VK_1 = 0x0031,
//KEY_VK_2 = 0x0032,
//KEY_VK_3 = 0x0033,
//KEY_VK_4 = 0x0034,
//KEY_VK_5 = 0x0035,
//KEY_VK_6 = 0x0036,
//KEY_VK_7 = 0x0037,
//KEY_VK_8 = 0x0038,
//KEY_VK_9 = 0x0039,
//KEY_VK_A = 0x0041,
//KEY_VK_B = 0x0042,
//KEY_VK_C = 0x0043,
//KEY_VK_D = 0x0044,
//KEY_VK_E = 0x0045,
//KEY_VK_F = 0x0046,
//KEY_VK_G = 0x0047,
//KEY_VK_H = 0x0048,
//KEY_VK_I = 0x0049,
//KEY_VK_J = 0x004A,
//KEY_VK_K = 0x004B,
//KEY_VK_L = 0x004C,
//KEY_VK_M = 0x004D,
//KEY_VK_N = 0x004E,
//KEY_VK_O = 0x004F,
//KEY_VK_P = 0x0050,
//KEY_VK_Q = 0x0051,
//KEY_VK_R = 0x0052,
//KEY_VK_S = 0x0053,
//KEY_VK_T = 0x0054,
//KEY_VK_U = 0x0055,
//KEY_VK_V = 0x0056,
//KEY_VK_W = 0x0057,
//KEY_VK_X = 0x0058,
//KEY_VK_Y = 0x0059,
//KEY_VK_Z = 0x005A,
//KEY_VK_LWIN = 0x005B,
//KEY_VK_RWIN = 0x005C,
//KEY_VK_APPS = 0x005D,
//KEY_VK_SLEEP = 0x005F,
//KEY_VK_NUMPAD0 = 0x0060,
//KEY_VK_NUMPAD1 = 0x0061,
//KEY_VK_NUMPAD2 = 0x0062,
//KEY_VK_NUMPAD3 = 0x0063,
//KEY_VK_NUMPAD4 = 0x0064,
//KEY_VK_NUMPAD5 = 0x0065,
//KEY_VK_NUMPAD6 = 0x0066,
//KEY_VK_NUMPAD7 = 0x0067,
//KEY_VK_NUMPAD8 = 0x0068,
//KEY_VK_NUMPAD9 = 0x0069,
//KEY_VK_MULTIPLY = 0x006A,
//KEY_VK_ADD = 0x006B,
//KEY_VK_SEPARATOR = 0x006C,
//KEY_VK_SUBTRACT = 0x006D,
//KEY_VK_DECIMAL = 0x006E,
//KEY_VK_DIVIDE = 0x006F,
//KEY_VK_F1 = 0x0070,
//KEY_VK_F2 = 0x0071,
//KEY_VK_F3 = 0x0072,
//KEY_VK_F4 = 0x0073,
//KEY_VK_F5 = 0x0074,
//KEY_VK_F6 = 0x0075,
//KEY_VK_F7 = 0x0076,
//KEY_VK_F8 = 0x0077,
//KEY_VK_F9 = 0x0078,
//KEY_VK_F10 = 0x0079,
//KEY_VK_F11 = 0x007A,
//KEY_VK_F12 = 0x007B,
//KEY_VK_F13 = 0x007C,
//KEY_VK_F14 = 0x007D,
//KEY_VK_F15 = 0x007E,
//KEY_VK_F16 = 0x007F,
//KEY_VK_F17 = 0x0080,
//KEY_VK_F18 = 0x0081,
//KEY_VK_F19 = 0x0082,
//KEY_VK_F20 = 0x0083,
//KEY_VK_F21 = 0x0084,
//KEY_VK_F22 = 0x0085,
//KEY_VK_F23 = 0x0086,
//KEY_VK_F24 = 0x0087H,
//KEY_VK_NUMLOCK = 0x0090,
//KEY_VK_SCROLL = 0x0091,
//KEY_VK_LSHIFT = 0x00A0,
//KEY_VK_RSHIFT = 0x00A1,
//KEY_VK_LCONTROL = 0x00A2,
//KEY_VK_RCONTROL = 0x00A3,
//KEY_VK_LMENU = 0x00A4,
//KEY_VK_RMENU = 0x00A5,

//KB_KEY enum contains the indices of the corresponding key of that arrays from InputManager class
enum class KB_KEY : uint8_t {
	KB_LBUTTON = 0x0001,
	KB_RBUTTON = 0x0002,
	KB_CANCEL = 0x0003,
	KB_BACK = 0x0008,
	KB_TAB = 0x0009,
	KB_CLEAR = 0x000C,
	KB_RETURN = 0x0D,
	KB_SHIFT = 0x10,
	KB_CONTROL = 0x11,
	KB_MENU = 0x12,
	KB_PAUSE = 0x0013,
	KB_CAPITAL = 0x0014,
	KB_ESCAPE = 0x001B,
	KB_SPACE = 0x0020,
	KB_PRIOR = 0x0021,
	KB_NEXT = 0x0022,
	KB_END = 0x0023,
	KB_HOME = 0x0024,
	KB_LEFT = 0x0025,
	KB_UP = 0x0026,
	KB_RIGHT = 0x0027,
	KB_DOWN = 0x0028,
	KB_SELECT = 0x0029,
	KB_PRINT = 0x002A,
	KB_EXECUTE = 0x002B,
	KB_SNAPSHOT = 0x002C,
	KB_INSERT = 0x002D,
	KB_DELETE = 0x002E,
	KB_HELP = 0x002F,
	KB_N0 = 0x0030,
	KB_N1 = 0x0031,
	KB_N2 = 0x0032,
	KB_N3 = 0x0033,
	KB_N4 = 0x0034,
	KB_N5 = 0x0035,
	KB_N6 = 0x0036,
	KB_N7 = 0x0037,
	KB_N8 = 0x0038,
	KB_N9 = 0x0039,
	KB_A = 0x0041,
	KB_B = 0x0042,
	KB_C = 0x0043,
	KB_D = 0x0044,
	KB_E = 0x0045,
	KB_F = 0x0046,
	KB_G = 0x0047,
	KB_H = 0x0048,
	KB_I = 0x0049,
	KB_J = 0x004A,
	KB_K = 0x004B,
	KB_L = 0x004C,
	KB_M = 0x004D,
	KB_N = 0x004E,
	KB_O = 0x004F,
	KB_P = 0x0050,
	KB_Q = 0x0051,
	KB_R = 0x0052,
	KB_S = 0x0053,
	KB_T = 0x0054,
	KB_U = 0x0055,
	KB_V = 0x0056,
	KB_W = 0x0057,
	KB_X = 0x0058,
	KB_Y = 0x0059,
	KB_Z = 0x005A,
	KB_LWIN = 0x005B,
	KB_RWIN = 0x005C,
	KB_APPS = 0x005D,
	KB_SLEEP = 0x005F,
	KB_NUMPAD0 = 0x0060,
	KB_NUMPAD1 = 0x0061,
	KB_NUMPAD2 = 0x0062,
	KB_NUMPAD3 = 0x0063,
	KB_NUMPAD4 = 0x0064,
	KB_NUMPAD5 = 0x0065,
	KB_NUMPAD6 = 0x0066,
	KB_NUMPAD7 = 0x0067,
	KB_NUMPAD8 = 0x0068,
	KB_NUMPAD9 = 0x0069,
	KB_MULTIPLY = 0x006A,
	KB_ADD = 0x006B,
	KB_SEPARATOR = 0x006C,
	KB_SUBTRACT = 0x006D,
	KB_DECIMAL = 0x006E,
	KB_DIVIDE = 0x006F,
	KB_F1 = 0x0070,
	KB_F2 = 0x0071,
	KB_F3 = 0x0072,
	KB_F4 = 0x0073,
	KB_F5 = 0x0074,
	KB_F6 = 0x0075,
	KB_F7 = 0x0076,
	KB_F8 = 0x0077,
	KB_F9 = 0x0078,
	KB_F10 = 0x0079,
	KB_F11 = 0x007A,
	KB_F12 = 0x007B,
	KB_F13 = 0x007C,
	KB_F14 = 0x007D,
	KB_F15 = 0x007E,
	KB_F16 = 0x007F,
	KB_F17 = 0x0080,
	KB_F18 = 0x0081,
	KB_F19 = 0x0082,
	KB_F20 = 0x0083,
	KB_F21 = 0x0084,
	KB_F22 = 0x0085,
	KB_F23 = 0x0086,
	KB_F24 = 0x0087,
	KB_NUMLOCK = 0x0090,
	KB_SCROLL = 0x0091,
	KB_LSHIFT = 0x00A0,
	KB_RSHIFT = 0x00A1,
	KB_LCONTROL = 0x00A2,
	KB_RCONTROL = 0x00A3,
	KB_LMENU = 0x00A4,
	KB_RMENU = 0x00A5,
};

//M_BUTTON contains the mouse buttons
enum class M_BUTTON : uint8_t {
	M_LB = 0,
	M_MB = 1,
	M_RB = 2,
};

class InputManager {
	//Make GameWindow a friend of InputManager so we can access private members of InputManager
	friend class GameWindow;

	//Make EngineBase a friend of InputManager so we can access private members of InputManager
	friend class EngineBase;

public:
	struct KeyState {
		bool bHeld = false;
		bool bPressed = false;
		bool bReleased = false;
	};

private:
	InputManager();
	~InputManager();


public:
	//Get the state of the keyboard key
	KeyState const & GetKey(const KB_KEY& Key) const;

	//Get the state of the mouse key
	KeyState const & GetMouseButton(const M_BUTTON& Key) const;

	//Get the normalized x coordinate of the mouse position
	float const & GetMouseXNorm() const;

	//Get the normalized y coordinate of the mouse position
	float const & GetMouseYNorm() const;

	//Get the x coordinate of the mouse position (not normalized)
	short const & GetMouseX() const;

	//Get the y coordinate of the mouse position (not normalized)
	short const & GetMouseY() const;

	//Get a refernce to the singleton 
	static InputManager& GetSingleton();

private:
	//Process the inputs
	void ProcessInputs();

	//Calculate the normalized mouse coord and Update it
	void UpdateMouse();

private:
	static constexpr int m_nKeyCount = 256;
	static constexpr int m_nMouseKeyCount = 3;

	//m_bCurrentKeyStates bool array keeps track of if the particular key is pressed or not in the current frame
	bool m_bCurrentKeyStates[m_nKeyCount];
	//m_bCurrentMouseKeyStates bool array keeps track of if the particular mouse key is pressed or not in the current frame
	bool m_bCurrentMouseKeyStates[m_nMouseKeyCount];

	//m_bPrevKeyStates bool array keeps track of if the particular key is pressed or not in the previous frame
	bool m_bPrevKeyStates[m_nKeyCount];
	//m_bPrevMouseKeyStates bool array keeps track of if the particular mouse key is pressed or not in the previous frame
	bool m_bPrevMouseKeyStates[m_nMouseKeyCount];

	KeyState m_ksKeyboardKeys[m_nKeyCount];
	KeyState m_ksMouseKeys[m_nMouseKeyCount];

	//Stores the x coordinate of the mouse relative to the window's left edge. (And this is in normalized space)
	float m_fMousePosX = 0.0f;
	//Stores the y coordinate of the mouse relative to the window's top edge. (And this is in normalized space)
	float m_fMousePosY = 0.0f;

	//Stores the x coordinate of the mouse relative to the window's left edge.
	short m_nMousePosX = 0;
	//Stores the y coordinate of the mouse relative to the window's top edge.
	short m_nMousePosY = 0;

	short m_nCurrentWindowWidth = 800;
	short m_nCurrentWindowHeight = 600;

private:
	static InputManager m_singleton;
};

#endif // !INPUTMANAGER_H
