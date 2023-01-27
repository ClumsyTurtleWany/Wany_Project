#include "FloydAlgorithm.h"
#include <iostream>

FloydGraph::FloydGraph(int x, int y)
	: Width(x), Height(y)
{
	NodeCnt = Width * Height;
	MapArray.assign(Height, std::vector<int>());
	for (auto &it : MapArray)
	{
		it.assign(Width, 0);
	}
}

FloydGraph::~FloydGraph()
{
}

bool FloydGraph::AddWall(Index index)
{
	if (index.x < 0 || index.y < 0 || index.x >= Width || index.y >= Height)
	{
		return false;
	}

	Walls.push_back(index);
	MapArray[index.y][index.x] = 99999999;

	return true;
}

bool FloydGraph::isWall(int x, int y)
{
	for (auto& it : Walls)
	{
		if (it.x == x && it.y == y)
		{
			return true;
		}
	}

	return false;
}

bool FloydGraph::MakeCostMap()
{	
	for (int StartNodeIdx = 0; StartNodeIdx < NodeCnt; StartNodeIdx++)
	{
		std::vector<int> cost(NodeCnt, 99999999);
		
		int x = StartNodeIdx % Width;
		int y = StartNodeIdx / Width;

		if (!isWall(x, y))
		{		
			for (int row = -1; row <= 1; row += 1)
			{
				for (int col = -1; col <= 1; col += 1)
				{
					int newX = x + col;
					int newY = y + row;

					// Check Out of Range
					if (newX < 0 || newY < 0 || newX >= Width || newY >= Height)
					{
						continue;
					}

					// Check Wall
					if (isWall(newX, newY))
					{
						continue;
					}

					int nodeIdx = newY * Width + newX;
					if (row == 0 && col == 0) // Check Self
					{
						cost[nodeIdx] = 0;
					}
					else
					{
						cost[nodeIdx] = (abs(row) + abs(col)) > 1 ? 14 : 10;
					}
				}
			}
		}
			
		CostArray.push_back(cost);
	}

	return true;
}

bool FloydGraph::FindPath()
{
	PathArray.assign(NodeCnt, std::vector<Path>());
	for (auto& it : PathArray)
	{
		it.assign(NodeCnt, Path());
	}

	for (int row = 0; row < NodeCnt; row++)
	{
		for (int col = 0; col < NodeCnt; col++)
		{
			int x = col % Width;
			int y = col / Width;
			Index idx(x, y);
			PathArray[row][col].push_back(idx);
		}
	}

	for (int ViaNodeIdx = 0; ViaNodeIdx < NodeCnt; ViaNodeIdx++) // 경유지
	{
		for (int StartNodeIdx = 0; StartNodeIdx < NodeCnt; StartNodeIdx++) // 출발지
		{
			for (int DstNodeIdx = 0; DstNodeIdx < NodeCnt; DstNodeIdx++) // 목적지
			{
				// 경유지를 통해 목적지로 가는 코스트가 직항 코스트보다 적으면 경유하는 경로로 바꾼다.
				if (CostArray[StartNodeIdx][ViaNodeIdx] + CostArray[ViaNodeIdx][DstNodeIdx] < CostArray[StartNodeIdx][DstNodeIdx])
				{
					CostArray[StartNodeIdx][DstNodeIdx] = CostArray[StartNodeIdx][ViaNodeIdx] + CostArray[ViaNodeIdx][DstNodeIdx];
					PathArray[StartNodeIdx][DstNodeIdx].assign(PathArray[StartNodeIdx][ViaNodeIdx].begin(), PathArray[StartNodeIdx][ViaNodeIdx].end());
					//PathArray[StartNodeIdx][DstNodeIdx].insert(PathArray[StartNodeIdx][DstNodeIdx].end(), PathArray[StartNodeIdx][ViaNodeIdx].begin(), PathArray[StartNodeIdx][ViaNodeIdx].end());
					PathArray[StartNodeIdx][DstNodeIdx].insert(PathArray[StartNodeIdx][DstNodeIdx].end(), PathArray[ViaNodeIdx][DstNodeIdx].begin(), PathArray[ViaNodeIdx][DstNodeIdx].end());
				}
			}
		}
	}

	return true;
}

void FloydGraph::Print(Index start, Index dst)
{
	std::vector<std::vector<int>> PrintMap;
	PrintMap.assign(Height, std::vector<int>());
	for (auto& it : PrintMap)
	{
		it.assign(Width, 0);
	}

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (isWall(col, row))
			{
				PrintMap[row][col] = 1;
			}
		}
	}

	int StartNodeIdx = start.y * Width + start.x;
	int DstNodeIdx = dst.y * Width + dst.x;
	for (auto it : PathArray[StartNodeIdx][DstNodeIdx])
	{
		PrintMap[it.y][it.x] = 2;
	}

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (PrintMap[row][col] == 1)
			{
				std::cout << "* ";
			}
			else
			{
				std::cout << PrintMap[row][col] << " ";
			}
		}
		std::cout << std::endl;
	}
}
