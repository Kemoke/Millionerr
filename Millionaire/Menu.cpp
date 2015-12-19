#include "stdafx.h"
#include <conio.h>
#include <string>
#include <consoleapi.h>
#include "Helpers.h"
#include <iostream>

using namespace std;

void PrintMenu(int choice, HANDLE &hConsole)// printa meni i ASCII art :)
{
	string menu[3] = { "Play", "Highscores", "Quit" };
	for (auto i = 0; i < 3; i++)
	{
		if (choice == i)
			SetConsoleTextAttribute(hConsole, 240);//Ako je to izabrano oboji ga
		Center(menu[i], i, hConsole);
		cout << menu[i];
		SetConsoleTextAttribute(hConsole, 15);//Ovo ostalo vrati na staru boju
	}
}

int MainMenu(HANDLE &hConsole)// Funkcija za meni
{
	auto choice = 0;
	auto key = 0;
	CONSOLE_SCREEN_BUFFER_INFO oldSize;
	GetConsoleScreenBufferInfo(hConsole, &oldSize);
	auto columns = oldSize.srWindow.Right - oldSize.srWindow.Left + 1;
	auto rows = oldSize.srWindow.Bottom - oldSize.srWindow.Top + 1;
	PrintTitleAscii(hConsole);
	while (key != 13)// key 13 = enter
	{
		if (key == 80)// key 80 = strelica dole
		{
			if (choice != 2)
				choice++;
		}
		if (key == 72)// key 72 = strelica gore
		{
			if (choice != 0)
				choice--;
		}
		CONSOLE_SCREEN_BUFFER_INFO newSize;
		GetConsoleScreenBufferInfo(hConsole, &newSize);
		auto ncolumns = newSize.srWindow.Right - newSize.srWindow.Left + 1;
		auto nrows = newSize.srWindow.Bottom - newSize.srWindow.Top + 1;
		if (ncolumns != columns || nrows != rows)
		{
			PrintTitleAscii(hConsole);
		}
		columns = ncolumns;
		rows = nrows;
		PrintMenu(choice, hConsole);
		key = _getch();
	}
	return choice;// vraca odabir
}