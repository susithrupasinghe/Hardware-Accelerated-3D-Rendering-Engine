#include "Mesh.h"

//Local Includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Standard Includes
#include <cstdint>

#pragma comment(lib, "assimp-vc142-mt.lib")

Mesh::Mesh(
	const Renderer* pRenderer, 
	const std::string& objfile, 
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
	
	Assimp::Importer im;
	const auto pScene = im.ReadFile(objfile, aiPostProcessSteps::aiProcess_Triangulate | aiPostProcessSteps::aiProcess_JoinIdenticalVertices | aiPostProcessSteps::aiProcess_FlipUVs);

	const auto pMesh = pScene->mMeshes[0];

	//pMesh->

	std::vector<Vertex> Vertices (pMesh->mNumVertices);

	for (size_t i = 0; i < pMesh->mNumVertices; i++) {
		const auto& vertex = pMesh->mVertices[i];
		const auto& normal = pMesh->mNormals[i];
		const auto& uv = pMesh->mTextureCoords[0][i];
		Vertices[i].position = DirectX::XMFLOAT3(vertex.x, vertex.y, vertex.z);
		if(pMesh->HasNormals()) Vertices[i].normal = DirectX::XMFLOAT3(normal.x, normal.y, normal.z);
		if(pMesh->HasTextureCoords(0)) Vertices[i].uv = { uv.x,  uv.y };
	}

	std::vector<uint16_t> Indices ((uint64_t)(pMesh->mNumFaces) * 3);
	for (size_t i = 0; i < pMesh->mNumFaces; i++) {
		const auto& pFace = pMesh->mFaces[i];
		if (pFace.mNumIndices != 3) throw EXCEPT_GENERAL_MSG(std::string("Loading failed faces are not triangulated!\n Loading mesh : ") + objfile);
		Indices[i * 3] = pFace.mIndices[0];
		Indices[i * 3 + 1] = pFace.mIndices[1];
		Indices[i * 3 + 2] = pFace.mIndices[2];
	}

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
		{ "NORMAL", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, (UINT)sizeof(Vertex::position), D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ "TEXCOORD", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0u, (UINT)(sizeof(Vertex::position) + sizeof(Vertex::normal)), D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
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
