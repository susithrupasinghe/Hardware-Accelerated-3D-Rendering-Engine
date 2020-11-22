#ifndef ENGINEBASE_H
#define ENGINEBASE_H

//Local Includes
#include "GameWindow.h"
#include "InputManager.h"
#include "Renderer.h"

//Standard Includes
#include <cstdint>
#include <string>
#include <atomic>
#include <optional>


class EngineBase {
public:
	EngineBase(
#if defined (UNICODE) || defined (_UNICODE)
		std::wstring AppName = L"Defualt App",
#else
		std::string AppName = "Defualt App",
#endif
		int32_t WndWidth = 800,
		int32_t WndHeight = 600

	);

	int Run();

	~EngineBase();

protected:
	//Runs once when the renderer started
	virtual bool OnStart() = 0;
	//Runs every frame 
	virtual bool OnUpdate(float dt) = 0;
	//Runs when the renderer finish rendering
	virtual bool OnDestroy();

protected:

	//A reference to InputManager singleton
	InputManager& Input;

	//Get the pointer to the renderer object
	constexpr Renderer* GetRenderer() {
		return m_ptrRenderer;
	}

	//Get the pointer to the GameWindow object
	constexpr GameWindow* GetWindow() {
		return m_ptrWnd;
	}

	//Get the width of the window
	constexpr int32_t GetWidth() {
		return m_nWndWidth;
	}


	//Get the height of the window
	constexpr int32_t GetHeight() {
		return m_nWndHeight;
	}

private:
	void EngineThread();
	static std::optional<LRESULT> EngineWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	int32_t m_nWndWidth = 800; // Width of the game window (in pixels)
	int32_t m_nWndHeight = 600; // Height of the game window (in pixels)
	// Name of the Application
#if defined (UNICODE) || defined (_UNICODE)
	std::wstring m_sAppName = L"Defualt App";
#else
	std::string m_sAppName = "Defualt App";
#endif

	// Pointer to the GameWindow object to be created
	GameWindow* m_ptrWnd = nullptr;

	// Pointer to the Renderer object to be created
	Renderer* m_ptrRenderer = nullptr;


	static std::atomic<bool> m_atomicBoolKeepEngineThreadActive;
};

#endif //!RENDERINGENGINE_BASE_H
