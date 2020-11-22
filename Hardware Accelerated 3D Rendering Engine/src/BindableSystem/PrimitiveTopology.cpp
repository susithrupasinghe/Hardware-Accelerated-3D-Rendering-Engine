#include "PrimitiveTopology.h"

PrimitiveTopology::PrimitiveTopology(const Renderer* pRenderer, const D3D11_PRIMITIVE_TOPOLOGY& topology) : Bindable(pRenderer), m_topology(topology) {}

void PrimitiveTopology::Bind() const {
	GetContext()->IASetPrimitiveTopology(m_topology);
}

void PrimitiveTopology::SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) { m_topology = topology; }
