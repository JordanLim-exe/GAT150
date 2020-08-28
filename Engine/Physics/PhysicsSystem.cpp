#include "pch.h"
#include "PhysicsSystem.h"
#include "Objects/GameObject.h"
#include "ContactListener.h"

namespace nc {
	bool PhysicsSystem::Startup()
	{
		b2Vec2 gravity{ 0, 10 };
		m_world = new b2World(gravity);

		m_cL = new ContactListener;
		m_world->SetContactListener(m_cL);

		return true;
	}

	void PhysicsSystem::Shutdown()
	{
		delete m_world;
		m_world = nullptr;
	}

	void PhysicsSystem::Update()
	{
		float timeStep = (1.0f / 60.0f);
		m_world->Step(timeStep, 8, 3);
	}
	
	b2Body* PhysicsSystem::CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic)
	{
		b2BodyDef bodyDef;

		Vector2 world = PhysicsSystem::ScreentoWorld(position);

		bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position.Set(world.x, world.y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(size.x, size.y);

		body->CreateFixture(&shape, density);

		return body;
	}

	b2Body* PhysicsSystem::CreateBody(const Vector2& position, float angle, const RigidBodyData& data, GameObject* gameObject)
	{
		b2BodyDef bodyDef;

		Vector2 world = PhysicsSystem::ScreentoWorld(position);

		bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position.Set(world.x, world.y);
		bodyDef.angle = nc::dtor(angle);
		bodyDef.fixedRotation = data.lockAngle;
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		Vector2 worldSize = PhysicsSystem::ScreentoWorld(data.size);
		shape.SetAsBox(worldSize.x, worldSize.y);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.isSensor;
		fixtureDef.shape = &shape;
		fixtureDef.userData = gameObject;


		body->CreateFixture(&fixtureDef);

		return body;
	}
	void PhysicsSystem::DestroyBody(b2Body* body)
	{
		m_world->DestroyBody(body);
	}
}
