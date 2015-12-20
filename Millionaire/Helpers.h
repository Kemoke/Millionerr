#pragma once
#include "Pitanja.h"
#include <consoleapi.h>
void Center(std::string item, int i);
void Center(int length);
void Center(int length, bool y);
void Center(int length, int yOffset);
void HideCursor();
void PrintTitleAscii();
void PrintHSAscii();
void Cls();
struct SortByScore
{
	bool operator() (Player L, Player R) const
	{
		return L.prag < R.prag;
	}
};