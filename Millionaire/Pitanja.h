#pragma once
#include <vector>

class Jokeri
{
public:
	bool publika;
	bool prijatelj;
	bool polapola;
	Jokeri()
	{
		publika = false;
		prijatelj = false;
		polapola = false;
	}
	Jokeri(bool publika, bool prijatelj, bool polapola)
	{
		this->publika = publika;
		this->prijatelj = prijatelj;
		this->polapola = polapola;
	}
};

class Player
{
public:
	std::string name;
	int prag;
	Jokeri jokeri;
	Player()
	{
		name = "";
		prag = 0;
	}
	Player(std::string name, int prag, Jokeri jokeri)
	{
		this->name = name;
		this->prag = prag;
		this->jokeri = jokeri;
	}
};

class Odg
{
public:
	std::string Text;
	bool Tacno;
	Odg()
	{
		Text = "";
		Tacno = false;
	}
	explicit Odg(std::string odgovor)
	{
		Text = odgovor;
		Tacno = false;
	}
	void Provjera()
	{
		auto temp = Text[0];
		if (temp == '*')
			Tacno = true;
	}
};

class Pitanje {
public:
	std::string Text;
	int Tezina;
	std::vector<Odg> Odgovori;
	Pitanje()
	{
		Text = "";
		Tezina = 0;
	}
	Pitanje(std::string text, int tezina, std::vector<Odg> &odgovori)
	{
		Text = text;
		Tezina = tezina;
		Odgovori = odgovori;
	}
	void DodajOdgovor(Odg &odgovor)
	{
		Odgovori.push_back(odgovor);
	}
	void ProvjeriOdgovore()
	{
		for(auto &o : Odgovori)
		{
			o.Provjera();
		}
			
	}
};