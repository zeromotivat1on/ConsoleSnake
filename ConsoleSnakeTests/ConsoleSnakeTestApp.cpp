#include "pch.h"
#include "CppUnitTest.h"
#include "AppObjects.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ConsoleSnakeTests
{
	TEST_CLASS(ConsoleSnakeTestApp)
	{
	public:
		TEST_METHOD_INITIALIZE(Init)
		{
			static IntVector2 mapSize = IntVector2(10, 10);
			static IntVector2 snakePos = IntVector2(5, 5);
			SnakeGameParams params = { mapSize, snakePos };
			SGApp = std::make_shared<App>(params);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(TestAppCtor)
			TEST_PRIORITY(0)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(TestAppCtor)
		{
			Menu = std::dynamic_pointer_cast<MainMenu>(SGApp->GetMainMenu());
			if (!Menu)
			{
				Assert::Fail(L"Failed to cast App.MainMenu (AppComponent-type) to MainMenu-type");
			}

			Game = std::dynamic_pointer_cast<class Game>(SGApp->GetSnakeGame());
			if (!Game)
			{
				Assert::Fail(L"Failed to cast App.Game (AppComponent-type) to Game-type");
			}
		}
	};
}
