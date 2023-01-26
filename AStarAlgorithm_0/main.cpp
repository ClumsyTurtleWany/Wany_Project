#include "AStarAlgorithm.h"

void main()
{
	/*AStarMap map(8, 5);
	map.AddWall({ 1, 1 });
	map.AddWall({ 1, 2 });
	map.AddWall({ 1, 3 });
	map.AddWall({ 4, 0 });
	map.AddWall({ 4, 1 });
	map.AddWall({ 4, 2 });
	map.AddWall({ 4, 3 });
	map.AddWall({ 2, 3 });
	map.AddWall({ 3, 3 });

	map.FindPath({ 2, 2 }, { 6, 2 });
	
	map.Print();*/

	AStarMap map(10, 10);
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

	map.FindPath({ 3, 5 }, { 7, 3 });

	map.Print();

	return;

}