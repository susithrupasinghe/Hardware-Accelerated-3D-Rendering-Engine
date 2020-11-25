#include "Mesh.h"

//Local Includes
#include "../../ThirdParty/WaveFrontReader.h"

//Standard Includes
#include <cstdint>

Mesh::Mesh(
	const Renderer* pRenderer, 
	const std::wstring& objfile, 
	const std::wstring& texture, 
	const DirectX::XMFLOAT3& position, 
	const DirectX::XMFLOAT3& rotation
) 
	: 
	Drawable(pRenderer), 
	m_position(position), 
	m_rotation(rotation)
{
	//First load the mesh
	WaveFrontReader<uint16_t> reader;
	reader.Load(objfile.c_str());

	const std::vector<WaveFrontReader<uint16_t>::Vertex>& Vertices = reader.vertices;
	const std::vector<uint16_t>& Indices = reader.indices;

	//Create a vertex buffer
	AddBindable(new VertexBuffer(GetRenderer(), (UINT)Vertices.size(), (UINT)sizeof(Vertices[0]), Vertices.data()));

	//Create a index buffer
	AddIndexBufferBindable(new IndexBuffer(GetRenderer(), (UINT)Indices.size(), (UINT)sizeof(Indices[0]), DXGI_FORMAT_R16_UINT, Indices.data()));

	//Create a vertex shader
	const VertexShader* pVertexShader = new VertexShader(GetRenderer(), std::wstring(L"Shaders/MeshVS.cso"));
	AddBindable(pVertexShader);

	//Create a pixel shader
	AddBindable(new PixelShader(GetRenderer(), std::wstring(L"Shaders/MeshPS.cso")));

	//Create an input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements = {
		{ "POSITION", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ "NORMAL", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, (UINT)sizeof(WaveFrontReader<uint16_t>::Vertex::position), D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ "TEXCOORD", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0u, (UINT)(sizeof(WaveFrontReader<uint16_t>::Vertex::position) + sizeof(WaveFrontReader<uint16_t>::Vertex::normal)), D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
	};

	AddBindable(new InputLayout(GetRenderer(), inputElements, *pVertexShader));

	//Create a primitive topology
	AddBindable(new PrimitiveTopology(GetRenderer(), D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	//Create a TransformVSCbuf
	AddBindable(new TransformVSCBuf(GetRenderer(), this));

	//Create a Texture and a sampler state
	AddBindable(new Texture2D(GetRenderer(), TextureImage(texture)));

	//Create a sampler
	AddBindable(new Sampler(GetRenderer()));

}

const void Mesh::SetPosition(const DirectX::XMFLOAT3& Position)
{
	m_position = Position;
}

const void Mesh::SetRotation(const DirectX::XMFLOAT3& Rotation)
{
	m_rotation = Rotation;
}

const DirectX::XMMATRIX Mesh::GetTransform() const
{
	using namespace DirectX;
	return XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z) * XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
}
