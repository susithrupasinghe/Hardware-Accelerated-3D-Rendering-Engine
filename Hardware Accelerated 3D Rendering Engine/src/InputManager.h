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
	LBUTTON = 0x0001,
	RBUTTON = 0x0002,
	CANCEL = 0x0003,
	BACK = 0x0008,
	TAB = 0x0009,
	CLEAR = 0x000C,
	RETURN = 0x0D,
	SHIFT = 0x10,
	CONTROL = 0x11,
	MENU = 0x12,
	PAUSE = 0x0013,
	CAPITAL = 0x0014,
	ESCAPE = 0x001B,
	SPACE = 0x0020,
	PRIOR = 0x0021,
	NEXT = 0x0022,
	END = 0x0023,
	HOME = 0x0024,
	LEFT = 0x0025,
	UP = 0x0026,
	RIGHT = 0x0027,
	DOWN = 0x0028,
	SELECT = 0x0029,
	PRINT = 0x002A,
	EXECUTE = 0x002B,
	SNAPSHOT = 0x002C,
	INSERT = 0x002D,
	DEL = 0x002E,
	HELP = 0x002F,
	N0 = 0x0030,
	N1 = 0x0031,
	N2 = 0x0032,
	N3 = 0x0033,
	N4 = 0x0034,
	N5 = 0x0035,
	N6 = 0x0036,
	N7 = 0x0037,
	N8 = 0x0038,
	N9 = 0x0039,
	A = 0x0041,
	B = 0x0042,
	C = 0x0043,
	D = 0x0044,
	E = 0x0045,
	F = 0x0046,
	G = 0x0047,
	H = 0x0048,
	I = 0x0049,
	J = 0x004A,
	K = 0x004B,
	L = 0x004C,
	M = 0x004D,
	N = 0x004E,
	O = 0x004F,
	P = 0x0050,
	Q = 0x0051,
	R = 0x0052,
	S = 0x0053,
	T = 0x0054,
	U = 0x0055,
	V = 0x0056,
	W = 0x0057,
	X = 0x0058,
	Y = 0x0059,
	Z = 0x005A,
	LWIN = 0x005B,
	RWIN = 0x005C,
	APPS = 0x005D,
	SLEEP = 0x005F,
	NUMPAD0 = 0x0060,
	NUMPAD1 = 0x0061,
	NUMPAD2 = 0x0062,
	NUMPAD3 = 0x0063,
	NUMPAD4 = 0x0064,
	NUMPAD5 = 0x0065,
	NUMPAD6 = 0x0066,
	NUMPAD7 = 0x0067,
	NUMPAD8 = 0x0068,
	NUMPAD9 = 0x0069,
	MULTIPLY = 0x006A,
	ADD = 0x006B,
	SEPARATOR = 0x006C,
	SUBTRACT = 0x006D,
	DECIMAL = 0x006E,
	DIVIDE = 0x006F,
	F1 = 0x0070,
	F2 = 0x0071,
	F3 = 0x0072,
	F4 = 0x0073,
	F5 = 0x0074,
	F6 = 0x0075,
	F7 = 0x0076,
	F8 = 0x0077,
	F9 = 0x0078,
	F10 = 0x0079,
	F11 = 0x007A,
	F12 = 0x007B,
	F13 = 0x007C,
	F14 = 0x007D,
	F15 = 0x007E,
	F16 = 0x007F,
	F17 = 0x0080,
	F18 = 0x0081,
	F19 = 0x0082,
	F20 = 0x0083,
	F21 = 0x0084,
	F22 = 0x0085,
	F23 = 0x0086,
	F24 = 0x0087,
	NUMLOCK = 0x0090,
	SCROLL = 0x0091,
	LSHIFT = 0x00A0,
	RSHIFT = 0x00A1,
	LCONTROL = 0x00A2,
	RCONTROL = 0x00A3,
	LMENU = 0x00A4,
	RMENU = 0x00A5,
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
