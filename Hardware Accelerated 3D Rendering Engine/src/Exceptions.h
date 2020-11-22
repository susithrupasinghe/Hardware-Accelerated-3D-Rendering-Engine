#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

//Windows includes
#include "WindowsInclude.h"

//Standard Includes
#include <stdexcept>
#include <vector>
#include <string>


class GeneralException : public std::exception {
public:
	GeneralException(const char* file, int line) noexcept;
	GeneralException(const char* file, int line, std::string message) noexcept;
	virtual const char* what() const noexcept override;

protected:
	virtual const std::string GetType() const noexcept;
	virtual const std::string GetErrorString() const noexcept;

private:
	const std::string GetFile() const noexcept;
	const int GetLine() const noexcept;
	const std::string GetOriginString() const noexcept;

private:
	std::string file;
	std::string errorString = std::string();
	int line;

protected:
	mutable std::string whatBuffer;
};

class WinException : public GeneralException {
public:
	WinException(const char* file, int line, HRESULT hr, std::vector<std::string> infos = {}) noexcept;

protected:
	virtual const std::string GetType() const noexcept override;
	virtual const std::string GetErrorString() const noexcept override;

private:
	const HRESULT GetErrorCode() const noexcept;
	const std::string GetErrorInfo() const noexcept;
	const std::string TranslateErrorCode(HRESULT hr) const;

private:
	HRESULT hr;
	std::vector<std::string> errorInfos;
};

class InfoOnlyException : public GeneralException {
public:
	InfoOnlyException(const char* file, int line, std::vector<std::string> infos) noexcept;
	virtual const std::string GetErrorString() const noexcept override;
	virtual const std::string GetType() const noexcept override;
	const std::string GetInfo() const noexcept;
private:
	std::vector<std::string> infos;
};

#define EXCEPT_GENERAL() GeneralException(__FILE__, __LINE__)
#define EXCEPT_GENERAL_MSG(message) GeneralException(__FILE__, __LINE__, message)
#define EXCEPT_WIN(hr) WinException(__FILE__, __LINE__, hr)
#define EXCEPT_WIN_INFO(hr, info) WinException(__FILE__, __LINE__, hr, info)
#define EXCEPT_WIN_LAST_ERR() WinException(__FILE__, __LINE__, GetLastError())
#define EXCEPT_INFO_ONLY(info) InfoOnlyException(__FILE__,__LINE__,info)

#define THROW_EXCEPT_WIN(hrCall) if(FAILED(hr = (hrCall))) throw EXCEPT_WIN(hr);

#endif // !EXCEPTIONS_H