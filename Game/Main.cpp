#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"

nc::InputSystem inputSystem;
nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::FrameTimer timer;

int main(int, char**)
{
	//nc::Timer timer;
	////profile
	//for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
	//std::cout << timer.ElapsedSeconds() << std::endl;
	

	renderer.Startup();
	renderer.Create("GAT150", 800, 600);

	inputSystem.Startup();
	

	nc::Texture* car = resourceManager.Get<nc::Texture>("cars.png", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("background.png", &renderer);
	
	float angle{ 0 };
	nc::Vector2 position{ 400, 300 };

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
		timer.Tick();
		inputSystem.Update();

		renderer.BeginFrame(); //begin

		angle += 1.0f;

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x - 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x + 200.0f * timer.DeltaTime();
		}


		texture2->Draw({ 0, 0 }, { 1, 1 }, 0);
		car->Draw({0, 16, 64, 144}, { 170, 0 }, { 1, 1 }, 0);

		renderer.EndFrame(); //end
	}



	// wait for keyboard enter to exit
	std::getchar();

	renderer.Shutdown();
	inputSystem.Shutdown();
	SDL_Quit();

	return 0;
}

