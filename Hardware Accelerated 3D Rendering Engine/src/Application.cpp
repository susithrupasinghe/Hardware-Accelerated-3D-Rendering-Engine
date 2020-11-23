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

	

	//Create a box
	pBox = new Box(GetRenderer());

	pBox2 = new Box(GetRenderer());

	pBoxTex = new BoxWithTexture(GetRenderer());

	pSkull = new Skull(GetRenderer());
	pSkull->GetPosition().z = 40.0f;

	return true;
}

bool Application::OnUpdate(float dt) {
	

	const float fMovingSpeed = 2.0f;
	const float fRotatingSpeed = 1.0f;

	//pBox->GetRotation().x += fRotatingSpeed * dt;
	//pBox->GetRotation().y += fRotatingSpeed * dt;

	//pBox2->GetRotation().x -= fRotatingSpeed * dt;
	//pBox2->GetRotation().y -= fRotatingSpeed * dt;

	//pBox->Draw();
	//pBox2->Draw();

	//pBoxTex->GetRotation().x -= fRotatingSpeed * dt;
	//pBoxTex->GetRotation().y -= fRotatingSpeed * dt;

	//pBoxTex->Draw();

	//pSkull->GetRotation().x -= fRotatingSpeed * dt;
	pSkull->GetRotation().y -= fRotatingSpeed * dt;

	pSkull->Draw();

	return true;
}

bool Application::OnDestroy()
{
	if (pBox) delete pBox;
	if (pBox2) delete pBox2;
	if (pBoxTex) delete pBoxTex;
	return true;
}
