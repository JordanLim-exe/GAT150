#include "pch.h"
#include "TileMap.h"
#include "Objects/Scene.h"
#include "Objects/GameObject.h"
#include "Objects/ObjectFactory.h"

namespace nc {
	bool TileMap::Create(Scene* scene)
	{
		for (size_t i = 0; i < m_tiles.size(); i++) {
			int index = m_tiles[i];
			if (index != 0) {
				GameObject* gameObject = nc::ObjectFactory::Instance().Create<GameObject>(m_tileNames[index]);
				
				if (gameObject) {
					float x = static_cast<float>(i % m_numX);
					float y = static_cast<float>(i / m_numY);
					gameObject->m_transform.position = m_start + nc::Vector2{ x, y } * m_size;
					scene->AddGameObject(gameObject);
				}
			}
		}

		return true;
	}

	void TileMap::Read(const rapidjson::Value& value)
	{
		json::Get(value, "numX", m_numX);
		json::Get(value, "numY", m_numY);
		json::Get(value, "size", m_size);
		json::Get(value, "start", m_start);
		json::Get(value, "tileNames", m_tileNames);
		json::Get(value, "tiles", m_tiles);
	}
}
