#include "stdafx.h"
#include <iostream>
#include <string>
#include <tchar.h>
#include <Windows.h>
#include <conio.h>
#include "Pitanja.h" // Klase za pitanja
#include "Helpers.h"
#include "FileIO.h"
#include "Menu.h"

using namespace std;

void DisplayHighScores()
{
	auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	auto players = ReadHSFile();
	auto key = 0;
	auto i = 1;
	PrintHSAscii();
	for (auto p : players)
	{
		cout << i << ". " << p.name
			<< ", cash won: " << p.prag
			<< ", Jokers: fifty-fifty "; 
		if (p.jokeri.polapola) cout << "not used"; else cout << "used";
		cout << ", audience ";
		if (p.jokeri.publika) cout << "not used"; else cout << "used";
		cout << ", friend ";
		if (p.jokeri.prijatelj) cout << "not used\n"; else cout << "used\n";
		i++;
		if (i == 10)
			break;
	}
	Center(4, 3);
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
	PrintTitleAscii();
	auto pitanja = ParseQ();
	string name;
	Center(40, true); cout << "Enter your name:"; cin >> name;
}

int main()
{
	// potrebno za meni
	HideCursor();
	entry:
	switch (MainMenu())
	{
	case 0:
		Game();
		break;
	case 1:
		DisplayHighScores();
		break;
	case 2:
		return 0;
	}
	goto entry;
}

