#ifndef BINDABLETESTING_H
#define BINDABLETESTING_H

//Local Inicludes
#include "EngineBase.h"
#include "DrawableSystem/Box.h"

//Standard Includes
#include <vector>

class BindableTesting : public EngineBase {
public:
	BindableTesting () : EngineBase("3D Rendering Engine", 800, 600) {}


private:
	bool OnStart() override {

		GetRenderer()->SetProjectionMatrix(DirectX::XMMatrixPerspectiveLH(1.0f, (float)GetHeight() / (float)GetWidth(), 0.5f, 100.0f));

		D3D11_VIEWPORT viewports[] = { {0.0f, 0.0f, (FLOAT)GetWidth(), (FLOAT)GetHeight(), 0.0f, 1.0f} };

		//Bind the viewports to the pipeline
		GetRenderer()->GetContext()->RSSetViewports((UINT)(sizeof(viewports) / sizeof(viewports[0])), viewports);

		ID3D11RenderTargetView* renderTargets[] = { GetRenderer()->GetBackbufferTargetView() };

		//Bind the backbuffer as the render target
		GetRenderer()->GetContext()->OMSetRenderTargets((UINT)(sizeof(renderTargets) / sizeof(renderTargets[0])), renderTargets, nullptr);

		//box = new Box(GetRenderer(), DirectX::XMMatrixPerspectiveFovLH(90.0f, (float)GetHeight() / (float)GetWidth(), 0.1f, 100.0f));
		box = new Box(GetRenderer());
		return true;
	}



	bool OnUpdate(float dt) override {
		box->Draw();
		return true;
	}


	bool OnDestroy() override {
		if (box) delete box;
		return true;
	}

private:
	Box* box = nullptr;

};

#endif // !BINDABLETESTING_H
