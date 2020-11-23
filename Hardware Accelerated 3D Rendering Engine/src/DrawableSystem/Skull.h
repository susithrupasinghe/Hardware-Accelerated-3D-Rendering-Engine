#ifndef SKULL_H
#define SKULL_H

//Local Includes
#include "Drawable.h"

//Standard Includes
#include <cstdint>
#include <string>

class Skull : public Drawable {
public:
	Skull(const Renderer* pRenderer);
	const void SetPosition(const DirectX::XMFLOAT3& Position);
	const void SetRotation(const DirectX::XMFLOAT3& Rotation);
	constexpr DirectX::XMFLOAT3& GetRotation() { return m_Rotation; }
	constexpr DirectX::XMFLOAT3& GetPosition() { return m_Position; }
	virtual const DirectX::XMMATRIX GetTransform() const override;
private:
	std::pair<std::vector<DirectX::XMFLOAT3>, std::vector<uint16_t>> LoadFromFile(std::string filename);

private:
	DirectX::XMFLOAT3 m_Position = DirectX::XMFLOAT3(0.0f, 0.0f, 60.0f);
	DirectX::XMFLOAT3 m_Rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
};

#endif // !SKULL_H
