#include "EngineBase.h"

//Local Includes
#include "Exceptions.h"
#include "SimpleTimer.h"

//Standard Includes
#include <thread>

std::atomic<bool> EngineBase::m_atomicBoolKeepEngineThreadActive = false;

EngineBase::EngineBase(
#if defined (UNICODE) || defined (_UNICODE)
	std::wstring AppName = L"Defualt App",
#else
	std::string AppName,
#endif
	int32_t WndWidth ,
	int32_t WndHeight 

):
	m_sAppName(AppName),
	m_nWndWidth(WndWidth),
	m_nWndHeight(WndHeight),
	Input(InputManager::GetSingleton())
{

}

int EngineBase::Run() {
	//Try creating a GameWindow
	try {
		//Set SetUserDefinedWndProc to EngineWndProc
		GameWindow::SetUserDefinedWndProc(EngineWndProc);

		//Create a GameWindow Object
		m_ptrWnd = new GameWindow(m_sAppName, m_nWndWidth, m_nWndHeight);
	}

	// See if the exception is a GeneralException
	catch (const GeneralException& e) {
		MessageBox(nullptr, e.what(), "GeneralException has been thrown!", MB_ICONERROR | MB_OK);
	}

	// See if the exception is a std exception
	catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard has been thrown!", MB_ICONERROR | MB_OK);
	}

	//Unknown Error
	catch (...) {
		MessageBox(nullptr, "Information Unavailable", "Unknown Error!", MB_ICONERROR | MB_OK);
	}

	//Start rendering part in a different thread
	std::thread threadEngineThread = std::thread(&EngineBase::EngineThread, this);
	

	//Windows Message loop

	MSG msg = {};

	while (GetMessage(&msg, nullptr, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	m_atomicBoolKeepEngineThreadActive = false;

	//Wait for rendernig thread to finish
	threadEngineThread.join();

	return msg.message;

}

EngineBase::~EngineBase() {
	//Destroy the game window object
	if (m_ptrWnd != nullptr) delete m_ptrWnd;
}


//Runs when the renderer finish rendering

bool EngineBase::OnDestroy() {
	return true;
}

void EngineBase::EngineThread() {
	// Rendering process, Input handling part and all other stuff are handled by a different thread

	try {
		//Create a Renderer object
		m_ptrRenderer = new Renderer(m_ptrWnd->GetHWND());

		//Initialize a simple timer object to calculate the time for a frame
		SimpleTimer frameTimer;

		//Set engine active flag
		m_atomicBoolKeepEngineThreadActive = true;

		int16_t nFrameCount = 0;
		float fOneSecond = 0.0f;

		if (!OnStart()) {
			m_atomicBoolKeepEngineThreadActive = false;
		}

		while (m_atomicBoolKeepEngineThreadActive) {
			while (m_atomicBoolKeepEngineThreadActive) {
				
				//Calculate the time for a frame 
				float dt = frameTimer.Mark();

				//Process Inputs
				Input.ProcessInputs();


				if (!OnUpdate(dt)) {
					//OnUpdate() failed for some reason
					m_atomicBoolKeepEngineThreadActive = false;
				}

				//Swap the backbuffer
				m_ptrRenderer->Render();

				//Calculate the frames per second
				fOneSecond += dt;
				nFrameCount++;

				if (fOneSecond >= 1.0f) {
					m_ptrWnd->SetWindowTitle(m_ptrWnd->GetWindowName() + " | FPS : " +  std::to_string(nFrameCount));
					fOneSecond = 0.0f;
					nFrameCount = 0;
				}
			}

			if (!OnDestroy()) {
				//User denied to exit. Keep going
				m_atomicBoolKeepEngineThreadActive = true;
			}
		}

		//Delete the renderer object
		if (m_ptrRenderer != nullptr) delete m_ptrRenderer;


	}

	// See if the exception is a GeneralException
	catch (const GeneralException& e) {
		MessageBox(nullptr, e.what(), "GeneralException has been thrown!", MB_ICONERROR | MB_OK);
		PostQuitMessage(EXIT_FAILURE);
		return;
	}

	// See if the exception is a std exception
	catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard has been thrown!", MB_ICONERROR | MB_OK);
		PostQuitMessage(EXIT_FAILURE);
		return;
	}

	//Unknown Error
	catch (...) {
		MessageBox(nullptr, "Information Unavailable", "Unknown Error!", MB_ICONERROR | MB_OK);
		PostQuitMessage(EXIT_FAILURE);
		return;
	}

	//Post a quit message to the message queue
	PostQuitMessage(0);
	return;
}

std::optional<LRESULT> EngineBase::EngineWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_QUIT: {
		m_atomicBoolKeepEngineThreadActive = false;
		return 0;
	}
	default:
		break;
	}

	return {};
}
