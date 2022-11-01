#pragma once

#include <windows.h>

class ConsoleEdit
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
	// Modified cursor belongs to the standart output stream.
	static void SetCursorPosition(int x, int y) 
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(x), (short)(y)});		
	}

	// Set console cursor position at the beginning of terminal.
	static void ResetCursorPosition() 
	{ 
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
	}
};