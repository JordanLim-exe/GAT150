#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"


nc::Engine engine;
nc::GameObject player;

int main(int, char**)
{
	//nc::Timer timer;
	////profile
	//for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
	//std::cout << timer.ElapsedSeconds() << std::endl;
	
	engine.Startup();
	
	player.Create(&engine);
	player.m_transform.position = { 400, 300 };
	player.m_transform.angle = 45;

	nc::Component* component = new nc::PhysicsComponent;
	player.AddComponent(component);
	component->Create();

	component = new nc::SpriteComponent;
	player.AddComponent(component);
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

		//controller
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle -= 200.0f * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle += 200.0f * engine.GetTimer().DeltaTime();
		}

		//physics
		nc::Vector2 force{ 0,0 };
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD) {
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::dtor(player.m_transform.angle));

		engine.GetSystem<nc::Renderer>()->BeginFrame(); //begin

		texture2->Draw({ 0, 0 }, { 1, 1 }, 0);

		player.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame(); //end
	}

	engine.Shutdown();

	return 0;
}

