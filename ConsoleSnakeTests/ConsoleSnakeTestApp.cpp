#include "pch.h"
#include "CppUnitTest.h"
#include "Core.h"
#include "App.h"
#include "App.cpp"
#include "Game/Game.cpp"
#include "Game/Map/Map.cpp"
#include "Game/Abstractions/Actor.cpp"
#include "Game/Abstractions/Cell.cpp"
#include "Game/Food/Food.cpp"
#include "Game/Snake/Snake.cpp"
#include "Menu/MainMenu.cpp"
#include "Math/IntVector2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ConsoleSnakeTests
{

	TEST_CLASS(ConsoleSnakeTestApp)
	{
	public:
		App sgapp;
		std::shared_ptr<MainMenu> menu;
		std::shared_ptr<Game> game;

		IntVector2 mapSize = IntVector2(10, 10);
		IntVector2 snakePos = IntVector2(5, 5);

		TEST_METHOD_INITIALIZE(Init)
		{
			SnakeGameParams params{ mapSize, snakePos };
			sgapp = App(params);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(TestAppCtor)
			TEST_PRIORITY(0)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(TestAppCtor)
		{
			menu = std::static_pointer_cast<MainMenu>(sgapp.GetMainMenu());
			if (!menu)
			{
				Assert::Fail(L"Failed to cast App.MainMenu (AppComponent-type) to MainMenu-type");
			}

			game = std::static_pointer_cast<Game>(sgapp.GetMainMenu());
			if (!game)
			{
				Assert::Fail(L"Failed to cast App.Game (AppComponent-type) to Game-type");
			}
		}
	};
}
