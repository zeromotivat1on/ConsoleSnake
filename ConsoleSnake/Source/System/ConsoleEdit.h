#pragma once

#include <windows.h>
#include <Math/IntVector2.h>

// Class for console manipulations.
class ConsoleEdit final
{
public:
	// Show or hide console cursor.
	static void SetCursorVisibility(bool isVisible)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(out, &cursorInfo);

		cursorInfo.bVisible = isVisible;

		SetConsoleCursorInfo(out, &cursorInfo);
	}

	// Set console cursor at specified position.
	// Modified cursor belongs to the standard output stream.
	static void SetCursorPosition(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(x), (short)(y)}); //
	}

	static void SetCursorPosition(const IntVector2& pos)
	{
		SetCursorPosition(pos.X, pos.Y); //
	}

	// Set console cursor position at the beginning of terminal.
	static void ResetCursorPosition()
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0}); //
	}
};