#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "Scene.h"
#include "ObjectFactory.h"

namespace nc {
	GameObject::GameObject(const GameObject& other)
	{
		m_name = other.m_name;
		m_tag = other.m_tag;
		m_lifetime = other.m_lifetime;

		m_flags = other.m_flags;

		m_transform = other.m_transform;
		m_engine = other.m_engine;
		m_scene = other.m_scene;

		for (Component* component : other.m_components) {
			Component* clone = dynamic_cast<Component*>(component->Clone());
			clone->m_owner = this;
			AddComponent(clone);
		}
	}
	bool GameObject::Create(void* data)
	{
		m_scene = static_cast<Scene*>(data);
		m_engine = m_scene->m_engine;
		return true;
	}

	void GameObject::Destroy()
	{
		RemoveAllComponents();
	}
	void GameObject::Read(const rapidjson::Value& value)
	{
		json::Get(value, "name", m_name);
		json::Get(value, "tag", m_tag);
		json::Get(value, "lifetime", m_lifetime);
		
		bool transient = m_flags[eFlag::TRANSIENT];
		json::Get(value, "transient", transient);
		m_flags[eFlag::TRANSIENT] = transient;

		json::Get(value, "position", m_transform.position);
		json::Get(value, "scale", m_transform.scale);
		json::Get(value, "angle", m_transform.angle);

		if (value.HasMember("Components")) {
			const rapidjson::Value& componentsValue = value["Components"];
			if (componentsValue.IsArray())
			{
				ReadComponents(componentsValue);
			}
		}
	}
	void GameObject::AddComponent(Component* component)
	{
		component->m_owner = this;
		m_components.push_back(component);
	}
	void GameObject::RemoveComponent(Component* component)
	{
		auto iter = std::find(m_components.begin(), m_components.end(), component);
		if (iter != m_components.end()) {
			(*iter)->Destroy();
			delete (*iter);
		}

	}
	void GameObject::RemoveAllComponents()
	{
		for (auto component : m_components) {
			component->Destroy();
			delete component;
		}
		m_components.clear();
	}
	void GameObject::Update()
	{
		for (auto component : m_components) {
			component->Update();
		}

		if (m_flags[eFlag::TRANSIENT]) {
			m_lifetime = m_lifetime - m_engine->GetTimer().DeltaTime();
			m_flags[eFlag::DESTROY] = (m_lifetime <= 0);
		}
	}
	void GameObject::Draw()
	{
		RenderComponent* component = GetComponent<RenderComponent>();
		if (component) {
			component->Draw();
		}
	}
	void GameObject::BeginContact(GameObject* other)
	{
		m_contacts.push_back(other);
		
		Event event;
		event.type = "CollisionEnter";
		event.sender = other;
		event.receiver = this;

		EventManager::Instance().Notify(event);
	}
	void GameObject::EndContact(GameObject* other)
	{
		m_contacts.remove(other);

		Event event;
		event.type = "CollisionExit";
		event.sender = other;
		event.receiver = this;

		std::cout << "end: " << other->m_name << std::endl;
	}
	std::vector<GameObject*> GameObject::GetContactsWithTag(const std::string& tag)
	{
		std::vector<GameObject*> contacts;

		for (auto contact : m_contacts) {
			if (contact->m_tag == tag) {
				contacts.push_back(contact);
			}
		}

		return contacts;
	}
	void GameObject::ReadComponents(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& componentValue = value[i];
			if (componentValue.IsObject())
			{
				std::string typeName;
				// read component “type” name from json (Get)
				json::Get(componentValue, "type", typeName);
				Component* component = nc::ObjectFactory::Instance().Create<nc::Component>(typeName);// create component from object factory
					if (component)
					{
						// call component create, pass in gameobject (this)
						component->Create(this);
						// call component read
						component->Read(componentValue);
						// add component to game object
						this->AddComponent(component);
					}
			}
		}
	}

}