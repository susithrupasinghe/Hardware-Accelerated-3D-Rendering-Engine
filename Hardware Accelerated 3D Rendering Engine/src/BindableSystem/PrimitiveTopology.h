#ifndef PRIMITIVETOPOLOGY_H
#define PRIMITIVETOPOLOGY_H

//Local Includes
#include "Bindable.h"

class PrimitiveTopology : public Bindable {
public:
	PrimitiveTopology(const Renderer* pRenderer, const D3D11_PRIMITIVE_TOPOLOGY& topology);

	virtual void Bind() const override;

	void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology);

private:
	D3D11_PRIMITIVE_TOPOLOGY m_topology;
};

#endif // !PRIMITIVETOPOLOGY_H
