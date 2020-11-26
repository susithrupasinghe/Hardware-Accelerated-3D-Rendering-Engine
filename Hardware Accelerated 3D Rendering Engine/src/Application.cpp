#include "Application.h"

//DirectX Includes
#include <DirectXMath.h>

bool Application::OnStart() {
	using namespace DirectX;

	//Set the projection matrix of the renderer
	GetRenderer()->SetProjectionMatrix(XMMatrixPerspectiveFovLH(90.0f, (float)GetWidth() / (float)GetHeight(), 0.5f, 100.0f));

	//Create and Bind the viewports to the pipeline
	D3D11_VIEWPORT viewports[] = { {0.0f, 0.0f, (FLOAT)GetWidth(), (FLOAT)GetHeight(), 0.0f, 1.0f} };
	GetRenderer()->GetContext()->RSSetViewports((UINT)(sizeof(viewports) / sizeof(viewports[0])), viewports);

	//Create and Bind the backbuffer as the render target
	ID3D11RenderTargetView* renderTargets[] = { GetRenderer()->GetBackbufferTargetView() };
	GetRenderer()->GetContext()->OMSetRenderTargets((UINT)(sizeof(renderTargets) / sizeof(renderTargets[0])), renderTargets, GetRenderer()->GetDepthStencilView());

	m_drawables.insert({ "Skull", new Mesh(
		GetRenderer(),
		std::string("Models/Skull.obj"),
		std::wstring(L"Models/Skull.jpg"),
		XMFLOAT3(0.0f, 0.0f, 40.0f)
	) });

	m_drawables.insert(
		{ "Cube", 
		new Mesh(
		GetRenderer(),
		std::string("Models/Cube.obj"),
		std::wstring(L"Models/Cube.png"),
		XMFLOAT3(5.0f, 0.0f, 4.0f)
	) });

	return true;
}

bool Application::OnUpdate(float dt) {
	const float fRotatingSpeed = 1.0f;

	Mesh* pBox = reinterpret_cast<Mesh*>(m_drawables["Cube"]);
	Mesh* pSkull = reinterpret_cast<Mesh*>(m_drawables["Skull"]);

	pSkull->GetRotation().y += fRotatingSpeed * dt;

	pBox->GetRotation().x += fRotatingSpeed * dt;
	pBox->GetRotation().z += fRotatingSpeed * dt;


	for (const std::pair<std::string, Drawable*>& drawablePair : m_drawables)
		drawablePair.second->Draw();
	return true;
}

bool Application::OnDestroy()
{
	for (const std::pair<std::string, Drawable*>& drawablePair : m_drawables)
		if (drawablePair.second) delete drawablePair.second;
	return true;
}
