#include "FloydAlgorithm.h"

void main()
{
	FloydGraph FloydMap(8, 5);

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

	FloydMap.Print(Index(2, 2), Index(6, 2));


	return;
}