#include "Exceptions.h"
#include <sstream>

#pragma region GeneralException

GeneralException::GeneralException(const char * file, int line) noexcept : file(file), line(line) {}

GeneralException::GeneralException(const char * file, int line, std::string message) noexcept : file(file), line(line), errorString(message)
{
}

const char * GeneralException::what() const noexcept {
	std::ostringstream oss;
	oss << GetOriginString() << std::endl
		<< GetErrorString() << std::endl;
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const std::string GeneralException::GetType() const noexcept {
	return "Rendering_Engine General Exception";
}

const std::string GeneralException::GetFile() const noexcept {
	return file;
}

const int GeneralException::GetLine() const noexcept {
	return line;
}

const std::string GeneralException::GetOriginString() const noexcept {
	std::ostringstream oss;
	oss
		<< std::endl
		<< "[TYPE] : " << GetType() << std::endl
		<< std::endl
		<< "[FILE] : " << GetFile() << std::endl
		<< "[LINE] : " << GetLine() << std::endl;
	return oss.str();
}

const std::string GeneralException::GetErrorString() const noexcept {
	return errorString;
}

#pragma endregion

#pragma region WinException

WinException::WinException(const char * file, int line, HRESULT hr, std::vector<std::string> infos) noexcept : GeneralException(file, line), hr(hr), errorInfos(infos) {}

const std::string WinException::GetType() const noexcept {
	return "Windows HRESULT Exception";
}

const std::string WinException::GetErrorString() const noexcept {
	std::ostringstream oss;
	oss << "[ERROR_CODE] : " << "0x" << std::hex << GetErrorCode() << std::endl
		<< "[ERROR] : " << TranslateErrorCode(hr);
	std::string errInfo = GetErrorInfo();
	if (!errInfo.empty()) {
		oss << std::endl
			<< std::endl
			<< "[ERROR_INFO]" << std::endl
			<< errInfo
			<< "[ERROR_INFO_END]" << std::endl
			<< std::endl;

	}
	return oss.str();
}

const HRESULT WinException::GetErrorCode() const noexcept {
	return hr;
}

const std::string WinException::GetErrorInfo() const noexcept {
	std::string errInfo;

	if (!errorInfos.empty()) {
		int i = 1;
		errInfo += "\n";
		for (const auto& s : errorInfos) {
			errInfo += "[" + std::to_string(i) + "] " + s + "\n" + "\n";
			i++;
		}
		//errInfo += "\n";

	}
	return errInfo;
}

const std::string WinException::TranslateErrorCode(HRESULT hr) const {
	char* pMsgBuffer = nullptr;
	DWORD nMsgLength = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&pMsgBuffer), 0, nullptr);
	if (nMsgLength == 0) {
		return "Unidentified error code.";
	}

	std::string errorString = pMsgBuffer;
	LocalFree(pMsgBuffer);
	return errorString;
}

#pragma endregion

#pragma region InfoOnlyException

InfoOnlyException::InfoOnlyException(const char * file, int line, std::vector<std::string> infos) noexcept : GeneralException(file, line), infos(infos) {}

const std::string InfoOnlyException::GetErrorString() const noexcept {
	std::ostringstream oss;
	oss << "[INFO_ONLY_EXCEPTION]" << std::endl
		<< std::endl
		<< "[INFO_BEGIN]" << std::endl
		<< GetInfo() << std::endl
		<< "[INFO_END]" << std::endl;
	return oss.str();
}

const std::string InfoOnlyException::GetType() const noexcept {
	return "Debug Info Only Exception";
}

const std::string InfoOnlyException::GetInfo() const noexcept {
	std::string s;
	std::ostringstream oss;
	int i = 1;
	oss << std::endl;
	for (const auto& info : infos) {
		oss << "[" << i << "] : " << info << std::endl << std::endl;
		i++;
	}
	oss << std::endl;
	s = oss.str();
	return s;
}

#pragma endregion
