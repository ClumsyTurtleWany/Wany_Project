#include <iostream>
#include <iomanip>

using namespace std;

void MakeMagicSquare_Odd(unsigned int **array, unsigned int size, unsigned int startNum = 1, unsigned int offset_x = 0, unsigned int offset_y = 0)
{
	//
		// 홀수 마방진은 row 0, col 센터에서 시작
		// 오른쪽 위 대각선으로 진행하며, 범위를 넘어가면 시작이나 끝 row, col로 이동 
		// 이미 채워진 자리일 경우 row 아래로
		// example - size 3
		// 0 1 0 | 0 1 0 | 0 1 0
		// 0 0 0 | 0 0 0 | 3 0 0
		// 0 0 0 | 0 0 2 | 0 0 2
		// 
		// 0 1 0 | 0 1 0 | 0 1 6
		// 3 0 0 | 3 5 0 | 3 5 0
		// 4 0 2 | 4 0 2 | 4 0 2
		// 
		// 0 1 6 | 8 1 6 | 8 1 6
		// 3 5 7 | 3 5 7 | 3 5 7
		// 4 0 2 | 4 0 2 | 4 9 2
		//

	int row = 0, col = 0;
	int length = size * size;
	int boundary_x = size + offset_x;
	int boundary_y = size + offset_y;
	for (int cnt = startNum; cnt <= length; cnt++)
	{
		if (cnt == 1)
		{
			row = offset_y + 0;
			col = offset_x + (size / 2);
		}
		else
		{
			int row_f = row - 1;
			int col_f = col + 1;

			if (row_f < 0)
			{
				row_f = boundary_y - 1;
			}

			if (col_f >= size)
			{
				col_f = offset_x;
			}

			if (array[row_f][col_f] != 0)
			{
				row_f = row + 1;
				if (row_f >= size)
				{
					row_f = 0;
				}
				col_f = col;
			}

			row = row_f;
			col = col_f;
		}

		array[row][col] = cnt;

	}
}

void MakeMagicSquare(unsigned int size)
{
	bool isExist = true;

	// Magic Square Array Initialize
	unsigned int** MagicSquare = nullptr;
	MagicSquare = new unsigned int* [size];
	for (int i = 0; i < size; i++)
	{
		MagicSquare[i] = new unsigned int[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			MagicSquare[i][j] = 0;
		}
	}

	// Case 1. Odd Number
	if ((size % 2) == 1)
	{
		//
		// 홀수 마방진은 row 0, col 센터에서 시작
		// 오른쪽 위 대각선으로 진행하며, 범위를 넘어가면 시작이나 끝 row, col로 이동 
		// 이미 채워진 자리일 경우 row 아래로
		// example - size 3
		// 0 1 0 | 0 1 0 | 0 1 0
		// 0 0 0 | 0 0 0 | 3 0 0
		// 0 0 0 | 0 0 2 | 0 0 2
		// 
		// 0 1 0 | 0 1 0 | 0 1 6
		// 3 0 0 | 3 5 0 | 3 5 0
		// 4 0 2 | 4 0 2 | 4 0 2
		// 
		// 0 1 6 | 8 1 6 | 8 1 6
		// 3 5 7 | 3 5 7 | 3 5 7
		// 4 0 2 | 4 0 2 | 4 9 2
		//

		/*int row = 0, col = 0;
		int length = size * size;
		for (int cnt = 1; cnt <= length; cnt++)
		{
			if (cnt == 1)
			{
				row = 0;
				col = size / 2;
			}
			else
			{
				int row_f = row - 1;
				int col_f = col + 1;

				if (row_f < 0)
				{
					row_f = size - 1;
				}

				if (col_f >= size)
				{
					col_f = 0;
				}

				if (MagicSquare[row_f][col_f] != 0)
				{
					row_f = row + 1;
					if (row_f >= size)
					{
						row_f = 0;
					}
					col_f = col;
				}

				row = row_f;
				col = col_f;
			}

			MagicSquare[row][col] = cnt;

		}*/

		MakeMagicSquare_Odd(MagicSquare, size);
	}
	// Case 2. Even Number (multiple of 4)
	else if((size % 4) == 0)
	{
		// 4의 배수 마방진은 row 0, col 0에서 시작
		// 정방향 모서리와 가운데 부분과  (1 : 2 : 1 비율)
		// 역방향 나머지 부분 합치면 완성
		//
		//   1   2   3   4  |     16  15  14  13  |       1  15  14   4  |
		//   5   6   7   8  |	  12  11  10   9  |		 12   6   7   9  |
		//   9  10  11  12  |	   8   7   6   5  |		  8  10  11   5  |
		//  13  14  15  16  |	   4   3   2   1  |		 13   3   2  16  |
		//

		int border_LT = size / 4;
		int border_RB = size / 4 * 3;
		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				// boundary fill 
				if (((row < border_LT || row >= border_RB) && (col < border_LT || col >= border_RB)) || 
					(((row >= border_LT) && (row < border_RB)) && ((col >= border_LT) && (col < border_RB))))
				{
					MagicSquare[row][col] = row * size + col + 1;
				}
				else
				{
					MagicSquare[row][col] = size * (size - row) - col;
				}
			}
		}	
	}
	// Case 3. Even Number (4n + 2)
	else if (((size % 4) == 2) && (size != 2))
	{
		//
		// 홀수 마방진 4개로 분리
		// example 6 * 6 
		// 
		//	[1구역]					 1 ~ (2n + 1)^2       | [2구역] 2 * (2n + 1)^2 + 1 ~ 3 * (2n + 1)^2  
		// -----------------------------------------------|-------------------------------------
		//  [3구역] 3 * (2n + 1)^2 + 1 ~ 4 * (2n + 1)^2   | [4구역] (2n + 1)^2 + 1 ~ 2 * (2n + 1)^2
		//
		// 1구역의 왼쪽 n줄 ( row[0~size / 2], col[0 ~ 1] )과 3구역의 왼쪽 n줄( row[size / 2 ~ size], col[0 ~ 1] ) 교환
		// 2구역의 오른쪽 n - 1줄 ( row[0~size / 2], col[size] )과 4구역의 오른쪽 n - 1줄 ( row[size / 2 ~ size], col[size] ) 교환 
		// 1구역과 3구역의 센터 값과 col - 1 위치 값 교환
		//

		// 3-1. Make Odd Magic Square
		/*int row = 0, col = 0;
		int halfSize = size / 2;
		int length = halfSize * halfSize;
		for (int cnt = 1; cnt <= length; cnt++)
		{
			if (cnt == 1)
			{
				row = 0;
				col = size / 2;
			}
			else
			{
				int row_f = row - 1;
				int col_f = col + 1;

				if (row_f < 0)
				{
					row_f = size - 1;
				}

				if (col_f >= size)
				{
					col_f = 0;
				}

				if (MagicSquare[row_f][col_f] != 0)
				{
					row_f = row + 1;
					if (row_f >= size)
					{
						row_f = 0;
					}
					col_f = col;
				}

				row = row_f;
				col = col_f;
			}

			MagicSquare[row][col] = cnt;

		}*/


	}
	else
	{
		isExist = false;
	}

	// Print Magic Square
	if (isExist)
	{
		int* rowSum = new int[size];
		int* colSum = new int[size];
		int diag_LB2RT = 0;
		int diag_LT2RB = 0;
		for (int i = 0; i < size; i++)
		{
			rowSum[i] = 0;
			colSum[i] = 0;
		}

		for (int i = 0; i < size; i++)
		{
			cout << std::setw(5) << " ";
			for (int j = 0; j < size; j++)
			{
				colSum[i] += MagicSquare[i][j];
				rowSum[j] += MagicSquare[i][j];
				if (i == j)
				{
					diag_LT2RB += MagicSquare[i][j];
				}
				if ((i + j) == (size - 1))
				{
					diag_LB2RT += MagicSquare[i][j];
				}

				cout << std::setw(5) << std::right << MagicSquare[i][j];
			}

			cout << " |";
			cout << std::setw(5) << std::right << colSum[i];
			cout << endl;
		}

		for (int i = 0; i < size + 1; i++)
		{
			cout << std::setw(5) << std::right << "---";
		}

		cout << endl << std::setw(5) << diag_LB2RT;
		for (int i = 0; i < size; i++)
		{
			cout << std::setw(5) << std::right << rowSum[i];
		}
		cout << "  " << std::setw(5) << diag_LT2RB;
	}
	else
	{
		cout << "Not Exist Magic Square of " << size << endl;
	}

	for (int i = 0; i < size; i++)
	{
		delete[] MagicSquare[i];
	}
	delete[] MagicSquare;
}

void main()
{
	cout << "Input Magic Square Size: ";
	int size = 0;
	cin >> size;

	MakeMagicSquare(size);
}



