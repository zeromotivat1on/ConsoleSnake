#include "MainMenu.h"

void MainMenu::Start()
{
	SYSTEM_CLEAR_CONSOLE();

	MainMenuState = MainMenuState::MMS_Idle;

	while (MainMenuState == MainMenuState::MMS_Idle)
	{
		Tick(); //
	}

	SYSTEM_RESET_CONSOLE();
}

void MainMenu::Tick()
{
	ConsumeMainMenuInput();
	RenderMainMenuScreen();
}

void MainMenu::RenderMainMenuScreen()
{
	std::stringstream sstream;

	sstream << "MAIN MENU\n"
			<< (char)MainMenuInput::MMI_Play << " - Start game\n"
			<< "Esc - Exit\n";

	ConsoleRenderer::RenderVertically(sstream, IntVector2(OffsetX, OffsetY));

	ConsoleEdit::ResetCursorPosition();
}

void MainMenu::ConsumeMainMenuInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)MainMenuInput::MMI_Play:
			MainMenuState = MainMenuState::MMS_StartPlay;
			break;

		case (char)MainMenuInput::MMI_Exit:
			MainMenuState = MainMenuState::MMS_Shutdown;
			break;

		default:
			break;
		}
	}

	std::this_thread::sleep_for(DeltaTime);
}

AppState MainMenu::GetCorrespondingAppState() const
{
	switch (MainMenuState)
	{
	case MainMenuState::MMS_StartPlay:
		return AppState::AS_Game;

	case MainMenuState::MMS_Shutdown:
		return AppState::AS_Shutdown;

	case MainMenuState::MMS_Idle:
	default:
		return AppState::AS_MainMenu;
	}
}
