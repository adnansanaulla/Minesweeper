#include "Board.h"
//Board header
int Board::dimensions[3];
void Board::Load(const string& someFile)
{
	ifstream file;
	file.open(someFile);
	string line;
	getline(file, line);
	Board::dimensions[0] = stoi(line) * 32;
	getline(file, line);
	Board::dimensions[1] = (stoi(line) * 32) + 100;
	getline(file, line);
	Board::dimensions[2] = stoi(line);
}
vector<vector<Tiles>> Board::MineField()
{
	int width = Board::dimensions[0] / 32;
	int length = (Board::dimensions[1] - 100) / 32;
	vector<vector<Tiles>> minefield(length, vector<Tiles>(width));
	int count = 0;
	while (count < dimensions[2])
	{
		int x = Random::Int(0, width - 1);
		int y = Random::Int(0, length - 1);
		if (minefield[y][x].isMine == false)
		{
			minefield[y][x].isMine = true;
			count += 1;
		}
	}

	for (int y = 0; y < length; y++)
	{
		for (int x = 0; x < width; x++)
		{
			for (int x2 = -1; x2 < 2; x2++)
			{
				for (int y2 = -1; y2 < 2; y2++)
				{
					if (x2 == 0 && y2 == 0)
					{
						continue;
					}
					int x3 = x + x2;
					int y3 = y + y2;
					if (x3 >= 0 && x3 < width && y3 >= 0 && y3 < length)
					{
						minefield[y][x].adjacent.push_back(&minefield[y3][x3]);
					}
				}
			}
		}
	}

	for (int y = 0; y < length; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (minefield[y][x].isMine)
			{
				continue;
			}
			int count = 0;
			for (unsigned int i = 0; i < minefield[y][x].adjacent.size(); i++)
			{
				if (minefield[y][x].adjacent[i]->isMine)
				{
					count++;
				}
			}
			minefield[y][x].adjacentMines = count;
		}
	}
	return minefield;
}

void Board::adjacentReveal(Tiles* tile)
{
	if (tile->isRevealed || tile->isFlagged)
	{
		return;
	}
	tile->isRevealed = true;
	if (tile->adjacentMines == 0 && tile->isMine == false)
	{
		for (int i = 0; i < tile->adjacent.size(); i++)
		{
			if (tile->adjacent[i]->isMine == false)
			{
				adjacentReveal(tile->adjacent[i]);
			}
		}
	}
}
vector<vector<Tiles>> Board::Test(const string& someFile)
{
	ifstream file;
	file.open(someFile);
	string line;
	int ycount = 0;
	int xcount = 0;
	while (getline(file, line))
	{
		ycount += 1;
		istringstream stream(line);
		xcount = line.length();
	}
	file.close();
	vector<vector<Tiles>> minefield(ycount, vector<Tiles>(xcount));
	file.open(someFile);
	int count = 0;
	while (getline(file, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '1')
			{
				minefield[count][i].isMine = true;
			}
			else
			{
				minefield[count][i].isMine = false;
			}
		}
		count += 1;
	}

	for (int y = 0; y < ycount; y++)
	{
		for (int x = 0; x < xcount; x++)
		{
			for (int x2 = -1; x2 < 2; x2++)
			{
				for (int y2 = -1; y2 < 2; y2++)
				{
					if (x2 == 0 && y2 == 0)
					{
						continue;
					}
					int x3 = x + x2;
					int y3 = y + y2;
					if (x3 >= 0 && x3 < xcount && y3 >= 0 && y3 < ycount)
					{
						minefield[y][x].adjacent.push_back(&minefield[y3][x3]);
					}
				}
			}
		}
	}
	for (int y = 0; y < ycount; y++)
	{
		for (int x = 0; x < xcount; x++)
		{
			if (minefield[y][x].isMine)
			{
				continue;
			}
			int count2 = 0;
			for (unsigned int i = 0; i < minefield[y][x].adjacent.size(); i++)
			{
				if (minefield[y][x].adjacent[i]->isMine)
				{
					count2++;
				}
			}
			minefield[y][x].adjacentMines = count2;
		}
	}
	return minefield;
}