#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"


nc::Engine engine;
//nc::GameObject player;
nc::Scene scene;

int main(int, char**)
{
	
	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);
	
	scene.Create(&engine);
	scene.Read(document);

	for (size_t i = 0; i < 10; i++) {
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("p_Coin");
		gameObject->m_transform.position = nc::Vector2{ nc::random(0, 800), nc::random(150, 450) };
		//gameObject->m_transform.angle = nc::random(0, 360);
		scene.AddGameObject(gameObject);
	}

	/*player->Create(&engine);
	nc::json::Load("player.txt", document);
	player->Read(document);

	nc::Component* component;
	component = nc::ObjectFactory::Instance().Create<nc::Component>("PhysicsComponent");
	component->Create(player);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("SpriteComponent");
	component->Create(player);
	player->AddComponent(component);
	nc::json::Load("sprite.txt", document);
	component->Read(document);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("PlayerComponent");
	component->Create(player);
	player->AddComponent(component);
	*/
	
	
	//texture
	//nc::Texture* texture2 = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());
	
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case::SDL_QUIT:
			quit = true;
			break;
		}

		//update
		engine.Update();
		scene.Update();
		//player->Update();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::HELD)
		{
			quit = true;
		}

		engine.GetSystem<nc::Renderer>()->BeginFrame(); //begin

		
		scene.Draw();

		//player->Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame(); //end
	}

	scene.Destroy();
	engine.Shutdown();

	return 0;
}

