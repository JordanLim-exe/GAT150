#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc {
	bool nc::SpriteComponent::Create(void* data)
	{
		m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());

		return true;
	}

	void nc::SpriteComponent::Destroy()
	{
	}

	void nc::SpriteComponent::Update()
	{
	}

	void nc::SpriteComponent::Draw()
	{
		m_texture->Draw({ 0, 16, 64, 144 }, m_owner->m_transform.position, { m_owner->m_transform.scale, m_owner->m_transform.scale }, m_owner->m_transform.angle);
	}
}
