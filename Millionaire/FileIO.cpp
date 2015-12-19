#include <fstream>
#include "Pitanja.h"
#include <string>

using namespace std;

vector<Pitanje> ParseQ()// Cita pitanja i odgovore iz fajla
{
	// format pitanja u fileu = "pitanje tezina odg1 odg2 odg3 odg4" (staviti * ispred tacnog odg)
	vector<Pitanje> pitanja;
	fstream File;
	File.open("Pitanja.txt", std::fstream::in);
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
	fstream File;
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