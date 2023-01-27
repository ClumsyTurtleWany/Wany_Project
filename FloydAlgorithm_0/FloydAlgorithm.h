#pragma once
#include <vector>

struct Index
{
	int x = 0;
	int y = 0;

	Index(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

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

class FloydGraph
{
private:
	int Width = 0;
	int Height = 0;
	int NodeCnt = 0;
	using Array2D = std::vector<std::vector<int>>;
	Array2D MapArray;
	Array2D CostArray;
	std::vector<Index> Walls;

	using Path = std::vector<Index>;
	using PathArray2D = std::vector<std::vector<Path>>;
	PathArray2D PathArray;

public:
	FloydGraph(int x, int y);
	~FloydGraph();

public:
	bool AddWall(Index index);
	bool isWall(int x, int y);
	bool MakeCostMap();
	bool FindPath();

public:
	void Print(Index start, Index dst);
};

