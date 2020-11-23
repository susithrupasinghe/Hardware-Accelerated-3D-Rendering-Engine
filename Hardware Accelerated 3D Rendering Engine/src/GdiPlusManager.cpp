#include "GdiPlusManager.h"

#pragma comment(lib, "gdiplus.lib")

uint32_t GdiPlusManager::m_nGDIManagerRefCount = 0;
ULONG_PTR GdiPlusManager::m_ptrGDIToken = 0;

GdiPlusManager::GdiPlusManager()
{
	//If GdiPlusManager hasn't initialized before
	if (m_nGDIManagerRefCount++ == 0) {
		//Initialize gdiplus
		Gdiplus::GdiplusStartupInput input;
		input.GdiplusVersion = 1;
		input.DebugEventCallback = nullptr;
		input.SuppressBackgroundThread = false;
		Gdiplus::GdiplusStartup(&m_ptrGDIToken, &input, nullptr);
	}
}

GdiPlusManager::~GdiPlusManager()
{
	//If all the reference to the GdiPlusManager has been destroyed
	if (--m_nGDIManagerRefCount == 0) {
		//Uninitialize the gdiplus
		Gdiplus::GdiplusShutdown(m_ptrGDIToken);

	}
}
