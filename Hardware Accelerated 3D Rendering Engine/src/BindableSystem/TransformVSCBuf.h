#ifndef TRANSFORMVSCBUF_H
#define TRANSFORMVSCBUF_H

//Local Includes
#include "Bindable.h"
#include "VSConstantBuffer.h"

//DirectX Includes
#include <DirectXMath.h>

class TransformVSCBuf : public Bindable {
public:
	TransformVSCBuf(const Renderer* pRenderer, const DirectX::XMFLOAT3& position = {}, const DirectX::XMFLOAT3& rotation = {});

	virtual void Bind() const override;

	void SetX(const float& x);
	void SetY(const float& y);

	void SetZ(const float& z);

	void SetPosition(const DirectX::XMFLOAT3& position);

	void SetPitch(const float& pitch);
	void SetYaw(const float& yaw);
	void SetRoll(const float& roll);
	void SetRotation(const DirectX::XMFLOAT3& rotation);

private:
	mutable VSConstantBuffer<DirectX::XMMATRIX> m_vsConstantBuf;
	DirectX::XMFLOAT3 m_f3Position = {};
	DirectX::XMFLOAT3 m_f3Rotation = {};
	DirectX::XMMATRIX m_mxmatProjectionMatrix = {};
};

#endif // !TRANSFORMVSCBUF_H
