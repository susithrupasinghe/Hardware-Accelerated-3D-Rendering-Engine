#ifndef PSCONSTANTBUFFER_H
#define PSCONSTANTBUFFER_H

//Local Includes
#include "ConstantBuffer.h"

template<typename T>
class PSConstantBuffer : public ConstantBuffer<T> {
public:
	//Using the Constructer of the ConstantBuffer<T> class
	using ConstantBuffer<T>::ConstantBuffer;
	using ConstantBuffer<T>::Update;
	using ConstantBuffer<T>::GetBuffer;

	virtual void Bind() const override {
		GetContext()->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	}

private:
	using Bindable::GetContext;
	using ConstantBuffer<T>::m_pConstantBuffer;
};

#endif // !PSCONSTANTBUFFER_H
