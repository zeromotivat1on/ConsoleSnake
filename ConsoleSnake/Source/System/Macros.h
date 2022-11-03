#pragma once

#include "System/ConsoleEdit.h"

// Debug the app.
#define SDEBUG 0

// Map dimensions.
#define MAP_WIDTH 80
#define MAP_HEIGHT 30

// Default time between ticks (in milliseconds).
#define TICK_MS 40

// Are we playing on Windows?
#define WINDOWS 1

#if WINDOWS
#define CLEAR_CMD "CLS"
#else
#define CLEAR_CMD "clear"
#endif

#define SYSTEM_CLEAR_CONSOLE() system(CLEAR_CMD);

#define SYSTEM_RESET_CONSOLE()                                                                                                               \
	SYSTEM_CLEAR_CONSOLE();                                                                                                                  \
	ConsoleEdit::ResetCursorPosition();
