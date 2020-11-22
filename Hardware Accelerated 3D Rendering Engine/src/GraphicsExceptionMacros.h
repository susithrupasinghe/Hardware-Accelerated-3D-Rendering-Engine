#ifndef GRAPHICSEXCEPTIONMACROS_H
#define GRAPHICSEXCEPTIONMACROS_H

//Local Includes
#include "Exceptions.h"
#include "GraphicsException.h"

//Standard Includes
#include <vector>
#include <String>

//Define some graphics exceptoins
#if defined (DEBUG) || defined (_DEBUG)

//IMPORTANT : And also before using this macro in debug mode you must get a refference to the DXGIInfoManager singleton to a variable called "g_DXGIInfoManager"
#define GFX_EXCEPT_WIN(hr) EXCEPT_WIN_INFO(hr, g_DXGIInfoManager.GetMessages())

//IMPORTANT : And also before using this macro in debug mode you must get a refference to the DXGIInfoManager singleton to a variable called "g_DXGIInfoManager"
#define GFX_EXCEPT_DEVICE_REMOVED(hr) GFX_DeviceRemovedException(__FILE__ , __LINE__ , hr, g_DXGIInfoManager.GetMessages())

//
//IMPORTANT : Before you using this GFX_THROW_EXCEPT_FAILED() macro you MUST declare a HRESULT variable with 'hr' identifier. Otherwise this won't work.
//            And you should declare only one 'HRESULT hr' for a single code block (Scope)
//IMPORTANT : And also before using this macro in debug mode you must get a refference to the DXGIInfoManager singleton to a variable called "g_DXGIInfoManager"
#define GFX_THROW_EXCEPT_FAILED(hrCall) g_DXGIInfoManager.Set(); if(FAILED(hr = (hrCall))) throw GFX_EXCEPT_WIN(hr)

//
//IMPORTANT : And also before using this macro in debug mode you must get a refference to the DXGIInfoManager singleton to a variable called "g_DXGIInfoManager"
#define GFX_THROW_EXCEPT_INFO_ONLY(hrCall) g_DXGIInfoManager.Set(); (hrCall); std::vector<std::string> infos = g_DXGIInfoManager.GetMessages(); if (!infos.empty()) throw EXCEPT_INFO_ONLY(infos)


#else

#define GFX_EXCEPT_WIN(hr) EXCEPT_WIN(hr)

#define GFX_EXCEPT_DEVICE_REMOVED(hr) GFX_DeviceRemovedException(__FILE__ , __LINE__ , hr)

//
//IMPORTANT : Before you using this GFX_THROW_EXCEPT_FAILED() macro you MUST declare a HRESULT variable with 'hr' identifier. Otherwise this won't work.
//            And you should declare only one 'HRESULT hr' for a single code block (Scope)
#define GFX_THROW_EXCEPT_FAILED(hrCall) if(FAILED(hr = (hrCall))) throw GFX_EXCEPT_WIN(hr)

#define GFX_THROW_EXCEPT_INFO_ONLY(hrCall)  (hrCall)

#endif

#endif // !GRAPHICSEXCEPTIONMACROS_H
