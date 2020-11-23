#ifndef BOX_H
#define BOX_H

//Local Includes
#include "Drawable.h"

//DirectX Includes
#include <DirectXMath.h>

//Standard Includes
#include <vector>
#include <cstdint>

struct Vertex {
	DirectX::XMFLOAT3 Position;
};

class Box : public Drawable {
	struct PSConstBuf {
		DirectX::XMFLOAT4 colors[6];
	};

public:
	Box(const Renderer* pRenderer);
	const void SetPosition(const DirectX::XMFLOAT3& Position);
	const void SetRotation(const DirectX::XMFLOAT3& Rotation);
	constexpr DirectX::XMFLOAT3& GetRotation() { return m_Rotation; }
	constexpr DirectX::XMFLOAT3& GetPosition() { return m_Position; }
	virtual const DirectX::XMMATRIX GetTransform() const override;

private:
	const std::vector<Vertex> m_vecVertices = {
		{DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f)},
		{DirectX::XMFLOAT3( 1.0f, -1.0f, -1.0f)},
		{DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f)},
		{DirectX::XMFLOAT3( 1.0f,  1.0f, -1.0f)},
		{DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f)},
		{DirectX::XMFLOAT3( 1.0f, -1.0f,  1.0f)},
		{DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f)},
		{DirectX::XMFLOAT3( 1.0f,  1.0f,  1.0f)},
	};

	const std::vector<uint16_t> m_vecIndices = {
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4,
	};

	const PSConstBuf m_colors = { 
		{
		DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),
		}
	};

	DirectX::XMFLOAT3 m_Position = DirectX::XMFLOAT3(0.0f, 0.0f, 4.0f);
	DirectX::XMFLOAT3 m_Rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	
};

#endif // !BOX_H
