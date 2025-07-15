#pragma once
#include <vector>
using namespace std;
//Tiles
class Tiles
{
public:
	bool isMine;
	bool isRevealed;
	bool isFlagged;
	int adjacentMines;
	vector<Tiles*> adjacent;
};

