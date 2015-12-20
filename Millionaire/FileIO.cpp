#include "stdafx.h"
#include <fstream>
#include "Pitanja.h"
#include <string>
#include "FileIO.h"
#include <algorithm>
#include "Helpers.h"

using namespace std;

vector<Pitanje> ParseQ()// Cita pitanja i odgovore iz fajla
{
	// format pitanja u fileu = "pitanje tezina odg1 odg2 odg3 odg4" (staviti * ispred tacnog odg)
	vector<Pitanje> pitanja;
	ifstream File("Pitanja.txt");
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
	return pitanja;
}

vector<Player> ReadHSFile()
{
	//HS file format = "name br.pitanja polapola prijatelj publika" (jokeri su ispisani ko 0/1)
	ifstream File("Scores.txt");
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
	sort(players.begin(), players.end(), SortByScore());
	return players;
}

void WriteHSFile(Player player)
{
	ofstream File("Scores.txt", ios::app);
	File << player.name << " " << player.prag << " " << player.jokeri.polapola << " " << player.jokeri.prijatelj << " " << player.jokeri.publika << endl;
	File.close();
}