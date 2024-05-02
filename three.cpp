#include "three.h"
#include "StringHelpers.h"
#include <unordered_set>

bool IsASCIINumber(char c)
{
	return c >= 48 && c <= 57;
}

bool IsCorrectSymbol(char c)
{
	return !IsASCIINumber(c) && c != '.';
}

bool IsCorrectGearSymbol(char c)
{
	return c == '*';
}

bool isNumber(const string& s) 
{
	if (s.empty()) return false;

	for (char c : s)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}

	return true;
}

int Traverse(char** inputGrid, int m, int startX, int startY)
{
	string left = "";
	string right = "";

	if (IsASCIINumber(inputGrid[startX][startY]))
	{
		left += inputGrid[startX][startY];
	}
	else
	{
		// not a number
		return -1;
	}

	// Get all left numbers
	for (int j = startY - 1; j >= 0; j--)
	{
		char c = inputGrid[startX][j];
		if (IsASCIINumber(c))
		{
			string cString;
			cString += c;

			left.insert(0, cString);
		}
		else
		{
			// No longer a number
			break;
		}
	}

	// Get all Right numbers
	for (int j = startY + 1; j < m; j++)
	{
		char c = inputGrid[startX][j];
		if (IsASCIINumber(c))
		{
			right.push_back(c);
		}
		else
		{
			// No longer a number
			break;
		}
	}

	left.append(right);

	return isNumber(left) ? stoi(left) : -1;
}

void three::Run(string input)
{
	int n = 0;
	int m = 0;
	char** inputGrid = FileReader::SplitStringBy2DGrid(input, n, m);

	vector<int> partNumbers;
	
	for (int i = 0; i < n; i++)
	{
		string current;

		for (int j = 0; j < m; j++)
		{
			char c = inputGrid[i][j];
			current += c;

			if (IsCorrectSymbol(c))
			{
				// Try get upper number
				int upperRight = Traverse(inputGrid, m, i - 1, j + 1);
				int upperLeft = Traverse(inputGrid, m, i - 1, j - 1);
				int upper = Traverse(inputGrid, m, i - 1, j);

				DEBUG_LOG(upperRight);
				DEBUG_LOG(upperLeft);
				DEBUG_LOG(upper);

				if (upper >= 0)
				{
					partNumbers.push_back(upper);
				}
				else
				{
					if (upperRight >= 0)
					{
						partNumbers.push_back(upperRight);
					}

					if (upperLeft >= 0)
					{
						partNumbers.push_back(upperLeft);
					}
				}

				// Try get lower number
				int lowerRight = Traverse(inputGrid, m, i + 1, j + 1);
				int lowerLeft = Traverse(inputGrid, m, i + 1, j - 1);
				int lower = Traverse(inputGrid, m, i + 1, j);

				if (lower >= 0)
				{
					partNumbers.push_back(lower);
				}
				else
				{
					if (lowerRight >= 0)
					{
						partNumbers.push_back(lowerRight);
					}

					if (lowerLeft >= 0)
					{
						partNumbers.push_back(lowerLeft);
					}
				}

				DEBUG_LOG(lowerRight);
				DEBUG_LOG(lowerLeft);
				DEBUG_LOG(lower);

				// Try get left
				int left = Traverse(inputGrid, m, i, j - 1);

				if (left >= 0)
				{
					partNumbers.push_back(left);
				}

				// Try get right
				int right = Traverse(inputGrid, m, i, j + 1);

				if (right >= 0)
				{
					partNumbers.push_back(right);
				}

				DEBUG_LOG(left);
				DEBUG_LOG(right);
			}
		}
	}

	int sum = 0;
	DEBUG_LOG("checking sum");
	for (int numb : partNumbers)
	{
		sum += numb;
		DEBUG_LOG(numb);
	}

	DEBUG_LOG_1("sum of numbers: ", sum);

	for (int i = 0; i < n; i++) 
	{
		delete[] inputGrid[i];
	}
	delete[] inputGrid;
}

void three::Run_2(string input)
{
	int n = 0;
	int m = 0;
	char** inputGrid = FileReader::SplitStringBy2DGrid(input, n, m);

	vector<int> partNumbers;

	for (int i = 0; i < n; i++)
	{
		string current;

		for (int j = 0; j < m; j++)
		{
			char c = inputGrid[i][j];
			current += c;

			if (IsCorrectGearSymbol(c))
			{
				vector<int> currentPartNumbers;

				// Try get upper number
				int upperRight = Traverse(inputGrid, m, i - 1, j + 1);
				int upperLeft = Traverse(inputGrid, m, i - 1, j - 1);
				int upper = Traverse(inputGrid, m, i - 1, j);

				if (upper >= 0)
				{
					currentPartNumbers.push_back(upper);
				}
				else
				{
					if (upperRight >= 0)
					{
						currentPartNumbers.push_back(upperRight);
					}

					if (upperLeft >= 0)
					{
						currentPartNumbers.push_back(upperLeft);
					}
				}

				// Try get lower number
				int lowerRight = Traverse(inputGrid, m, i + 1, j + 1);
				int lowerLeft = Traverse(inputGrid, m, i + 1, j - 1);
				int lower = Traverse(inputGrid, m, i + 1, j);

				if (lower >= 0)
				{
					currentPartNumbers.push_back(lower);
				}
				else
				{
					if (lowerRight >= 0)
					{
						currentPartNumbers.push_back(lowerRight);
					}

					if (lowerLeft >= 0)
					{
						currentPartNumbers.push_back(lowerLeft);
					}
				}

				// Try get left
				int left = Traverse(inputGrid, m, i, j - 1);

				if (left >= 0)
				{
					currentPartNumbers.push_back(left);
				}

				// Try get right
				int right = Traverse(inputGrid, m, i, j + 1);

				if (right >= 0)
				{
					currentPartNumbers.push_back(right);
				}

				// Exactly 2 numbers is a gear
				if (currentPartNumbers.size() == 2)
				{
					int ratio = currentPartNumbers[0] * currentPartNumbers[1];
					partNumbers.push_back(ratio);
				}
			}
		}
	}

	int sum = 0;
	DEBUG_LOG("checking sum");
	for (int numb : partNumbers)
	{
		sum += numb;
		DEBUG_LOG(numb);
	}

	DEBUG_LOG_1("sum of numbers: ", sum);

	for (int i = 0; i < n; i++)
	{
		delete[] inputGrid[i];
	}
	delete[] inputGrid;
}
