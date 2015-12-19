#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <tchar.h>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include "Pitanja.h" // Klase za pitanja
#include <algorithm>
#include "Helpers.h"
#include "FileIO.h"

using namespace std;

HANDLE hConsole;// Handle za konzolu
vector<Pitanje> pitanja;// lista pitanja

void PrintMenu(int choice)// printa meni i ASCII art :)
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

int MainMenu()// Funkcija za meni
{
	auto choice = 0;
	auto key = 0;
	CONSOLE_SCREEN_BUFFER_INFO oldSize;
	GetConsoleScreenBufferInfo(hConsole, &oldSize);
	auto columns = oldSize.srWindow.Right - oldSize.srWindow.Left + 1;
	auto rows = oldSize.srWindow.Bottom - oldSize.srWindow.Top + 1;
	PrintAscii(hConsole);
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
			PrintAscii(hConsole);
		} 
		columns = ncolumns;
		rows = nrows;
		PrintMenu(choice);
		key = _getch();
	}
	return choice;// vraca odabir
}

void DisplayHighScores()
{
	auto players = ReadHSFile();
	auto choice = 0;
	auto key = 0;
	auto i = 1;
	system("cls");
	cout << endl;
	Center(70, hConsole); cout << "  ___ ___  __        __                                              \n";
	Center(70, hConsole); cout << " /   |   \\|__| ____ |  |__   ______ ____  ___________   ____   ______\n";
	Center(70, hConsole); cout << "/    ~    \\  |/ ___\\|  |  \\ /  ___// ___\\/  _ \\_  __ \\_/ __ \\ /  ___/\n";
	Center(70, hConsole); cout << "\\    Y    /  / /_/  >   Y  \\\\___ \\\\  \\__(  <_> )  | \\/\\  ___/ \\___ \\ \n";
	Center(70, hConsole); cout << " \\___|_  /|__\\___  /|___|  /____  >\\___  >____/|__|    \\___  >____  >\n";
	Center(70, hConsole); cout << "       \\/   /_____/      \\/     \\/     \\/                  \\/     \\/ \n";
	sort(players.begin(), players.end(), SortByScore());
	for (auto p : players)
	{
		cout << i << ". " << p.name
			<< " , cash won: " << p.prag
			<< ", Jokers: fifty-fifty "; 
		if (p.jokeri.polapola) cout << "not used"; else cout << "used";
		cout << ", audience ";
		if (p.jokeri.publika) cout << "not used"; else cout << "used";
		cout << ", friend ";
		if (p.jokeri.prijatelj) cout << "not used\n"; else cout << "used\n";
		i++;
	}
	Center(4, 3, hConsole);
	SetConsoleTextAttribute(hConsole, 240);
	cout << "Back";
	SetConsoleTextAttribute(hConsole, 15);
	while (key != 13)
	{
		key = _getch();
	}
}

void Game()
{
	PrintAscii(hConsole);
	string name;
	Center(40, true, hConsole); cout << "Enter your name:"; cin >> name;
}

int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// potrebno za meni
	pitanja = ParseQ();
	HideCursor(hConsole);
	entry:
	switch (MainMenu())
	{
	case 0:
		Game();
		goto entry;
	case 1:
		DisplayHighScores();
		goto entry;
	case 2:
		return 0;
	}
}

