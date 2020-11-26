#ifndef MESH_H
#define MESH_H

//Local Includes
#include "Drawable.h"

//DirectX Includes
#include <DirectXMath.h>


class Mesh : public Drawable {
private:
	struct Vertex {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};
public:
	Mesh(const Renderer* pRenderer, const std::string& objfile, 
		const std::wstring& texture, 
		const DirectX::XMFLOAT3& position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		const DirectX::XMFLOAT3& rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)
		);

	const void SetPosition(const DirectX::XMFLOAT3& Position);
	const void SetRotation(const DirectX::XMFLOAT3& Rotation);
	constexpr DirectX::XMFLOAT3& GetRotation() { return m_rotation; }
	constexpr DirectX::XMFLOAT3& GetPosition() { return m_position; }
	virtual const DirectX::XMMATRIX GetTransform() const override;

private:
	DirectX::XMFLOAT3 m_position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
};

#endif // !MESH_H