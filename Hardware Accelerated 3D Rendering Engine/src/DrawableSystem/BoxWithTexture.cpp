#include "BoxWithTexture.h"

BoxWithTexture::BoxWithTexture(const Renderer* pRenderer) : Drawable(pRenderer)
{
	//Create the vertex buffer
 	AddBindable(new VertexBuffer(GetRenderer(), (UINT)m_vecVertices.size(), (UINT)sizeof(m_vecVertices[0]), m_vecVertices.data()));

	//Create the Index buffer
	AddIndexBufferBindable(new IndexBuffer(GetRenderer(), (UINT)m_vecIndices.size(), (UINT)sizeof(m_vecIndices[0]), DXGI_FORMAT::DXGI_FORMAT_R16_UINT, m_vecIndices.data()));

	//Create the vertex shader
	VertexShader* pVertexShader = new VertexShader(GetRenderer(), std::wstring(L"Shaders/VSBoxTex.cso"));

	AddBindable(pVertexShader);

	//Create the Pixel Shader
	AddBindable(new PixelShader(GetRenderer(), std::wstring(L"Shaders/PSBoxTex.cso")));

	//Create the Input Layout

	std::vector<D3D11_INPUT_ELEMENT_DESC> vecBoxWithTexInputElementDescs = { 
		{ "POSITION", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u }, 
		{ "TEXCOORD", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0u, (UINT)sizeof(Vertex::position), D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
	};

	AddBindable(new InputLayout(GetRenderer(), vecBoxWithTexInputElementDescs, *pVertexShader));

	//Set Promitive topology
	AddBindable(new PrimitiveTopology(GetRenderer(), D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	//Create a constant buffer for the vertex shader (in this case it's a Transform Constant buffer)
	AddBindable(new TransformVSCBuf(GetRenderer(), this));

	//Create a Texture and a sampler state
	AddBindable(new Texture2D(GetRenderer(), TextureImage(std::wstring(L"Textures/BoxTex.png"))));

	AddBindable(new Sampler(GetRenderer()));
}

const void BoxWithTexture::SetPosition(const DirectX::XMFLOAT3& Position)
{
	m_Position = Position;
}

const void BoxWithTexture::SetRotation(const DirectX::XMFLOAT3& Rotation)
{
	m_Rotation = Rotation;
}

const DirectX::XMMATRIX BoxWithTexture::GetTransform() const {
	using namespace DirectX;
	return XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z) * XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
}
