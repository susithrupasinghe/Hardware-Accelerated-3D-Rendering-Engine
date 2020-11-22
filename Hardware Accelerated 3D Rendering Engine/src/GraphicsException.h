#ifndef GRAPHICSEXCEPTION_H
#define GRAPHICSEXCEPTION_H

#include "WindowsInclude.h"

//Local Includes
#include "Exceptions.h"

class GFX_DeviceRemovedException : public WinException {
	using WinException::WinException;
private:
	const std::string GetType() const noexcept override;
};

#endif // !GRAPHICSEXCEPTION_H
