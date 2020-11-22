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
public:
	Box(const Renderer* pRenderer);

private:
	//const std::vector<Vertex> m_vecVertices = {
	//	{DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f)},
	//	{DirectX::XMFLOAT3( 1.0f, -1.0f, -1.0f)},
	//	{DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f)},
	//	{DirectX::XMFLOAT3( 1.0f,  1.0f, -1.0f)},
	//	{DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f)},
	//	{DirectX::XMFLOAT3( 1.0f, -1.0f,  1.0f)},
	//	{DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f)},
	//	{DirectX::XMFLOAT3( 1.0f,  1.0f,  1.0f)},
	//};

	//const std::vector<uint16_t> m_vecIndices = {
	//	0,2,1, 2,3,1,
	//	1,3,5, 3,7,5,
	//	2,6,3, 3,6,7,
	//	4,5,7, 4,7,6,
	//	0,4,2, 2,4,6,
	//	0,1,4, 1,5,4,
	//};


	std::vector<Vertex> m_vecVertices = {
	{DirectX::XMFLOAT3(-0.75f, -0.75f, 0.0f)},
	{DirectX::XMFLOAT3(0.0f, 0.75f, 0.0f)},
	{DirectX::XMFLOAT3(0.75f, -0.75f, 0.0f)},
	{DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f)},
	};

	std::vector<uint16_t> m_vecIndices = {
		0, 1, 2,
		0, 3, 1,
	};

	const TransformVSCBuf* vcBuf = nullptr;
};

#endif // !BOX_H
