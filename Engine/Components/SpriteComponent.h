#pragma once
#include "RenderComponent.h"

namespace nc {
	class SpriteComponent : public RenderComponent {
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Update() override;
		virtual void Draw() override;

	protected:
		class Texture* m_texture;
	};
}
