#pragma once

#include "sstream"
#include "System/Macros.h"
#include "Math/IntVector2.h"

// Simple class for convinient console rendering (printing).
class ConsoleRenderer final
{
public:
	/**
	 * Render string stream at given location vertically.
	 * Reserves relative position even after new line.
	 * Prints to standard output stream.
	 * Don't forget to separate your data with "\n".
	 */
	static void RenderVertically(std::stringstream& sstream, const IntVector2& pos = IntVector2::ZeroVector)
	{
		int x = pos.X;
		int y = pos.Y;

		std::string chunk;
		while (std::getline(sstream, chunk))
		{
			ConsoleEdit::SetCursorPosition(x, y++);
			std::cout << chunk;
		}

		ConsoleEdit::ResetCursorPosition();
	}

	static void Render(const char* data, const IntVector2& pos = IntVector2::ZeroVector) 
	{
		ConsoleEdit::SetCursorPosition(pos.X, pos.Y);
		std::cout << data;
		ConsoleEdit::ResetCursorPosition();
	}
};
