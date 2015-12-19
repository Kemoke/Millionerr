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

using namespace std;

fstream File;// File za pitanja
HANDLE hConsole;// Handle za konzolu
vector<Pitanje> pitanja;// lista pitanja

void ParseQ()// Cita pitanja i odgovore iz fajla
{
	// format pitanja u fileu = "pitanje tezina odg1 odg2 odg3 odg4" (staviti * ispred tacnog odg)
	File.open("Pitanja.txt", fstream::in);
	string buffer;
	while (File >> buffer)// cita text pitanja
	{
		Pitanje temp;// pravi temp pitanje
		temp.Text = buffer;// ubacuje text pitanja
		File >> temp.Tezina;// cita i ubacuje tezinu pitanja
		for (auto i = 0; i < 4; i++)
		{
			File >> buffer;// cita odgovor
			temp.Odgovori.push_back(Odg(buffer));// ubacuje odgovor u pitanje
		}
		temp.ProvjeriOdgovore();// provjerava koji je odgovor tacan
		pitanja.push_back(temp);// ubacuje pitanje u listu
	}
	File.close();
}

void Center(string item, int i) 
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	auto rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - strlen(item.c_str())) / 2;
	csbi.dwCursorPosition.Y = (rows / 2) - 2 + 2*i;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void Center(int length)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X = (columns - length) / 2;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
void Center(int length, bool y)
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

void Center(int length, int yOffset)
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

void PrintMenu(int choice)// printa meni i ASCII art :)
{
	string menu[3] = { "Play", "Highscores", "Quit" };
	for (auto i = 0; i < 3; i++)
	{
		if (choice == i)
			SetConsoleTextAttribute(hConsole, 240);//Ako je to izabrano oboji ga
		Center(menu[i], i);
		cout << menu[i];
		SetConsoleTextAttribute(hConsole, 15);//Ovo ostalo vrati na staru boju
	}
}

void PrintAscii()
{
	system("cls");
	cout << endl;
	Center(119); cout << "__________                                                      __ __   __   __                      __               \n";
	Center(119); cout << "\\______   \\ ____  ____  ____   _____   ____   _____      _____ |__|  | |  | |__| ____   ____ _____  |__|______  ____  \n";
	Center(119); cout << " |    |  _// __ \\/ ___\\/  _ \\ /     \\_/ __ \\  \\__  \\    /     \\|  |  | |  | |  |/  _ \\ /    \\\\__  \\ |  \\_  __ \\/ __ \\ \n";
	Center(119); cout << " |    |   \\  ___|  \\__(  <_> )  Y Y  \\  ___/   / __ \\_ |  Y Y  \\  |  |_|  |_|  (  <_> )   |  \\/ __ \\|  ||  | \\|  ___/ \n";
	Center(119); cout << " |______  /\\___  >___  >____/|__|_|  /\\___  > (____  / |__|_|  /__|____/____/__|\\____/|___|  (____  /__||__|   \\___  >\n";
	Center(119); cout << "        \\/     \\/    \\/            \\/     \\/       \\/        \\/                            \\/     \\/               \\/ \n";
}

int MainMenu()// Funkcija za meni
{
	auto choice = 0;
	auto key = 0;
	CONSOLE_SCREEN_BUFFER_INFO oldSize;
	GetConsoleScreenBufferInfo(hConsole, &oldSize);
	auto columns = oldSize.srWindow.Right - oldSize.srWindow.Left + 1;
	auto rows = oldSize.srWindow.Bottom - oldSize.srWindow.Top + 1;
	PrintAscii();
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
			PrintAscii();
		} 
		columns = ncolumns;
		rows = nrows;
		PrintMenu(choice);
		key = _getch();
	}
	return choice;// vraca odabir
}

vector<Player> ReadHSFile()
{
	//HS file format = "name br.pitanja polapola prijatelj publika" (jokeri su ispisani ko 0/1)
	File.open("Scores.txt", fstream::in);
	vector<Player> players;
	string nameBuf;
	int pragBuf;
	Jokeri jokeri;
	while (File >> nameBuf)
	{
		File >> pragBuf;
		File >> jokeri.polapola;
		File >> jokeri.prijatelj;
		File >> jokeri.publika;
		players.push_back(Player(nameBuf, pragBuf, jokeri));
	}
	File.close();
	return players;
}

void DisplayHighScores()
{
	auto players = ReadHSFile();
	auto choice = 0;
	auto key = 0;
	auto i = 1;
	system("cls");
	cout << endl;
	Center(70); cout << "  ___ ___  __        __                                              \n";
	Center(70); cout << " /   |   \\|__| ____ |  |__   ______ ____  ___________   ____   ______\n";
	Center(70); cout << "/    ~    \\  |/ ___\\|  |  \\ /  ___// ___\\/  _ \\_  __ \\_/ __ \\ /  ___/\n";
	Center(70); cout << "\\    Y    /  / /_/  >   Y  \\\\___ \\\\  \\__(  <_> )  | \\/\\  ___/ \\___ \\ \n";
	Center(70); cout << " \\___|_  /|__\\___  /|___|  /____  >\\___  >____/|__|    \\___  >____  >\n";
	Center(70); cout << "       \\/   /_____/      \\/     \\/     \\/                  \\/     \\/ \n";
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
	PrintAscii();
	string name;
	Center(40, true); cout << "Enter your name:"; cin >> name;
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// potrebno za meni
	ParseQ();
	HideCursor();
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

