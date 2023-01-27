#include "FloydAlgorithm.h"

void main()
{
	/*FloydGraph FloydMap(8, 5);

	FloydMap.AddWall({ 1, 1 });
	FloydMap.AddWall({ 1, 2 });
	FloydMap.AddWall({ 1, 3 });
	FloydMap.AddWall({ 4, 0 });
	FloydMap.AddWall({ 4, 1 });
	FloydMap.AddWall({ 4, 2 });
	FloydMap.AddWall({ 4, 3 });
	FloydMap.AddWall({ 2, 3 });
	FloydMap.AddWall({ 3, 3 });
	
	FloydMap.MakeCostMap();

	FloydMap.FindPath();

	map.Print(Index(2, 2), Index(6, 2));*/

	FloydGraph map(10, 10);
	map.AddWall({ 1, 1 });
	map.AddWall({ 1, 2 });
	map.AddWall({ 1, 3 });
	map.AddWall({ 1, 4 });
	map.AddWall({ 2, 4 });
	map.AddWall({ 3, 4 });
	map.AddWall({ 4, 1 });
	map.AddWall({ 4, 2 });
	map.AddWall({ 4, 3 });
	map.AddWall({ 4, 4 });
	map.AddWall({ 4, 5 });
	map.AddWall({ 4, 6 });
	map.AddWall({ 1, 7 });
	map.AddWall({ 2, 7 });
	map.AddWall({ 3, 7 });
	map.AddWall({ 4, 7 });
	map.AddWall({ 6, 7 });
	map.AddWall({ 6, 8 });
	map.AddWall({ 6, 9 });
	map.AddWall({ 7, 7 });
	map.AddWall({ 8, 7 });
	map.AddWall({ 8, 7 });
	map.AddWall({ 6, 1 });
	map.AddWall({ 6, 2 });
	map.AddWall({ 6, 3 });
	map.AddWall({ 6, 4 });
	map.AddWall({ 6, 5 });
	map.AddWall({ 7, 1 });
	map.AddWall({ 8, 1 });
	map.AddWall({ 7, 5 });
	map.AddWall({ 8, 5 });

	map.MakeCostMap();

	map.FindPath();

	map.Print(Index(3, 5), Index(8, 2));

	return;
}