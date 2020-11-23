#ifndef APPLICATION_H
#define APPLICATION_H

//Local Includes
#include "EngineBase.h"
#include "DrawableSystem/Box.h"
#include "DrawableSystem/BoxWithTexture.h"
#include "DrawableSystem/Skull.h"

//Standard Includes
#include <vector>
#include <cstdint>

class Application : public EngineBase {
public:
	using EngineBase::EngineBase;
private:
	bool OnStart() override; 
	bool OnUpdate(float dt) override; 
	bool OnDestroy() override;

private:
	Box* pBox = nullptr;
	Box* pBox2 = nullptr;
	BoxWithTexture* pBoxTex = nullptr;
	Skull* pSkull = nullptr;
	
};

#endif // !APPLICATION_H