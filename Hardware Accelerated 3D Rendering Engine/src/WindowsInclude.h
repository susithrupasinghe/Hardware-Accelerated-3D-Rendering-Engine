#ifndef WINDOWSINCLUDE_H
#define WINDOWSINCLUDE_H

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

#define NOMINMAX
#include <Windows.h>

#endif // !WINDOWSINCLUDE_H