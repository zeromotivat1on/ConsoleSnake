#include "Menu/MainMenu.h"

void MainMenu::Start()
{
	system("CLS");

	MainMenuState = MainMenuState::MMS_Idle;

	while (MainMenuState == MainMenuState::MMS_Idle)
	{
		Tick(); //
	}

	system("CLS");
	ConsoleEdit::ResetCursorPosition();
}

void MainMenu::Tick()
{
	RenderMainMenuScreen();
	ConsumeMainMenuInput();
}

void MainMenu::RenderMainMenuScreen()
{
	std::cout << "\n\n\tMAIN MENU\n\t" << (char)MainMenuInput::MMI_Play << " - Start game\n\t"
			  << "Esc"
			  << " - Exit ";

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
