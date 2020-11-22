#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H


//Windows INcludes
#include "WindowsInclude.h" //Include windows include

//Local Includes
#include "Exceptions.h" //Include the custom exceptions
#include "InputManager.h" //Include the Input manager

//Standard Includes
#include <string>
#include <cstdint>
#include <optional>

//Game window responsible for making a window for the engine. Currently this class holds the platform specific code for opening a window.
//Since I am currently making a Direct3D Rendering engine, this whole project should contain windows specific code only. If I decided to make
//engine cross platform, there has to be some major changes to make to the code.
class GameWindow {

	//To open a window first we must register a window class (don't get confused this is not a c++ class) on OS's side. 
	//On Windows OS every window we open must be opened from a window class.
	//This window class stores some commen behaviors, styles, common resources (like icons), and window procedure of the window.
	//Every window opened based on this class will have these styles behaviors and icon. And yes a single class can open multiple windows.
	//Theoriticaly we can open a window from a already registered general window class but I'm gonna register my own window class.
	//We can register individual classes for each window but we are not going to do that. I need every opened window in this application
	//to be based on a single Window class and share the same window procedure.

	//So to register this window class I'm going to make a c++ class called WindowClass and make it responsible for registering and
	//Unregistering Window class. Since we are not going to need this WindowClass class other than inside GameWindow class, I'm
	//going to declare WindowClass class inside GameWindow class as a private field. And also we only need a single instance of this
	//class for all GameWindows I'm going to make it a singleton class.

private:
	class WindowClass {
	private:
		WindowClass(HINSTANCE hInstance);
		WindowClass();

		~WindowClass();

	public:
		//Get the class name
#if defined(UNICODE) || defined (_UNICODE)
		constexpr std::wstring const& GetClsName() const;
#else
		constexpr std::string const & GetClsName() const;
#endif
	public:
		// Get a reference to the singleton
		static constexpr WindowClass& GetSingleton();

	private:
		
		//This is just WndProc for initializing
		static LRESULT CALLBACK WndProc_Init(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//The window procedure
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	private:
		// A Handle to the instance which constains the Window Procedure
		HINSTANCE m_hInstance = nullptr; 

		// The name of the window class
#if defined(UNICODE) || defined (_UNICODE)
		std::wstring const m_sClassName = L"Rendering_Engine_3D";
#else
		std::string const m_sClassName = "Rendering_Engine_3D";
#endif

	private:
		static WindowClass m_singleton; // static singleton
	};
 

public:
	//GameWindow class constructor
	GameWindow(
#if defined(UNICODE) || defined (_UNICODE)
		std::wstring WindowName,
#else
		std::string WindowName, 
#endif
		uint32_t WindowWidth, 
		uint32_t WindowHeight, 
		HINSTANCE hInstance
	);

	GameWindow(
#if defined(UNICODE) || defined (_UNICODE)
		std::wstring WindowName,
#else
		std::string WindowName,
#endif
		uint32_t WindowWidth, 
		uint32_t WindowHeight
	);

	//Get a reffernce to the window handle
	constexpr HWND const & GetHWND() {
		return m_hWnd;
	}


	//Get the WindowName
#if defined(UNICODE) || defined (_UNICODE)
	constexpr std::wstring const& GetWindowName()
#else
	constexpr std::string const & GetWindowName()
#endif
	{
		return m_sWindowName;
	}

	//Get window width
	constexpr uint32_t const & GetWindowWidth() {
		return m_nWindowWidth;
	}

	//Get window height
	constexpr uint32_t const & GetWindowHeight() {
		return m_nWindowHeight;
	}

	//Change the window name
	void SetWindowTitle(
#if defined (UNICODE) || defined (_UNICODE)
		const std::wstring& title
#else
		const std::string& title
#endif
	) const;

	//Process Messages for all windows
	static std::optional<int> ProcessMessages();

	~GameWindow();

public:
	//Window Configuration functions

	constexpr static void SetWindowStyles(const DWORD& dwStyles) {
		m_dwUserDefinedWindowStylesConfig = dwStyles;
	}

	constexpr static void SetWindowExStyles(const DWORD& dwExStyles) {
		m_dwUserDefinedExWindowStylesConfig = dwExStyles;
	}

	constexpr static void SetUserDefinedWndProc(std::optional<LRESULT>(* const& m_pWndProc)(HWND, UINT, WPARAM, LPARAM)) {
		m_pUserDefinedWindowProcConfig = m_pWndProc;
	}

private:
	// Handle to the created window
	HWND m_hWnd = nullptr;

	//Name of the window
#if defined (UNICODE) || defined (_UNICODE)
	std::wstring m_sWindowName = "Default Window";
#else
	std::string m_sWindowName = "Default Window";
#endif

	//Width of the window (in Pixels)
	uint32_t m_nWindowWidth = 800;

	//height of the window (in pixels)
	uint32_t m_nWindowHeight = 600;

	//Handle to the cuurent instance that requested to open the window
	HINSTANCE m_hInstance = nullptr;

	//Window styles
	DWORD m_dwWindowStyles = 0;

	//Extended Window styles
	DWORD m_dwExWindowStyles = 0;

	//A refference to the WindowClass class
	WindowClass& m_wndCls;

	//Custom user defined window proc
	std::optional<LRESULT>(*m_pUserDefinedWindowProc) (HWND, UINT, WPARAM, LPARAM) = nullptr;

private:
	//Window configuration variables
	static DWORD m_dwUserDefinedWindowStylesConfig;
	static DWORD m_dwUserDefinedExWindowStylesConfig;
	static std::optional<LRESULT>(*m_pUserDefinedWindowProcConfig) (HWND, UINT, WPARAM, LPARAM);

	//A static reference to Input manager singleton
	static InputManager& m_InputManager;

	//Total opened windows count
	static unsigned short m_nWindowCount;
};


#endif // !GAMEWINDOW_H

