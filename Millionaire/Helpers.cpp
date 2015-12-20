#include "stdafx.h"
#include <consoleapi.h>
#include <string>
#include <iostream>
#include "Helpers.h"

using namespace std;

void Center(string &item, int i, HANDLE &hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	auto rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - strlen(item.c_str())) / 2;
	csbi.dwCursorPosition.Y = (rows / 2) - 2 + 2 * i;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void Center(int length, HANDLE &hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - length) / 2;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
void Center(int length, bool y, HANDLE &hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	auto rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - length) / 2;
	csbi.dwCursorPosition.Y = (rows / 2);
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void Center(int length, int yOffset, HANDLE &hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	auto rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - length) / 2;
	csbi.dwCursorPosition.Y = rows - yOffset;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void HideCursor(HANDLE &hConsole)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void PrintTitleAscii(HANDLE &hConsole)
{
	Cls(hConsole);
	cout << endl;
	Center(119, hConsole); cout << "__________                                                      __ __   __   __                      __               \n";
	Center(119, hConsole); cout << "\\______   \\ ____  ____  ____   _____   ____   _____      _____ |__|  | |  | |__| ____   ____ _____  |__|______  ____  \n";
	Center(119, hConsole); cout << " |    |  _// __ \\/ ___\\/  _ \\ /     \\_/ __ \\  \\__  \\    /     \\|  |  | |  | |  |/  _ \\ /    \\\\__  \\ |  \\_  __ \\/ __ \\ \n";
	Center(119, hConsole); cout << " |    |   \\  ___|  \\__(  <_> )  Y Y  \\  ___/   / __ \\_ |  Y Y  \\  |  |_|  |_|  (  <_> )   |  \\/ __ \\|  ||  | \\|  ___/ \n";
	Center(119, hConsole); cout << " |______  /\\___  >___  >____/|__|_|  /\\___  > (____  / |__|_|  /__|____/____/__|\\____/|___|  (____  /__||__|   \\___  >\n";
	Center(119, hConsole);
	std::cout << "        \\/     \\/    \\/            \\/     \\/       \\/        \\/                            \\/     \\/               \\/ \n";
}

void PrintHSAscii(HANDLE &hConsole)
{
	Cls(hConsole);
	cout << endl;
	Center(70, hConsole); cout << "  ___ ___  __        __                                              \n";
	Center(70, hConsole); cout << " /   |   \\|__| ____ |  |__   ______ ____  ___________   ____   ______\n";
	Center(70, hConsole); cout << "/    ~    \\  |/ ___\\|  |  \\ /  ___// ___\\/  _ \\_  __ \\_/ __ \\ /  ___/\n";
	Center(70, hConsole); cout << "\\    Y    /  / /_/  >   Y  \\\\___ \\\\  \\__(  <_> )  | \\/\\  ___/ \\___ \\ \n";
	Center(70, hConsole); cout << " \\___|_  /|__\\___  /|___|  /____  >\\___  >____/|__|    \\___  >____  >\n";
	Center(70, hConsole); cout << "       \\/   /_____/      \\/     \\/     \\/                  \\/     \\/ \n";
}

void Cls(HANDLE &hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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