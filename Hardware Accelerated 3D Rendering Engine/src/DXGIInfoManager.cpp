
#if defined (DEBUG) || defined (_DEBUG)
//Local Includes
#include "DXGIInfoManager.h"
#include "Exceptions.h"

//Standard Includes
#include <memory>

//Link DXGIInfoManager object file with dxguid.lib library
#pragma comment(lib,"dxguid.lib")

DXGIInfoManager DXGIInfoManager::instance;

DXGIInfoManager::DXGIInfoManager()
{
	// define function signature of DXGIGetDebugInterface
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void **);

	// load the dll that contains the function DXGIGetDebugInterface
	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr)
	{
		throw EXCEPT_WIN_LAST_ERR();
	}

	// get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		);
	if (DxgiGetDebugInterface == nullptr)
	{
		throw EXCEPT_WIN_LAST_ERR();
	}

	HRESULT hr;
	THROW_EXCEPT_WIN(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue));
}

void DXGIInfoManager::Set() noexcept
{
	next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DXGIInfoManager::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = next; i < end; i++)
	{
		HRESULT hr;
		SIZE_T messageLength = 0;
		// get the size of message i in bytes
		THROW_EXCEPT_WIN(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
		// allocate memory for message
		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		// get the message and push its description into the vector
		THROW_EXCEPT_WIN(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}
DXGIInfoManager& DXGIInfoManager::GetInstance()
{
	return instance;
}

DXGIInfoManager& g_DXGIInfoManager = DXGIInfoManager::GetInstance();
#endif