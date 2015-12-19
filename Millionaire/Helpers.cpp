#include <consoleapi.h>
#include <string>
#include <iostream>

using namespace std;

void Center(string item, int i, HANDLE &hConsole)
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

void PrintAscii(HANDLE &hConsole)
{
	system("cls");
	cout << endl;
	Center(119, hConsole); cout << "__________                                                      __ __   __   __                      __               \n";
	Center(119, hConsole); cout << "\\______   \\ ____  ____  ____   _____   ____   _____      _____ |__|  | |  | |__| ____   ____ _____  |__|______  ____  \n";
	Center(119, hConsole); cout << " |    |  _// __ \\/ ___\\/  _ \\ /     \\_/ __ \\  \\__  \\    /     \\|  |  | |  | |  |/  _ \\ /    \\\\__  \\ |  \\_  __ \\/ __ \\ \n";
	Center(119, hConsole); cout << " |    |   \\  ___|  \\__(  <_> )  Y Y  \\  ___/   / __ \\_ |  Y Y  \\  |  |_|  |_|  (  <_> )   |  \\/ __ \\|  ||  | \\|  ___/ \n";
	Center(119, hConsole); cout << " |______  /\\___  >___  >____/|__|_|  /\\___  > (____  / |__|_|  /__|____/____/__|\\____/|___|  (____  /__||__|   \\___  >\n";
	Center(119, hConsole);
	std::cout << "        \\/     \\/    \\/            \\/     \\/       \\/        \\/                            \\/     \\/               \\/ \n";
}