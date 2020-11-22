#ifndef MESH_H
#define MESH_H

//Local Includes
#include "Drawable.h"

//DirectX Includes
#include <DirectXMath.h>

//Standard library

struct Vertex {
	DirectX::XMFLOAT3 Position;
};


class Mesh : public Drawable {
public:
	Mesh(const Renderer* pRenderer) : Drawable(pRenderer) {
		
	}

private:
	std::vector<Vertex> m_vecVertices;
	std::vector<unsigned short> m_vecIndices;
};

#endif // !MESH_H