#include "Game.h"
#include "Game/Snake/Snake.h"
#include "Game/Food/Food.h"

Game::Game(std::unique_ptr<Map> map, std::unique_ptr<Snake> snake)
	: GameMap(std::move(map)),		 //
	  PlayerSnake(std::move(snake)), //
	  PlayerScore(0),				 //
	  SecondScreenOffsetX(5)
{
	GameMap->SetPlayerSnake(PlayerSnake);

	Seconds = 0;
	Minutes = 0;
	Hours = 0;

	GenerateFoodOnMap();
}

Game::Game(const IntVector2& mapSize, const IntVector2& snakeInitialLocation)
	: GameMap(std::make_unique<Map>(mapSize)),					  //
	  PlayerSnake(std::make_shared<Snake>(snakeInitialLocation)), //
	  PlayerScore(0),											  //
	  SecondScreenOffsetX(5)
{
	GameMap->SetPlayerSnake(PlayerSnake);

	Seconds = 0;
	Minutes = 0;
	Hours = 0;

	GenerateFoodOnMap();
}

Game::~Game()
{
	for (auto& worker : Workers) worker.join();
}

void Game::Reset()
{
	SYSTEM_CLEAR_CONSOLE();

	PlayerScore = 0;

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
	SYSTEM_CLEAR_CONSOLE();

	GameState = GameState::GS_Play;

	Workers.emplace_back(std::thread(&Game::RenderTimer, this));

	while (GameState != GameState::GS_Shutdown)
	{
		Tick(); //
	}

	SYSTEM_RESET_CONSOLE();
}

// Simple timer implementation on separate thread.
void Game::RenderTimer()
{
	using namespace std::literals::chrono_literals;

	int cursorX = GameMap->GetWidth() + SecondScreenOffsetX;
	int cursorY = (int)(GameMap->GetHeight() * 0.25);

	std::stringstream sstream;

	while (GameState != GameState::GS_Shutdown)
	{
		// Loaded values from atomic.

		int lsec = Seconds.load();
		int lmin = Minutes.load();
		int lhr = Hours.load();

		if (GameState == GameState::GS_Over)
		{
			if (lsec != 0 || lmin != 0 || lhr != 0)
			{
				Seconds = 0;
				Minutes = 0;
				Hours = 0;
				sstream.clear();
			}

			std::this_thread::sleep_for(1s);

			continue;
		}

		if (lsec == 60)
		{
			Minutes = ++lmin;

			if (lmin == 60)
			{
				Hours = ++lhr;
				lmin = 0;
				Minutes = 0;
			}

			lsec = 0;
			Seconds = 0;
		}

		sstream << "Time: "												 //
				<< std::setfill('0') << std::setw(2) << Hours << " : "	 //
				<< std::setfill('0') << std::setw(2) << Minutes << " : " //
				<< std::setfill('0') << std::setw(2) << Seconds << '\n';

		ConsoleRenderer::RenderVertically(sstream, IntVector2(cursorX, cursorY));

		Seconds = ++lsec;
		sstream.clear();

		std::this_thread::sleep_for(1s);
	}
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

	std::this_thread::sleep_for(DeltaTime);
}

void Game::GameTick()
{
	ConsumeGameInput();

	TickActors();
	CheckSnakeCollision();

	if (CheckEndGame()) return;

	RenderGameMap();
	RenderSecondScreen();
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

void Game::RenderSecondScreen()
{
	int cursorX = GameMap->GetWidth() + SecondScreenOffsetX;
	int cursorY = 0;

	std::stringstream sstream;

	sstream << "Score: " << PlayerScore << '\n';

	ConsoleRenderer::RenderVertically(sstream, IntVector2(cursorX, cursorY));

#if SDEBUG
	cursorY = (int)(GameMap->GetHeight() * 0.5);

	sstream.clear();

	sstream << "DEBUG ONLY INFO\n"										   //
			<< "---------------\n"										   //
			<< "Snake velocity: " << PlayerSnake->GetVelocity() << "   \n" //
			<< "Snake position: " << PlayerSnake->GetLocation() << "   \n" //
			<< "Snake length: " << PlayerSnake->GetLength() << "   \n"	   //
			<< "Snake is dead: " << (PlayerSnake->GetIsDead() ? "True" : "False") << "   \n";

	ConsoleRenderer::RenderVertically(sstream, IntVector2(cursorX, cursorY));
#endif
}

void Game::ConsumeGameInput()
{
	Snake* snake = PlayerSnake.get();
	if (!snake) return;

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
	if (!snake) return;

	const IntVector2 snakeLocation = snake->GetLocation();
	if (!GameMap->IsInsideMap(snakeLocation))
	{
		snake->SetCollidedCell(std::make_unique<Cell>(snakeLocation, CellType::CT_Wall));
		return;
	}

	switch (GameMap->GetMapCellTexture(snakeLocation))
	{
	case (char)CellType::CT_Wall:
	{
		snake->SetCollidedCell(std::make_unique<Cell>(snakeLocation, CellType::CT_Wall));
		break;
	}

	case (char)CellType::CT_SnakeBody:
	{
		snake->SetCollidedCell(std::make_unique<Cell>(snakeLocation, CellType::CT_SnakeBody));
		break;
	}

	case (char)CellType::CT_Food:
	{
		// Add scores to player.
		const std::shared_ptr<Food> eatenFood = std::static_pointer_cast<Food>(GameMap->GetActorByLocation(snakeLocation));
		if (!eatenFood) break;

		PlayerScore += eatenFood->GetScore();

		// Regenerate food cell.
		GameMap->RemoveActorByLocation(snakeLocation);
		GenerateFoodOnMap();

		snake->SetCollidedCell(std::make_unique<Cell>(snakeLocation, CellType::CT_Food));
		break;
	}

	default:
		break;
	}
}

bool Game::CheckEndGame()
{
	bool PlayerSnakeDead = PlayerSnake->GetIsDead();
	bool PlayerWin = PlayerSnake->GetLength() == GameMap->GetFreeCells();

	if (PlayerSnakeDead || PlayerWin)
	{
		GameState = GameState::GS_Over; //
	}

	return GameState == GameState::GS_Over;
}

void Game::RenderGameOverScreen()
{
	int cursorX = GameMap->GetWidth() + 5;
	int cursorY = 0;

	std::stringstream sstream;

	sstream << "GAME OVER          \n"
			<< "Your score - " << PlayerScore << "          \n"
			<< "r - Restart the game          \n"
			<< "Esc - Go to main menu          \n";

	ConsoleRenderer::RenderVertically(sstream, IntVector2(cursorX, cursorY));
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

template <typename T> //
bool Game::AddActorToMap(const IntVector2& location, const CellType type)
{
	static_assert(std::is_base_of<Actor, T>::value, "T is not of type Actor");
	return GameMap->AddActor(std::make_unique<T>(location, type));
}

template <typename T> //
bool Game::GenerateFoodOnMap()
{
	static_assert(std::is_base_of<Food, T>::value, "T is not of type Food");

	IntVector2 foodLocation = Food::GenerateLocation(GameMap->GetSize());

	// Get rid of situations when food doesn't spawn on empty cell.
	// Warning: with snake grow, amount of iterations will increase (on average).

	// Add 1 to player snake as at this moment we don't know
	// that snake has increased, but it definetly will.
	bool mapHasSpaceToSpawnFood = PlayerSnake->GetLength() + 1 < GameMap->GetFreeCells();

	// While food not on empty cell and map has space to spawn food - retry to spawn new food.
	while (GameMap->GetMapCellTexture(foodLocation) != (char)CellType::CT_Empty && mapHasSpaceToSpawnFood)
	{
		foodLocation = Food::GenerateLocation(GameMap->GetSize()); //

		std::stringstream sstream;
		sstream << "Generated food location: " << foodLocation << " Game map size: " << GameMap->GetSize();
		sstream << "Snake length + 1: " << PlayerSnake->GetLength() + 1 << "Map free cells: " << GameMap->GetFreeCells();
		ConsoleRenderer::RenderVertically(sstream, IntVector2(10, 10));
	}

	return AddActorToMap<T>(foodLocation, CellType::CT_Food);
}
