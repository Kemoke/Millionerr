#include "stdafx.h"
#include <consoleapi.h>
#include <string>
#include <iostream>
#include "Helpers.h"

using namespace std;

void Center(string item, int i)
{
	auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	auto rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - strlen(item.c_str())) / 2;
	csbi.dwCursorPosition.Y = (rows / 2) - 2 + 2 * i;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void Center(int length)
{
	auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - length) / 2;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
void Center(int length, bool y)
{
	auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	auto rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - length) / 2;
	csbi.dwCursorPosition.Y = (rows / 2);
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void Center(int length, int yOffset)
{
	auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	auto rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - length) / 2;
	csbi.dwCursorPosition.Y = rows - yOffset;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void HideCursor()
{
	auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void PrintTitleAscii()
{
	Cls();
	cout << endl;
	Center(119); cout << "__________                                                      __ __   __   __                      __               \n";
	Center(119); cout << "\\______   \\ ____  ____  ____   _____   ____   _____      _____ |__|  | |  | |__| ____   ____ _____  |__|______  ____  \n";
	Center(119); cout << " |    |  _// __ \\/ ___\\/  _ \\ /     \\_/ __ \\  \\__  \\    /     \\|  |  | |  | |  |/  _ \\ /    \\\\__  \\ |  \\_  __ \\/ __ \\ \n";
	Center(119); cout << " |    |   \\  ___|  \\__(  <_> )  Y Y  \\  ___/   / __ \\_ |  Y Y  \\  |  |_|  |_|  (  <_> )   |  \\/ __ \\|  ||  | \\|  ___/ \n";
	Center(119); cout << " |______  /\\___  >___  >____/|__|_|  /\\___  > (____  / |__|_|  /__|____/____/__|\\____/|___|  (____  /__||__|   \\___  >\n";
	Center(119); cout << "        \\/     \\/    \\/            \\/     \\/       \\/        \\/                            \\/     \\/               \\/ \n";
}

void PrintHSAscii()
{
	Cls();
	cout << endl;
	Center(70); cout << "  ___ ___  __        __                                              \n";
	Center(70); cout << " /   |   \\|__| ____ |  |__   ______ ____  ___________   ____   ______\n";
	Center(70); cout << "/    ~    \\  |/ ___\\|  |  \\ /  ___// ___\\/  _ \\_  __ \\_/ __ \\ /  ___/\n";
	Center(70); cout << "\\    Y    /  / /_/  >   Y  \\\\___ \\\\  \\__(  <_> )  | \\/\\  ___/ \\___ \\ \n";
	Center(70); cout << " \\___|_  /|__\\___  /|___|  /____  >\\___  >____/|__|    \\___  >____  >\n";
	Center(70); cout << "       \\/   /_____/      \\/     \\/     \\/                  \\/     \\/ \n";
}

void Cls()
{
	auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };
	if (hConsole == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hConsole,
		static_cast<TCHAR>(' '),
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hConsole,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hConsole, homeCoords);
}