#ifndef VSCONSTANTBUFFER_H
#define VSCONSTANTBUFFER_H

//Local Includes
#include "ConstantBuffer.h"


template<typename T>
class VSConstantBuffer : public ConstantBuffer<T> {
private:
	using Bindable::GetContext;
	using ConstantBuffer<T>::m_pConstantBuffer;
public:
	//Using the Constructer of the ConstantBuffer<T> class
	using ConstantBuffer<T>::ConstantBuffer;
	using ConstantBuffer<T>::Update;
	using ConstantBuffer<T>::GetBuffer;

	virtual void Bind() const override {
		GetContext()->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	}

};

#endif // !VSCONSTANTBUFFER_H;
