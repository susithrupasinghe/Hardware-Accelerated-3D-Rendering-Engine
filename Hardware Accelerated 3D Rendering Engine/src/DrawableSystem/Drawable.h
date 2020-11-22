#ifndef DRAWABLE_H
#define DRAWABLE_H

//Local Includes
#include "../Renderer.h"
#include "../BindableSystem/BindableSystem.h"

//DirectX Includes
#include <DirectXMath.h>

//Standard Includes
#include <vector>

class Drawable {
public:
	Drawable(const Renderer* pRenderer);
	~Drawable();

	virtual void Draw();

protected:
	void AddBindable(const Bindable* pBindable);

	void AddIndexBufferBindable(const IndexBuffer* pIndexBuffer);

	constexpr const Renderer* GetRenderer() const {
		return m_ptrRenderer;
	}

private:
	const Renderer* m_ptrRenderer = nullptr;
	std::vector<const Bindable*> m_ptrBindables;
	UINT m_nIndexCount = 0;
};

#endif // !DRAWABLE_H
