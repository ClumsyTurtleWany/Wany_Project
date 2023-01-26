#pragma once

#include <vector>
#include <set>

struct Index
{
	int x = 0;
	int y = 0;

	bool operator ==(Index idx)
	{
		if (x != idx.x)
		{
			return false;
		}

		if (y != idx.y)
		{
			return false;
		}

		return true;
	}
};

struct Node
{
	int G = 0;
	int H = 0;
	Index Idx;
	Node* Parent = nullptr;

	int GetScore()
	{
		return G + H;
	}
};

class AStarMap
{
private:
	int Width = 0;
	int Height = 0;
	int** MapArray = nullptr;
	std::vector<Index> Walls;
	std::vector<Index> Path;

public:
	AStarMap(int x, int y);
	~AStarMap();

public:
	bool AddWall(Index index);
	bool FindPath(Index start, Index dst);

public:
	void Print();
};

