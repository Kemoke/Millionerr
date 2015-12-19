﻿#include "stdafx.h"
#include <iostream>
#include <string>
#include <tchar.h>
#include <Windows.h>
#include <conio.h>
#include "Pitanja.h" // Klase za pitanja
#include <algorithm>
#include "Helpers.h"
#include "FileIO.h"
#include "Menu.h"

using namespace std;

HANDLE hConsole;// Handle za konzolu
vector<Pitanje> pitanja;// lista pitanja

void DisplayHighScores()
{
	auto players = ReadHSFile();
	auto choice = 0;
	auto key = 0;
	auto i = 1;
	PrintHSAscii(hConsole);
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
	PrintTitleAscii(hConsole);
	string name;
	Center(40, true, hConsole); cout << "Enter your name:"; cin >> name;
}

int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// potrebno za meni
	pitanja = ParseQ();
	HideCursor(hConsole);
	entry:
	switch (MainMenu(hConsole))
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

