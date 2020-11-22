#include "GameWindow.h"

#include <cstdint>

//WindowClass Class

//This GetModuleHandle(nullptr) function returns a handle to the current instance of the application.
//This is Same as the hInstance arg parsed to WinMain() function.
//But WNDCLASSEX expects a handle to the instance that contains the Window Procedure. Since now we are 
//using WindowClass as source form it's fine. But if we moved this code to a dll file this becomes unusable
//because then the instance that contains the WndProc is the instance to that dll. GetModuleHandle(nullptr)
//only returns a pointer to a current instance of the application. Since we are using this as source form
//It won't become a problem. But is we ever decide to move the engine to a dll file we have to reconsider about this code
GameWindow::WindowClass GameWindow::WindowClass::m_singleton(GetModuleHandle(nullptr));

GameWindow::WindowClass::WindowClass(HINSTANCE hInstance) : m_hInstance(hInstance) {
	//To register a window class on windows first we must create and fill the WNDCLASSEX struct
	//and pass the pointer to that struct we created to RegisterClassEx() function.

	WNDCLASSEX wcex = {};

	//Size of the WNDCLASSEX struct in bytes
	wcex.cbSize = sizeof(WNDCLASSEX);

	//Styles of the window based on this class should have
	//All the styles we can enter here starts with CS_ (Stands for Class Style) prefix.
	//Right now we really don't need any Class Style.
	//So we set it to 0.
	wcex.style = 0;

	//A pointer to the Window procedure We want windows from this class to follow.
	wcex.lpfnWndProc = WndProc_Init;

	//Number of extra bytes to be allocated after this WNDCLASSEX struct
	//We don't need this so set to 0.
	wcex.cbClsExtra = 0;

	//Number of extra bytes to be allocated after this the window
	//We don't need this so set to 0.
	wcex.cbWndExtra = 0;

	//This is important. This is the handle to the application instance that holds the WindowProcedure
	wcex.hInstance = m_hInstance;

	//This is to set our custom icon. We are not setting that.
	wcex.hIcon = nullptr;

	//We'll use default cursor
	wcex.hCursor = nullptr;

	//Don't need this either
	wcex.hbrBackground = nullptr;

	//Don't need this either
	wcex.lpszMenuName = nullptr;

	//This is very important. This is a pointer to a null terminated string which contains the class name
	//If a class with this name already exist the RegisterClass() function will fail
	wcex.lpszClassName = m_sClassName.c_str();

	wcex.hIconSm = nullptr;

	//Register the class
	//RegisterClassEx() function returns non-zero value if it succeded.
	if (RegisterClassEx(&wcex) == 0) {
		throw EXCEPT_WIN_LAST_ERR();
	}
}

GameWindow::WindowClass::WindowClass() : WindowClass(GetModuleHandle(nullptr)) {}

GameWindow::WindowClass::~WindowClass() {
	//Unregister the registered class like a good programmer
	UnregisterClass(m_sClassName.c_str(), m_hInstance);
}

#if defined(UNICODE) || defined (_UNICODE)
constexpr std::wstring const& GameWindow::WindowClass::GetClsName() const {
#else
constexpr std::string const & GameWindow::WindowClass::GetClsName() const {
#endif
	return m_sClassName;
}

// Get a reference to the singleton

constexpr GameWindow::WindowClass & GameWindow::WindowClass::GetSingleton() {
	return m_singleton;
}


LRESULT GameWindow::WindowClass::WndProc_Init(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GameWindow* pWindow = nullptr;
	switch (uMsg)
	{
	case WM_NCCREATE: {
		pWindow = static_cast<GameWindow*> (reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&GameWindow::WindowClass::WndProc));
		return GameWindow::WindowClass::WndProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT GameWindow::WindowClass::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Get the pointer to GameWindow class associated with hWnd
	GameWindow* pGameWindow = (GameWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	switch (uMsg)
	{
	case WM_CREATE: {
		m_InputManager.m_nCurrentWindowWidth = (short)pGameWindow->m_nWindowWidth;
		m_InputManager.m_nCurrentWindowHeight = (short)pGameWindow->m_nWindowHeight;
		return 0;
		break;
	}
	case WM_SETFOCUS: {
		m_InputManager.m_nCurrentWindowWidth = (short)pGameWindow->m_nWindowWidth;
		m_InputManager.m_nCurrentWindowHeight = (short)pGameWindow->m_nWindowHeight;
		return 0;
		break;
	}

	case WM_MOUSEMOVE: {
		POINTS pt = MAKEPOINTS(lParam);
		m_InputManager.m_nMousePosX = pt.x;
		m_InputManager.m_nMousePosY = pt.y;
		return 0;
		break;
	}
	case WM_LBUTTONDOWN: {
		m_InputManager.m_bCurrentMouseKeyStates[static_cast<uint8_t>(M_BUTTON::M_LB)] = true;
		return 0;
		break;
	}

	case WM_LBUTTONUP: {
		m_InputManager.m_bCurrentMouseKeyStates[static_cast<uint8_t>(M_BUTTON::M_LB)] = false;
		return 0;
		break;
	}

	case WM_RBUTTONDOWN: {
		m_InputManager.m_bCurrentMouseKeyStates[static_cast<uint8_t>(M_BUTTON::M_RB)] = true;
		return 0;
		break;
	}

	case WM_RBUTTONUP: {
		m_InputManager.m_bCurrentMouseKeyStates[static_cast<uint8_t>(M_BUTTON::M_RB)] = false;
		return 0;
		break;
	}

	case WM_MBUTTONDOWN: {
		m_InputManager.m_bCurrentMouseKeyStates[static_cast<uint8_t>(M_BUTTON::M_MB)] = true;
		return 0;
		break;
	}
	case WM_MBUTTONUP: {
		m_InputManager.m_bCurrentMouseKeyStates[static_cast<uint8_t>(M_BUTTON::M_MB)] = false;
		return 0;
		break;
	}
	case WM_KEYDOWN: {
		m_InputManager.m_bCurrentKeyStates[(uint8_t)wParam] = true;
		return 0;
		break;
	}
	case WM_KEYUP: {
		m_InputManager.m_bCurrentKeyStates[(uint8_t)wParam] = false;
		return 0;
		break;
	}

	case WM_CLOSE: {

		DestroyWindow(hWnd);
		return 0;
		break;
	}
	case WM_DESTROY: {
		if (--GameWindow::m_nWindowCount == 0)
			PostQuitMessage(0);
		break;
	}
	default:
		break;
	
	}

	if (pGameWindow->m_pUserDefinedWindowProc != nullptr) {
		std::optional<LRESULT> userDefinedWndProc = pGameWindow->m_pUserDefinedWindowProc(hWnd, uMsg, wParam, lParam);
		if (userDefinedWndProc.has_value())
			return userDefinedWndProc.value();
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//End WindowClass Class


//GameWindow Class

DWORD GameWindow::m_dwUserDefinedWindowStylesConfig = 0;
DWORD GameWindow::m_dwUserDefinedExWindowStylesConfig = 0;
std::optional<LRESULT> (*GameWindow::m_pUserDefinedWindowProcConfig)(HWND, UINT, WPARAM, LPARAM) = nullptr;
InputManager& GameWindow::m_InputManager = InputManager::GetSingleton();
unsigned short GameWindow::m_nWindowCount = 0;

//GameWindow class constructor

GameWindow::GameWindow(
#if defined (UNICODE) || (_UNICODE)
	std::wstring WindowName,
#else
	std::string WindowName,
#endif
	uint32_t WindowWidth,
	uint32_t WindowHeight, 
	HINSTANCE hInstance
) 
	: 
	m_sWindowName(WindowName), 
	m_nWindowWidth(WindowWidth), 
	m_nWindowHeight(WindowHeight), 
	m_hInstance(hInstance), 
	m_wndCls(WindowClass::GetSingleton()) {

	//Set the window styles and ex styles
	m_dwWindowStyles = WS_BORDER | WS_CAPTION | WS_SYSMENU;
	m_dwExWindowStyles = WS_EX_CLIENTEDGE;

	if (m_dwUserDefinedWindowStylesConfig != 0) {
		m_dwWindowStyles = m_dwUserDefinedWindowStylesConfig;
		m_dwUserDefinedWindowStylesConfig = 0;
	}

	if (m_dwUserDefinedExWindowStylesConfig != 0) {
		m_dwExWindowStyles = m_dwUserDefinedExWindowStylesConfig;
		m_dwUserDefinedExWindowStylesConfig = 0;
	}

	if (m_pUserDefinedWindowProcConfig != nullptr) {
		m_pUserDefinedWindowProc = m_pUserDefinedWindowProcConfig;
		m_pUserDefinedWindowProcConfig = nullptr;
	}


	RECT windowSize = { 0,0,(LONG)m_nWindowWidth ,(LONG)m_nWindowHeight };

	//Get the real size of the window after we applied all the styles we requested 
	if (AdjustWindowRectEx(&windowSize, m_dwWindowStyles, NULL, m_dwExWindowStyles) == 0) {
		throw EXCEPT_WIN_LAST_ERR();
	}

	//Create a window based on given informations. CraeteWindowEx() funstion returns a valid handle to the created window if the function succeeded. Otherwise it will return null ptr. We have to check if the returened ptr isn't a nullptr 
	m_hWnd = CreateWindowEx(m_dwExWindowStyles, m_wndCls.GetClsName().c_str(), m_sWindowName.c_str(), m_dwWindowStyles, CW_USEDEFAULT, CW_USEDEFAULT, (int)(windowSize.right - windowSize.left), (int)(windowSize.bottom - windowSize.top), nullptr, nullptr, m_hInstance, this);

	//Check if the window created successfully
	if (m_hWnd == nullptr) {
		throw EXCEPT_WIN_LAST_ERR();
	}


	//Show window
	ShowWindow(m_hWnd, SW_NORMAL);

	m_nWindowCount++;

	////Set the userdata associated with this window to be 
	//if (SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG_PTR)this) != 0) 
	//{
	//	throw EXCEPT_WIN_LAST_ERR();
	//}

}

GameWindow::GameWindow(
#if defined (UNICODE) || (_UNICODE)
	std::wstring WindowName,
#else
	std::string WindowName,
#endif
	uint32_t WindowWidth, 
	uint32_t WindowHeight
) 
	: 
	GameWindow(WindowName, WindowWidth, WindowHeight, GetModuleHandle(NULL)) 
{}

//Change the window name

void GameWindow::SetWindowTitle(
#if defined (UNICODE) || defined (_UNICODE)
	const std::wstring& title
#else
	const std::string& title
#endif
) const {
	SetWindowText(m_hWnd, title.c_str());
}

std::optional<int> GameWindow::ProcessMessages()
{
	MSG Msg;
	while (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE) != 0) {
		if (Msg.message == WM_QUIT)
			return Msg.message;
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	m_InputManager.ProcessInputs();
	return {};
}

GameWindow::~GameWindow() {}



//End GameWindow Class