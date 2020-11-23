#ifndef BOXWITHTEXTURE_H
#define BOXWITHTEXTURE_H

//Local Inicludes
#include "Drawable.h"

//DirectX Includes
#include <DirectXMath.h>

//Standard Includes
#include <cstdint>
#include <vector>

class BoxWithTexture : public Drawable {
private:
	struct Vertex {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 UVCoord;
	};
public:
	BoxWithTexture(const Renderer* pRenderer);
	const void SetPosition(const DirectX::XMFLOAT3& Position);
	const void SetRotation(const DirectX::XMFLOAT3& Rotation);
	constexpr DirectX::XMFLOAT3& GetRotation() { return m_Rotation; }
	constexpr DirectX::XMFLOAT3& GetPosition() { return m_Position; }
	virtual const DirectX::XMMATRIX GetTransform() const override;

private:
	std::vector<Vertex> m_vecVertices = {

		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.25f, 0.33f) },
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.33f) },
		{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.66f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.25f, 0.66f) },

		
		{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.25f, 0.99f) },
		{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.5f, 0.99f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.5f, 0.66f) },

		{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.75f, 0.66f) },
		{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.66f) },

		{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.33f) },
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.75f, 0.33f) },

		{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.5f, 0.33f) },
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.5f, 0.0f) },
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.25f, 0.0f) },
	};

	std::vector<uint16_t> m_vecIndices = {
		//FRONT FACE
		0,1,2,
		0,2,3,

		//RIGHT FACE
		3,4,5,
		3,5,6,

		//BACK FACE
		6,7,10,
		6,10,11,

		//LEFT FACE
		11,12,13,
		11,13,0,

		//UP FACE
		9,10,7,
		9,7,8,

		//DOWN FACE
		11,0,3,
		11,3,6,
	};

	DirectX::XMFLOAT3 m_Position = DirectX::XMFLOAT3(0.0f, 0.0f, 4.0f);
	DirectX::XMFLOAT3 m_Rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
};

#endif // !BOXWITHTEXTURE_H
