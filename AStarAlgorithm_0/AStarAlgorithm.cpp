#include "AStarAlgorithm.h"
#include <iostream>

AStarMap::AStarMap(int x, int y)
	: Width(x), Height(y)
{
	MapArray = new int*[Height];
	for (int row = 0; row < Height; row++)
	{
		MapArray[row] = new int[Width];
	}

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			MapArray[row][col] = 0;
		}
	}

}

AStarMap::~AStarMap()
{
	for (int row = 0; row < Height; row++)
	{
		delete[] MapArray[row];
	}
	delete MapArray;
}

bool AStarMap::AddWall(Index index)
{
	if (index.x < 0 || index.y < 0 || index.x >= Width || index.y >= Height)
	{
		return false;
	}

	Walls.push_back(index);
	MapArray[index.y][index.x] = 1;

	return true;
}

bool AStarMap::FindPath(Index start, Index dst)
{
	std::set<Node*> OpenSet;
	std::set<Node*> ClosedSet;
	Node* currentNode = new Node;
	currentNode->Idx.x = start.x;
	currentNode->Idx.y = start.y;
	OpenSet.insert(currentNode);

	while (!OpenSet.empty())
	{
		currentNode = *OpenSet.begin();
		for (auto Path : OpenSet)
		{
			if (Path->GetScore() <= currentNode->GetScore())
			{
				currentNode = Path;
			}
		}

		if (currentNode->Idx == dst)
		{
			break;
		}

		ClosedSet.insert(currentNode);
		OpenSet.erase(currentNode);

		// Search 8 Direction
		for (int row = -1; row <= 1; row += 1)
		{
			for (int col = -1; col <= 1; col += 1)
			{
				// 자기 자신 건너 뜀.
				if ((row == 0) && (col == 0))
				{
					continue;
				}

				int x = currentNode->Idx.x + col;
				int y = currentNode->Idx.y + row;
				// Out of Range
				if (x < 0 || y < 0 || x >= Width || y >= Height)
				{
					continue;
				}

				// 벽
				if (MapArray[y][x] == 1)
				{
					continue;
				}

				// 이미 방문한 노드인지 확인
				bool isClosed = false;
				for (auto it : ClosedSet)
				{
					if ((it->Idx.x == x) && (it->Idx.y == y))
					{
						isClosed = true;
						break;
					}
				}

				if (isClosed)
				{
					continue;
				}

				// 열려있는 노드와 스코어 비교하여 경로 획득.
				int newCost = ((abs(row) + abs(col)) > 1) ? 14 : 10;
				int totalCost = currentNode->G + newCost;
				bool isOpened = false;
				for (auto it : OpenSet)
				{
					if ((it->Idx.x == x) && (it->Idx.y == y))
					{
						isOpened = true;
						if (totalCost < it->G)
						{
							it->Parent = currentNode;
							it->G = totalCost;
						}
						break;
					}
				}

				if (isOpened)
				{
					continue;
				}

				// 새 경로 추가.
				Node* newPathNode = new Node;
				newPathNode->Parent = currentNode;
				newPathNode->G = totalCost;
				newPathNode->H = sqrt(pow((x - dst.x), 2) + pow((y - dst.y), 2)) * 10;
				newPathNode->Idx.x = x;
				newPathNode->Idx.y = y;

				OpenSet.insert(newPathNode);
			}
		}
	}

	while (currentNode != nullptr)
	{
		int x = currentNode->Idx.x;
		int y = currentNode->Idx.y;
		MapArray[y][x] = 2;
		currentNode = currentNode->Parent;
	}

	return true;
}

void AStarMap::Print()
{
	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			std::cout << MapArray[row][col] << " ";
		}
		std::cout << std::endl;
	}
}
