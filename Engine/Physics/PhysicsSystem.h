#pragma once
#include "Core/System.h"
#include "box2d/box2d.h"

namespace nc
{
	class GameObject;

	class ContactListener;

	class PhysicsSystem : public System
	{
	public:
		struct RigidBodyData{
			Vector2 size;
			float density{ 0 };
			float friction{ 1 };
			float restitution{ 0.3f };
			float gravityScale{ 1 };
			bool lockAngle{ false };
			bool isDynamic{ false };
			bool isSensor{ false };
		};

	public:
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		b2Body* CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic = true);
		b2Body* CreateBody(const Vector2& position, float angle, const RigidBodyData& data, GameObject* gameObject);
		void DestroyBody(b2Body* body);

		static Vector2 WorldtoScreen(const Vector2& world) { return world * 32.0f; }
		static Vector2 ScreentoWorld(const Vector2& screen) { return screen * (1.0f / 32.0f); }

	protected:
		b2World* m_world{ nullptr };
		ContactListener* m_cL{nullptr};
	};
}
