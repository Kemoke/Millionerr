#pragma once
#include "Pitanja.h"
void Center(std::string item, int i, HANDLE hConsole);
void Center(int length, HANDLE hConsole);
void Center(int length, bool y, HANDLE hConsole);
void Center(int length, int yOffset, HANDLE hConsole);
void HideCursor(HANDLE hConsole);
void PrintTitleAscii(HANDLE hConsole);
void PrintHSAscii(HANDLE hConsole);
void Cls(HANDLE hConsole);
struct SortByScore
{
	bool operator() (Player L, Player R) const
	{
		return L.prag < R.prag;
	}
};