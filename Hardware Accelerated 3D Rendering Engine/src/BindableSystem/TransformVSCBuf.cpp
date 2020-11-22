#include "TransformVSCBuf.h"

TransformVSCBuf::TransformVSCBuf(const Renderer* pRenderer, const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& rotation) 
	: 
	Bindable(pRenderer), 
	m_vsConstantBuf(pRenderer),
	m_mxmatProjectionMatrix(pRenderer->GetProjectionMatrix())
{}

void TransformVSCBuf::Bind() const {
	using namespace DirectX;
	XMMATRIX data = XMMatrixTranspose(
		XMMatrixRotationRollPitchYaw(m_f3Rotation.x, m_f3Rotation.y, m_f3Rotation.z) *
		XMMatrixTranslation(m_f3Position.x, m_f3Position.y, m_f3Position.z) *
		m_mxmatProjectionMatrix
	);
	//data = XMMatrixIdentity();
	memcpy(&(m_vsConstantBuf.GetBuffer()), &data, sizeof(data));
	//m_vsConstantBuf.GetBuffer() =
	//	XMMatrixTranspose(
	//		XMMatrixRotationRollPitchYaw(m_f3Rotation.x, m_f3Rotation.y, m_f3Rotation.z) *
	//		XMMatrixTranslation(m_f3Position.x, m_f3Position.y, m_f3Position.z) *
	//		m_matProjectionMatrix
	//	);
	m_vsConstantBuf.Update();
	m_vsConstantBuf.Bind();
}

void TransformVSCBuf::SetX(const float& x) { m_f3Position.x = x; }

void TransformVSCBuf::SetY(const float& y) { m_f3Position.y = y; }

void TransformVSCBuf::SetZ(const float& z) { m_f3Position.z = z; }

void TransformVSCBuf::SetPosition(const DirectX::XMFLOAT3& position) { m_f3Position = position; }

void TransformVSCBuf::SetPitch(const float& pitch) { m_f3Rotation.x = pitch; }

void TransformVSCBuf::SetYaw(const float& yaw) { m_f3Rotation.y = yaw; }

void TransformVSCBuf::SetRoll(const float& roll) { m_f3Rotation.z = roll; }

void TransformVSCBuf::SetRotation(const DirectX::XMFLOAT3& rotation) { m_f3Rotation = rotation; }
