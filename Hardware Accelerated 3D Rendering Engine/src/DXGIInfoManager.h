#ifndef DXGIINFOMANAGER_H
#define DXGIINFOMANAGER_H

/*
This code is copied from ChiliTommatoNoodle's Direct X Series
which you can find here https://www.youtube.com/watch?v=HKMLUL3dMM0&list=PLqCJpWy5Fohd3S7ICFXwUomYW0Wv67pDD&index=16&t=271s
*/

#if defined(DEBUG) || defined(_DEBUG)

//Windows Includes
#include "WindowsInclude.h"
#include <dxgidebug.h>
#include <wrl.h>

//Standard Includes
#include <vector>
#include <string>


class DXGIInfoManager
{
public:
	DXGIInfoManager();
	~DXGIInfoManager() = default;
	DXGIInfoManager(const DXGIInfoManager&) = delete;
	DXGIInfoManager& operator=(const DXGIInfoManager&) = delete;
	void Set() noexcept;
	std::vector<std::string> GetMessages() const;
	static DXGIInfoManager& GetInstance();
private:
	unsigned long long next = 0;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
	static DXGIInfoManager instance;
};

extern DXGIInfoManager& g_DXGIInfoManager;

#endif

#endif // !DXGIINFOMANAGER_H
