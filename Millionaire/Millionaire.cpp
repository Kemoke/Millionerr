// Millionaire.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <tchar.h>
#include <conio.h>
#include <Windows.h>
#include "Pitanja.h" // Klase za pitanja

using namespace std;

ifstream File;// File za pitanja
HANDLE hConsole;// Handle za konzolu
vector<Pitanje> pitanja;// lista pitanja

void ParseQ()// Cita pitanja i odgovore iz fajla
{
	// format pitanja u fileu = "pitanje tezina odg1 odg2 odg3 odg4" (staviti * ispred tacnog odg)
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
}

void PrintMenu(int choice)// printa meni i ASCII art :)
{
	string menu[3] = { "Become a millionaire!", "Highscores", "Quit" };
	system("cls");
	cout << "__________                                                      __ __   __   __                      __               \n";
	cout << "\\______   \\ ____  ____  ____   _____   ____   _____      _____ |__|  | |  | |__| ____   ____ _____  |__|______  ____  \n";
	cout << " |    |  _// __ \\/ ___\\/  _ \\ /     \\_/ __ \\  \\__  \\    /     \\|  |  | |  | |  |/  _ \\ /    \\\\__  \\ |  \\_  __ \\/ __ \\ \n";
	cout << " |    |   \\  ___|  \\__(  <_> )  Y Y  \\  ___/   / __ \\_ |  Y Y  \\  |  |_|  |_|  (  <_> )   |  \\/ __ \\|  ||  | \\|  ___/ \n";
	cout << " |______  /\\___  >___  >____/|__|_|  /\\___  > (____  / |__|_|  /__|____/____/__|\\____/|___|  (____  /__||__|   \\___  >\n";
	cout << "        \\/     \\/    \\/            \\/     \\/       \\/        \\/                            \\/     \\/               \\/ \n";
	for (auto i = 0; i < 3; i++)
	{
		if (choice == i)
			SetConsoleTextAttribute(hConsole, 240);//Ako je to izabrano oboji ga
		cout << menu[i] << endl;
		SetConsoleTextAttribute(hConsole, 15);//Ovo ostalo vrati na staru boju
	}
}

int MainMenu()// Funkcija za meni
{
	auto choice = 0;
	int key = 0;
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
		PrintMenu(choice);
		key = _getch();
	}
	return choice;// vraca odabir
}

int main()
{
	File.open("Pitanja.txt");
	ParseQ();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// potrebno za meni
	MainMenu();
    return 0;
}

