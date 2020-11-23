#include "Box.h"



Box::Box(const Renderer* pRenderer) : Drawable(pRenderer) {
	AddBindable(new VertexBuffer(GetRenderer(), (UINT)m_vecVertices.size(), (UINT)sizeof(m_vecVertices[0]), m_vecVertices.data()));
	AddIndexBufferBindable(new IndexBuffer(GetRenderer(), (UINT)m_vecIndices.size(), (UINT)sizeof(m_vecIndices[0]), DXGI_FORMAT::DXGI_FORMAT_R16_UINT, m_vecIndices.data()));
	VertexShader* pVertexShader = new VertexShader(GetRenderer(), std::wstring(L"Shaders/VertexShaderBox.cso"));
	AddBindable(pVertexShader);
	AddBindable(new PixelShader(GetRenderer(), std::wstring(L"Shaders/PixelShaderBox.cso")));
	std::vector<D3D11_INPUT_ELEMENT_DESC> BoxInputLayouts = { { "POSITION", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u }, };
	AddBindable(new InputLayout(GetRenderer(), BoxInputLayouts, *pVertexShader));
	AddBindable(new PrimitiveTopology(GetRenderer(), D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	AddBindable(new TransformVSCBuf(GetRenderer(), this));

	AddBindable(new PSConstantBuffer<PSConstBuf>(GetRenderer(), m_colors));

}

const void Box::SetPosition(const DirectX::XMFLOAT3& Position)
{
	m_Position = Position;
}

const void Box::SetRotation(const DirectX::XMFLOAT3& Rotation)
{
	m_Rotation = Rotation;
}

const DirectX::XMMATRIX Box::GetTransform() const {
	using namespace DirectX;
	return XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z)* XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
}
