#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Core/Factory.h"


nc::Engine engine;
nc::GameObject player;
nc::Factory<nc::Object, std::string> objectFactory;

int main(int, char**)
{
	//nc::Timer timer;
	////profile
	//for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
	//std::cout << timer.ElapsedSeconds() << std::endl;
	rapidjson::Document document;

	
	engine.Startup();

	objectFactory.Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
	objectFactory.Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);
	
	nc::GameObject* player = objectFactory.Create<nc::GameObject>("GameObject");

	player->Create(&engine);
	nc::json::Load("player.txt", document);
	player->Read(document);

	nc::Component* component;
	component = objectFactory.Create<nc::Component>("PhysicsComponent");
	player->AddComponent(component);
	component->Create();

	component = new nc::SpriteComponent;
	player->AddComponent(component);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	component->Create();

	component = new nc::PlayerComponent;
	player->AddComponent(component);
	component->Create();
	
	
	
	//texture
	nc::Texture* texture2 = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());
	
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
		player->Update();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::HELD)
		{
			quit = true;
		}

		engine.GetSystem<nc::Renderer>()->BeginFrame(); //begin

		texture2->Draw({ 0, 0 }, { 1, 1 }, 0);

		player->Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame(); //end
	}

	engine.Shutdown();

	return 0;
}

