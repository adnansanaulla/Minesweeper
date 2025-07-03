#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Random.h"
#include "Tiles.h"
using namespace std;
class Board
{
public:
	static void Load(const string& someFile);
	static int dimensions[3];
	static vector<vector<Tiles>> MineField();
	static void adjacentReveal(Tiles* tile);
	static vector<vector<Tiles>> Test(const string& someFile);
};

