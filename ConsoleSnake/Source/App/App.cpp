#include "App.h"
#include "Game/Map/Map.h"
#include "Game/Snake/Snake.h"

App::App(const SnakeGameParams& snakeGameParams) //
	: MainMenu(std::make_shared<class MainMenu>())
{
	SnakeGame = std::make_shared<Game>(								  //
		std::make_unique<Map>(snakeGameParams.mapSize),				  //
		std::make_unique<Snake>(snakeGameParams.snakeInitialLocation) //
	);
}

void App::Start()
{
	ConsoleEdit::SetCursorVisibility(false);

	while (AppState != AppState::AS_Shutdown)
	{
		Tick(); //
	}

	ConsoleEdit::ResetCursorPosition();
	ConsoleEdit::SetCursorVisibility(true);
}

void App::Tick()
{
	switch (AppState)
	{
	case AppState::AS_MainMenu:
		MainMenu->Start();
		AppState = MainMenu->GetCorrespondingAppState();
		break;

	case AppState::AS_Game:
		SnakeGame->Start();
		AppState = SnakeGame->GetCorrespondingAppState();
		break;

	case AppState::AS_Shutdown:
	default:
		break;
	}

	std::this_thread::sleep_for(DeltaTime);
}
