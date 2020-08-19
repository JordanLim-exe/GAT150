#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"

namespace nc {
	bool Scene::Create(void* data)
	{
		m_engine = static_cast<Engine*>(data);
		return true;
	}

	void Scene::Destroy()
	{
		// call the member function to remove all game objects
		RemoveAllGameObjects();
	}

	void Scene::Read(const rapidjson::Value& value)
	{
		const rapidjson::Value& objectsValue = value["GameObjects"];
		if (objectsValue.IsArray())
		{
			ReadGameObjects(objectsValue);
		}
	}

	void Scene::ReadGameObjects(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject())
			{
				std::string typeName;
				// read component “type” name from json (Get)
				json::Get(objectValue, "type", typeName);
				nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>(typeName);// get from object factory, use typeName as the key

				if (gameObject)
				{
					gameObject->Create(m_engine);
					// call game object read (pass in objectValue)
					gameObject->Read(objectValue);
					// call AddGameObject passing in the game object
					AddGameObject(gameObject);
				}
			}
		}
	}

	void Scene::Update()
	{
		// iterate through the actors and call Update on each actor
		for (auto gameObject : m_gameObjects) {
			// update
			gameObject->Update();
		}

	}

	void Scene::Draw()
	{
		// iterate through the actors and call Draw on each actor
		for (auto gameObject : m_gameObjects) {
			// draw
			gameObject->Draw();
		}

	}

	GameObject* Scene::Find(const std::string& name)
	{
		for (auto gameObject : m_gameObjects)
		{
			// compare game object name to name parameter (==)
			if(gameObject->m_name == name)
			{
				return gameObject;
			}
		}
		return nullptr;
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		// push back gameObject
		m_gameObjects.push_back(gameObject);
	}
	
	void Scene::RemoveGameObject(GameObject* gameObject)
	{
		auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
		if (iter != m_gameObjects.end())
		{
			// destroy 
			(*iter)->Destroy();
			// delete 
			delete (*iter);
			// erase iter from m_gameObjects
			
		}

	}

	void Scene::RemoveAllGameObjects()
	{
		for (GameObject* gameObject : m_gameObjects)
		{
			// destroy
			// delete
		}

		// clear game objects

	}
}
