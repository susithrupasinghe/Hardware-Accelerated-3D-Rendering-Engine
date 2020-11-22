#ifndef TRIANGLE_H
#define TRIANGLE_H

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

class Triangle : public Drawable {
public:
	Triangle(const Renderer* pRenderer);

private:
	
	//{ { -0.75f, -0.75f, 0.0f }, { 0.0f, 0.75f, 0.0f }, { 0.75f, -0.75f, 0.0f } };
	std::vector<Vertex> m_vecVertices = {
		{DirectX::XMFLOAT3(-0.75f, -0.75f, 0.0f)},
		{DirectX::XMFLOAT3(  0.0f, 0.75f, 0.0f)},
		{DirectX::XMFLOAT3( 0.75f, -0.75f, 0.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f)},
	};

	std::vector<uint16_t> m_vecIndices = {
		0, 1, 2,
		0, 3, 1,
	};
};

#endif // !TRIANGLE_H
