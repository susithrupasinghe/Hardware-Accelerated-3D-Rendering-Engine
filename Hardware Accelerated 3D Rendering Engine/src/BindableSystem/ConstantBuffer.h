#ifndef CONSTANTBUFFER_H
#define CONSTANTBUFFER_H

//Local includes
#include "Bindable.h"

template <typename T>
class ConstantBuffer : public Bindable {
public:
	ConstantBuffer(const Renderer* pRenderer, const T& pInitialData = {}) : Bindable(pRenderer) {
		D3D11_BUFFER_DESC constantBufferDesc = {
				/*UINT ByteWidth				 */ sizeof(m_data),
				/*D3D11_USAGE Usage				 */ D3D11_USAGE::D3D11_USAGE_DYNAMIC /*We are using dynamic mode because we will be writing this buffer from the cpu*/,
				/*UINT BindFlags				 */ D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER,
				/*UINT CPUAccessFlags			 */	D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE,
				/*UINT MiscFlags				 */ 0u,
				/*UINT StructureByteStride		 */ 0u,
		};

		
		memcpy(&m_data, &pInitialData, sizeof(T));
		
	
		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = (void*)&m_data;
		

		HRESULT hr;
		GFX_THROW_EXCEPT_FAILED(GetDevice()->CreateBuffer(&constantBufferDesc, &bufferData, &m_pConstantBuffer));
	}

	T& GetBuffer() {
		return m_data;
	}

	void Update() const {
		HRESULT hr;
		D3D11_MAPPED_SUBRESOURCE mappedResource = {};
		GFX_THROW_EXCEPT_FAILED(GetContext()->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
		memcpy(mappedResource.pData, &m_data, sizeof(m_data));
		GetContext()->Unmap(m_pConstantBuffer.Get(), 0);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;
	T m_data = {};
};

#endif // !CONSTANTBUFFER_H
