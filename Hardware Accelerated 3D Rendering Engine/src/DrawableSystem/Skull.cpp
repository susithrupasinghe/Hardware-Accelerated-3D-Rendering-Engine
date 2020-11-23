#include "Skull.h"

#include <fstream>
#include <iterator>
#include <sstream>

Skull::Skull(const Renderer* pRenderer) : Drawable(pRenderer)
{
	const auto VerticesAndIndices = LoadFromFile("Models/Skull.obj");
	const auto& Vertices = VerticesAndIndices.first;
	const auto& Indices = VerticesAndIndices.second;

	//Create a vertex buffer for the model
	AddBindable(new VertexBuffer(GetRenderer(), (UINT)Vertices.size(), (UINT)sizeof(Vertices[0]), Vertices.data()));

	//Create an Index buffer
	AddIndexBufferBindable(new IndexBuffer(GetRenderer(), (UINT)Indices.size(), (UINT)sizeof(Indices[0]), DXGI_FORMAT_R16_UINT, Indices.data()));

	//Create a vertex shader
	const VertexShader* pVertexShader = new VertexShader(GetRenderer(), std::wstring(L"Shaders/VertexShaderBox.cso"));
	AddBindable(pVertexShader);

	//Create a pixel shader
	AddBindable(new PixelShader(GetRenderer(), std::wstring(L"Shaders/BoxPixelShader.cso")));

	//Create a input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayouts = { { "POSITION", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u }, };
	AddBindable(new InputLayout(GetRenderer(), InputLayouts, *pVertexShader));

	//Create a primitive topology
	AddBindable(new PrimitiveTopology(GetRenderer(), D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	//Create a TransformVSCbuf
	AddBindable(new TransformVSCBuf(GetRenderer(), this));
	
}	

const void Skull::SetPosition(const DirectX::XMFLOAT3& Position)
{
	m_Position = Position;
}

const void Skull::SetRotation(const DirectX::XMFLOAT3& Rotation)
{
	m_Rotation = Rotation;
}

const DirectX::XMMATRIX Skull::GetTransform() const {
	using namespace DirectX;
	return XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z) * XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
}


std::pair<std::vector<DirectX::XMFLOAT3>, std::vector<uint16_t>> Skull::LoadFromFile(std::string filename)
{
	std::pair<
		std::vector<DirectX::XMFLOAT3>,
		std::vector<uint16_t>
	> output = {};

	//Load the file
	std::ifstream file(filename);
	if (!file.is_open()) {
		return output;
	}


	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::vector<std::string> words(std::istream_iterator<std::string>{iss},
			std::istream_iterator<std::string>());
		if (words[0] == "v") {
			output.first.emplace_back(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
		}
		if (words[0] == "f") {
			output.second.push_back(std::stoi(words[1]) - 1);
			output.second.push_back(std::stoi(words[2]) - 1);
			output.second.push_back(std::stoi(words[3]) - 1);
		}

	}

	return output;
}
