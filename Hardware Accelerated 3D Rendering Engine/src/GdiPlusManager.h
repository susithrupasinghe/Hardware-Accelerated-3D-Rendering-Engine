#ifndef GDIPLUSMANAGER_H
#define GDIPLUSMANAGER_H

//Windows Includes
#include "WindowsInclude.h"

//Standard includes
#include <algorithm>
#include <cstdint>

//Becuase we undefined the min max macros in Windows.h We need to inject min max functions from C++ std library
//to Gdiplus namespace before including Gdiplus.h. Becuase gdi+ uses min max macros a lot

namespace Gdiplus {
	using std::min;
	using std::max;
}

//Include GDI+
#include <gdiplus.h>

class GdiPlusManager {
public:
	GdiPlusManager();
	~GdiPlusManager();

private:
	static ULONG_PTR m_ptrGDIToken;
	static uint32_t m_nGDIManagerRefCount;
};

#endif // !GDIPLUSMANAGER_H
