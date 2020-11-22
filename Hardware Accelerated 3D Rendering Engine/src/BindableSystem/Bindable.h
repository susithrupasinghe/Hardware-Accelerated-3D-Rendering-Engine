#ifndef BINDABLE_H
#define BINDABLE_H

//Window Includes
#include "../WindowsInclude.h"

//Direct3D Includes
#include "../D3DIncludes.h"

//Local Includes
#include "../Renderer.h"

//Bindable is a pure abstract class.
class Bindable {
public:
	Bindable( const Renderer* pRenderer );

public:
	//Bind() is a pure function. 
	virtual void Bind() const = 0;



protected:
	//Get a pointer to ID3D11Device interface that interfere with Direct3D Device object
	ID3D11Device* GetDevice() const;

	//Get a pointer to ID3D11DeviceContext interface that interfere with Direct3D Device Context object
	ID3D11DeviceContext* GetContext() const;

	//Get a pointer to IDXGISwapChain interface that interfere with DXGI Swap Chain object
	IDXGISwapChain* GetSwap() const;

private:
	//A pointer to a const Renderer object
	const Renderer* m_ptrRenderer = nullptr;
};

#endif // !BINDABLE_H
