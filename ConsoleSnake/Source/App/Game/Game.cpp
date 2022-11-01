#include "Game.h"
#include "Snake.h"
#include "Food.h"

Game::Game(const IntVector2& mapSize, const IntVector2& snakeInitialLocation)
{
	GameMap = std::make_unique<Map>(mapSize);
	PlayerSnake = std::make_shared<Snake>(snakeInitialLocation);

	GameMap->SetPlayerSnake(PlayerSnake);

	GenerateFoodOnMap();
}

void Game::Reset()
{
	PlayerSnake->Reset();

	GameMap->Reset();
	GameMap->SetPlayerSnake(PlayerSnake);

	GenerateFoodOnMap();
}

AppState Game::GetCorrespondingAppState() const
{
	switch (GameState)
	{
	case GameState::GS_Shutdown:
		return AppState::AS_MainMenu;

	case GameState::GS_Over:
	case GameState::GS_Play:
	default:
		return AppState::AS_Game;
	}
}

void Game::Start()
{
	system("CLS");

	GameState = GameState::GS_Play;

	while (GameState != GameState::GS_Shutdown)
	{
		Tick(); //
	}

	system("CLS");
	ConsoleEdit::ResetCursorPosition();
}

void Game::Tick()
{
	switch (GameState)
	{
	case GameState::GS_Play:
		GameTick();
		break;
	case GameState::GS_Over:
		GameOverTick();
		break;
	}
}

void Game::GameTick()
{
	RenderGameMap();
	ConsumeGameInput();
	TickActors();
	CheckSnakeCollision();
	CheckEndGame();
}

void Game::GameOverTick()
{
	RenderGameOverScreen();
	ConsumeGameOverInput();
}

void Game::RenderGameMap()
{
	GameMap->Render();

	// Create "real-time rendering" effect.
	// Set console cursor at the start of the console.
	ConsoleEdit::ResetCursorPosition();
}

void Game::ConsumeGameInput()
{
	Snake* snake = PlayerSnake.get();

	/**
	 * Check for console recent keystroke.
	 * Allows player snake to move automatically after movement key was pressed.
	 */

	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)GameInput::GI_SUp:
			snake->SetVelocity(IntVector2::UpVector);
			return;

		case (char)GameInput::GI_SDown:
			snake->SetVelocity(IntVector2::DownVector);
			return;

		case (char)GameInput::GI_SLeft:
			snake->SetVelocity(IntVector2::LeftVector);
			return;

		case (char)GameInput::GI_SRight:
			snake->SetVelocity(IntVector2::RightVector);
			return;

		default:
			return;
		}
	}
}

void Game::TickActors()
{
	PlayerSnake->Tick();

	for (const auto& actor : GameMap->GetActors())
	{
		actor.get()->Tick(); //
	}
}

void Game::CheckSnakeCollision()
{
	Snake* snake = PlayerSnake.get();

	const IntVector2 snakeLocation = snake->GetLocation();
	if (GameMap->IsOutOfBounds(snakeLocation))
	{
		std::unique_ptr<Cell> cell = std::make_unique<Cell>(snakeLocation, CellType::CT_Wall);
		snake->SetCollidedCell(cell);
		return;
	}

	Map::MapType mapBlueprint = GameMap->GetMapBlueprint();
	switch (mapBlueprint[snakeLocation.Y][snakeLocation.X])
	{
	case (char)CellType::CT_Wall:
	{
		std::unique_ptr<Cell> cell = std::make_unique<Cell>(snakeLocation, CellType::CT_Wall);
		snake->SetCollidedCell(cell);
		break;
	}

	case (char)CellType::CT_SnakeBody:
	{
		std::unique_ptr<Cell> cell = std::make_unique<Cell>(snakeLocation, CellType::CT_SnakeBody);
		snake->SetCollidedCell(cell);
		break;
	}

	case (char)CellType::CT_Food:
	{
		// Regenerate food cell.
		GameMap->RemoveActorByLocation(snakeLocation);
		GenerateFoodOnMap();

		std::unique_ptr<Cell> cell = std::make_unique<Cell>(snakeLocation, CellType::CT_Food);
		snake->SetCollidedCell(cell);
		break;
	}

	default:
		break;
	}
}

void Game::CheckEndGame()
{
	bool PlayerSnakeDead = PlayerSnake->GetIsDead();
	bool PlayerWin = PlayerSnake->GetLength() == GameMap->GetFreeCells();

	if (PlayerSnakeDead || PlayerWin)
	{
		GameState = GameState::GS_Over; //
	}
}

void Game::RenderGameOverScreen()
{
	std::cout << "\n\n\tGAME OVER\n\tr - Restart the game\n\tEsc - Go to main menu";

	ConsoleEdit::ResetCursorPosition();
}

void Game::ConsumeGameOverInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)GameOverInput::GOI_Restart:
			GameState = GameState::GS_Play;
			Reset();
			break;
		case (char)GameOverInput::GOI_End:
			GameState = GameState::GS_Shutdown;
			Reset();
			break;
		default:
			break;
		}
	}
}

bool Game::AddActorToMap(const IntVector2& location, const CellType type)
{
	std::unique_ptr<Actor> actor = std::make_unique<Actor>(location, type);
	return GameMap->AddActor(actor);
}

bool Game::GenerateFoodOnMap()
{
	Map::MapType mapBlueprint = GameMap->GetMapBlueprint();
	IntVector2 foodLocation = Food::GenerateLocation(GameMap->GetSize());

	// Get rid of situations when food doesn't spawn on empty cell.
	// FIX: With snake grows, amount of iterations will increase (on average)
	while (mapBlueprint[foodLocation.Y][foodLocation.X] != (char)CellType::CT_Empty)
	{
		foodLocation = Food::GenerateLocation(GameMap->GetSize()); //
	}

	return AddActorToMap(foodLocation, CellType::CT_Food);
}
