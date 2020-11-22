#ifndef APPLICATION_H
#define APPLICATION_H

//Local Includes
#include "EngineBase.h"

//Standard Includes
#include <vector>
#include <cstdint>

class Application : public EngineBase {
private:
	Application();

public:
	static Application& GetSingleton();

private:
	struct Vector3 {
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	struct Vertex {
		Vector3 Position;
	};

private:
	bool OnStart() override;
	bool OnUpdate(float dt) override;

private:

	//Vertices of the box
	std::vector<Vertex> boxVertices = {
		{-0.5f, -0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
		{-0.5f, -0.5f,  0.5f},
	};
	
	//Indices of the box
	std::vector<uint16_t> boxIndices = {
		0,1,2,
		0,2,3,

		3,2,5,
		3,5,4,

		4,5,6,
		4,6,7,

		7,6,1,
		7,1,0,

		1,6,5,
		1,5,2,

		7,0,3,
		7,3,4,
	};


	float fBoxX = 0.0f;
	float fBoxY = 0.0f;
	float fBoxZ = 0.0f;
	float fBoxRoll = 0.0f;
	float fBoxPitch = 0.0f;
	float fBoxYaw = 0.0f;

	Microsoft::WRL::ComPtr<ID3D11Buffer> pBoxVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBoxIndexBuffer;
	Microsoft::WRL::ComPtr<ID3DBlob> pShaderBlob;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBoxVertexShaderConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pBoxVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBoxPixelShaderConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pBoxPixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pBoxInputLayout;

	//Singleton
	static Application singleton;
};

#endif // !APPLICATION_H