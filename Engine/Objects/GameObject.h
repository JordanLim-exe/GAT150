#pragma once
#include "Object.h"
#include "Math\Transform.h"
#include "Engine.h"
#include <vector>

namespace nc {
	class Component; //forward declaration

	class GameObject : public Object {
	public:
		GameObject() = default;
		GameObject(const GameObject& other);

		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new GameObject{*this}; }

		void Read(const rapidjson::Value& value) override;

		template<typename T>
		T* GetComponent() {
			T* result{ nullptr };
			for (auto component : m_components) {
				result = dynamic_cast<T*>(component);
				if (result) break;
			}
			return result;
		}

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponents();

		void Update();
		void Draw();

		void ReadComponents(const rapidjson::Value& value);

		friend class Component;
		friend class PhysicsComponent;

	public:
		std::string m_name;
		Transform m_transform;
		Engine* m_engine{ nullptr };

	protected:
		std::vector<Component*> m_components;
	};
}