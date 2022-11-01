#pragma once

#include "Core.h"

// Primary player interaction with the snake game app.
class MainMenu
{
public:
	MainMenu() = default;
	~MainMenu() = default;

private:
	/**
	 * As main menu is the primar interaction with the app,
	 * this field is set after player chose option from main menu.
	 * Tells the app class to which state it should update.
	 */
	MainMenuState MainMenuState = MainMenuState::MMS_Idle;

public:
	enum class MainMenuState GetMainMenuState() const { return MainMenuState; }

	// Get app state that corresponds to main menu state.
	AppState GetCorrespondingAppState() const;

private:
	// Update and display main menu screen.
	void RenderMainMenuScreen();

	// Handle player input during main menu.
	void ConsumeMainMenuInput();

public:
	// Perfrom main menu tick.
	void Tick();

	// Start the main menu loop
	void Start();
};
