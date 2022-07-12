#include <iostream>
#include <iomanip>

using namespace std;
int g_HanoiCounter = 0;

void CalcHanoiTower(unsigned int ring, char StartPoint, char TempPoint, char LastPoint)
{
	// example - Height 3
	// 
	//			ring 1 Start -> Last : A -> C 
	//		ring 2 Start -> Temp : A -> B
	//			ring 1 Last -> Temp : C -> B
	//	ring 3 Start -> Last : A -> C
	//			ring 1 Temp -> Start : B -> A
	//		ring 2 Temp -> Last : B -> C
	//			ring 1 Start -> Last : A -> C

	// example - Height 4
	// 
	//				ring 1 Start -> Temp : A -> B 
	//			ring 2 Start -> Last : A -> C
	//				ring 1 Temp -> Last : B -> C
	//		ring 3 Start -> Temp : A -> B
	//				ring 1 Last -> Start : C -> A
	//			ring 2 Last -> Temp : C -> B
	//				ring 1 Start -> Temp : A -> B
	//	ring 4 Start -> Last : A -> C
	//				ring 1 Temp -> Last : B -> C
	//			ring 2 Temp -> Start : B -> A
	//				ring 1 Last -> Start : C -> A
	//		ring 3 Temp -> Last : B -> C
	//				ring 1 Start -> Temp : A -> B
	//			ring 2 Start -> Last : A -> C
	//				ring 1 Temp -> Last : B -> C
	// 
	// 
	// count: 2^n - 1

	if (ring == 1)
	{
		cout << "[" << g_HanoiCounter << "] " << "ring " << ring << " [" << StartPoint << " -> " << LastPoint << "]" << endl;
		g_HanoiCounter++;
	}
	else
	{
		CalcHanoiTower(ring - 1, StartPoint, LastPoint, TempPoint);
		cout << "[" << g_HanoiCounter << "] " << "ring " << ring << " [" << StartPoint << " -> " << LastPoint << "]" << endl;
		g_HanoiCounter++;
		CalcHanoiTower(ring - 1, TempPoint, StartPoint, LastPoint);
	}

}


void main()
{
	// Calc Hanoi Tower
	cout << "Input Tower Height: ";
	unsigned int towerHeight = 0;
	cin >> towerHeight;

	cout << "Tower Height: " << towerHeight << endl;

	CalcHanoiTower(towerHeight, 'A', 'B', 'C');

	cout << "Total Count: " << g_HanoiCounter;
}

