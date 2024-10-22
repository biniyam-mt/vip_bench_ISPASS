#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <thread>

using namespace std;

#include "../config.h"
#include "utils.h"

// `M × N` matrix
#define M 10
#define N 10

// Used to find adjacent values of an element in a matrix
int row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int col[] = {-1, 0, 1, -1, 1, -1, 0, 1};
vector<int> primeNum(M *N, 0);
#ifndef VIP_NA_MODE
struct node
{
	string sub_group = "-"; // points to a value in the array called group which is created below
	string group = "-";
	VIP_ENCBOOL assigned = false;
};

// same size as the given matrix
// An element with location(x,y) here represents the element(x,y) in the input matrix
// Holds the groups of the elements in the input matrix
// node struct_mat[M][N];

// Can use this function to see the groups and subgroup
void printStructMatrix(node struct_mat[M][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(6) << "(" << VIP_DEC(struct_mat[i][j].sub_group) << " : " << VIP_DEC(struct_mat[i][j].group) << "),";
		}
		cout << endl;
	}
}

vector<int> split(string target, string delimiter)
{
	vector<int> components;
	if (!target.empty())
	{
		size_t start = 0;
		do
		{
			const size_t index = target.find(delimiter, start);
			if (index == string::npos)
			{
				break;
			}
			const size_t length = index - start;
			string found2 = target.substr(start, length);
			if (found2 != "")
				components.push_back(stoi(found2));
			start += (length + delimiter.size());
		} while (true);
		string found = target.substr(start);
		if (found != "")
			components.push_back(stoi(found));
	}

	return components;
}

string sortGroup(string text)
{
	string res = "-";
	vector<int> numbers = split(text, "-");
	sort(numbers.begin(), numbers.end());

	for (int i = 0; i < numbers.size(); i++)
	{
		res += to_string(numbers[i]) + "-";
	}

	return res;
}
bool isFound(string source, string text, string pattern, string idx = "-")
{
	string sortedText = sortGroup(text);
	string sortedPattern = sortGroup(pattern);
	bool isIn = sortedText.find(sortedPattern) != std::string::npos;

	if (!isIn && source == "concat")
	{
		cout << "idx: " << idx << endl;
		cout << "text: " << text << endl;
		cout << "pattern: " << pattern << endl;
		cout << "is Found: " << isIn << "\n\n";
	}

	return isIn;
}
// checks if small is a factor of big
VIP_ENCBOOL isFactor(VIP_ENCDOUBLE big, VIP_ENCDOUBLE small)
{
	VIP_ENCDOUBLE temp = big / small;
	VIP_ENCINT temp1 = big / small;
	return (temp - temp1) == 0;
}
VIP_ENCBOOL isFactor2(VIP_ENCLONG big, VIP_ENCLONG small)
{

	return big % small == 0;
}

// generates primeNumbers in a random way
// void generatePrime()
// {
// 	int index = 0;
// 	vector<int> out(M * N, 0);
// 	bool found = false;
// 	for (int i = 2; true; i++)
// 	{
// 		for (int j = 0; j < M * N; j++)
// 		{
// 			if (primeNum[j] == 0)
// 			{
// 				break;
// 			}
// 			if (i % primeNum[j] == 0)
// 			{
// 				found = true;
// 				break;
// 			}
// 		}
// 		if (!found)
// 		{
// 			primeNum[index] = i;
// 			index++;
// 			if (index == M * N)
// 				break;
// 		}
// 		found = false;
// 	}
// 	index = rand() % (M * N);
// 	for (int i = 0; i < M * N; i++)
// 	{
// 		while (out[index] != 0)
// 		{
// 			index = rand() % (M * N);
// 		}
// 		out[index] = primeNum[i];
// 	}
// 	primeNum = out;
// }
#endif

void floodfill(VIP_ENCCHAR mat[M][N], VIP_ENCINT x, VIP_ENCINT y, VIP_ENCCHAR replacement)
{
	VIP_ENCINT countP = 0;
	VIP_ENCINT place = 1;
	int groupIndex = 0;
	node struct_mat[M][N];

#ifndef VIP_NA_MODE
#define SAFELOC(X, Y) ((X) >= 0 && (X) < M && (Y) >= 0 && (Y) < N)

	// Used for the condition value in VIP_CMOV
	VIP_ENCBOOL condition = false;
	// Set to true if at least one element adjacent to the
	// element in question has been assigned and has the same color
	VIP_ENCBOOL found = false;
	string temp = "";

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			auto cell = &(struct_mat[i][j]);
			for (int k = 0; k < 8; k++)
			{
				if (SAFELOC(i + row[k], j + col[k]))
				{
					auto adjCell = &(struct_mat[i + row[k]][j + col[k]]);

					// Set to true if at least one element adjacent to the
					// element in question has been assigned and has the same color
					condition = (adjCell->assigned && mat[i][j] == mat[i + row[k]][j + col[k]]);

					// The moment condition is set to true this value become true until it is reset to false later on
					if (condition)
					{
						found = true;

						// Assigns the group of the current element to the adjacent group if condition is true and
						// It is assigned any group yet
						if (!cell->assigned)
						{
							cell->sub_group = adjCell->sub_group;
							cell->group = adjCell->group;
						}
						else
						{
							// If the condition is true but the current element is already assigned an element then
							// the all element in the adjacent's group is changed to the current elements group
							bool cc = !isFound("concat", cell->group, adjCell->group, "cell: " + to_string(i) + "-" + to_string(j) + " adj: " + to_string(i + row[k]) + "-" + to_string(j + col[k])) && cell->sub_group != adjCell->sub_group;
							if (cc)
							{
								temp = cell->group + adjCell->group.substr(1);
								// cout << cell->group << " + " << adjCell->group << " = " << temp << endl;
								adjCell->group = temp;
								cell->group = temp;
							}
							if (cell->sub_group == adjCell->sub_group)
							{
								if (cell->group > adjCell->group)
								{
									temp = cell->group;
								}
								else
								{
									temp = adjCell->group;
								}
								cell->group = temp;
								adjCell->group = temp;
							}
						}

						// If conditon was set to true the the current element will be assigned(true)
						cell->assigned = true;
					}
				}
			}
			if (!found)
			{
				// If no adjacent value that fullfils the condition is found then it will be assigned a new group
				auto thePrime = (VIP_ENCULONG)primeNum[groupIndex];
				// cout << "using prime: " << thePrime << endl;
				cell->sub_group += to_string(thePrime) + "-";
				cell->group = cell->sub_group;
				groupIndex++;
			}

			// all value are assigned after the finish this phase
			cell->assigned = true;
			// found variable is reset for the next iteration
			found = false;
		}
	}
	// cout << "\n Fat matrix : " << endl;
	// printStructMatrix(struct_mat);

	// Holds the value of the group to be changed
	string targetGr = "";
	for (int ix = 0; ix < M; ix++)
	{
		for (int iy = 0; iy < N; iy++)
		{
			VIP_ENCBOOL _istarget = (x == ix && y == iy);
			targetGr = VIP_CMOV(_istarget, struct_mat[ix][iy].group, targetGr);
		}
	}
	cout << "\ntargetGr : " << targetGr << endl;
	for (int ix = 0; ix < M; ix++)
	{
		for (int iy = 0; iy < N; iy++)
		{
			bool cond = isFound("target", struct_mat[ix][iy].group, targetGr) && struct_mat[ix][iy].group.length() > targetGr.length();
			targetGr = VIP_CMOV(cond, struct_mat[ix][iy].group, targetGr);

			// cout << struct_mat[ix][iy].group << "\n - cond : " << cond << "\n";
			// cout << " % : " << targetGr << " = " << struct_mat[ix][iy].group % targetGr << "\n\n";
		}
	}
	cout << "\ntargetGr : " << targetGr << endl;

	// This loop finds each element that is in the target group and assigns it with the replacemnt color
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{

			condition = (isFound("color", targetGr, struct_mat[i][j].sub_group));
			// cout << struct_mat[i][j].group << " - cond : " << condition << "\n";
			// cout << " sub-group : " << struct_mat[i][j].sub_group << " division: " << fixed << (targetGr % struct_mat[i][j].sub_group) << "\n\n";

			mat[i][j] = VIP_CMOV(condition, replacement, mat[i][j]);
		}
	}
#else
#define ISSAFE(MAT, X, Y, TARGET) (((X) >= 0 && (X) < M && (Y) >= 0 && (Y) < N) && mat[(X)][(Y)] == (TARGET))
	VIP_ENCCHAR target = mat[x][y];

	mat[x][y] = replacement;

	for (int k = 0; k < 8; k++)
	{
		if (ISSAFE(mat, x + row[k], y + col[k], target))
		{
			floodfill(mat, x + row[k], y + col[k], replacement);
		}
	}
#endif
}

void floodfillNA(VIP_ENCCHAR mat[M][N], VIP_ENCINT x, VIP_ENCINT y, VIP_ENCCHAR replacement)
{
#define ISSAFE(MAT, X, Y, TARGET) (((X) >= 0 && (X) < M && (Y) >= 0 && (Y) < N) && mat[(X)][(Y)] == (TARGET))

	// get the target color
	VIP_ENCCHAR target = mat[x][y];

	// replace the current pixel color with that of replacement
	mat[x][y] = replacement;

	// process all eight adjacent pixels of the current pixel and
	// recur for each valid pixel
	for (int k = 0; k < 8; k++)
	{
		// if the adjacent pixel at position `(x + row[k], y + col[k])` is
		// a valid pixel and has the same color as that of the current pixel
		if (ISSAFE(mat, x + row[k], y + col[k], target))
		{
			floodfillNA(mat, x + row[k], y + col[k], replacement);
		}
	}
}
void printMatrix(VIP_ENCCHAR mat[M][N], VIP_ENCINT x, VIP_ENCINT y, VIP_ENCCHAR replacement)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// char *outpt = VIP_DEC(mat[i][j]);
			if (VIP_DEC(x) == i && VIP_DEC(y) == j && VIP_DEC(mat[i][j]) != VIP_DEC(replacement))
			{
				cout << "\033[1;33m" << setw(3) << VIP_DEC(mat[i][j]) << "\033[0m";
			}
			else if (VIP_DEC(mat[i][j]) == VIP_DEC(mat[VIP_DEC(x)][VIP_DEC(y)]) && VIP_DEC(mat[i][j]) != VIP_DEC(replacement))
			{
				cout << "\033[1;31m" << setw(3) << VIP_DEC(mat[i][j]) << "\033[0m";
			}
			else if (VIP_DEC(mat[i][j]) == VIP_DEC(replacement))
			{
				cout << "\033[1;32m" << setw(3) << VIP_DEC(mat[i][j]) << "\033[0m";
			}
			else
			{
				cout << setw(3) << VIP_DEC(mat[i][j]);
			}
		}
		cout << endl;
	}
}

void clearScreen(int delay)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	cout << "\033[H\033[2J\033[3J";
}

void copyMatrix(VIP_ENCCHAR mat[M][N], VIP_ENCCHAR copy[M][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			copy[i][j] = mat[i][j];
		}
	}
}
bool compareMatrix(VIP_ENCCHAR mat1[M][N], VIP_ENCCHAR mat2[M][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mat1[i][j] != mat2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void primeInRange(int L, int R)
{
	int i, j, flag;
	int count = 0;
	// Traverse each number in the
	// interval with the help of for loop
	for (i = L; i <= R; i++)
	{

		// Skip 0 and 1 as they are
		// neither prime nor composite
		if (i == 1 || i == 0)
			continue;

		// flag variable to tell
		// if i is prime or not
		flag = 1;

		// Iterate to check if i is prime
		// or not
		for (j = 2; j <= i / 2; ++j)
		{
			if (i % j == 0)
			{
				flag = 0;
				break;
			}
		}

		// flag = 1 means i is prime
		// and flag = 0 means i is not prime
		if (flag == 1)
		{
			primeNum[count] = i;
			count++;
			// printf("%d ", i);
		}
	}
	cout << "prime count: " << count << endl;
}
int main3()
{
	string test = "-2-54-7-19-5-234-56-8-24-";
	cout << sortGroup(test) << endl;
	// vector<string> res = split(test, "-");

	// for (int i = 0; i < res.size(); i++)
	// {
	// 	cout << i << " : " << res[i] << endl;
	// }

	return 0;
}
int main()
{

	VIP_ENCCHAR replacement = 'C';
#ifndef VIP_NA_MODE
	// generatePrime();
	primeInRange(1, 548);

#endif
	// VIP_ENCINT x = 6, y = 9;
	// VIP_ENCCHAR mat[M][N] =
	// 	{
	// 		{'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
	// 		{'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X'},
	// 		{'G', 'X', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X'},
	// 		{'W', 'X', 'X', 'W', 'W', 'G', 'G', 'G', 'G', 'X'},
	// 		{'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X'},
	// 		{'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X'},
	// 		{'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X'},
	// 		{'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X'},
	// 		{'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X'},
	// 		{'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};

	// cout << "\nBEFORE flooding `" << VIP_DEC(replacement) << "' @ "
	// 	 << "(" << VIP_DEC(x) << "," << VIP_DEC(y) << "):\n";
	// printMatrix(mat, x, y, replacement);

	// floodfill(mat, x, y, replacement);

	// cout << "\nAFTER:" << endl;
	// printMatrix(mat, x, y, replacement);

	// VIP_ENCCHAR mat2[M][N] = {
	// 	{'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
	// 	{'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X'},
	// 	{'G', 'X', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X'},
	// 	{'W', 'X', 'X', 'W', 'W', 'G', 'G', 'G', 'G', 'X'},
	// 	{'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X'},
	// 	{'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X'},
	// 	{'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X'},
	// 	{'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X'},
	// 	{'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X'},
	// 	{'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};
	// ;

	// cout << "\nBEFORE flooding `" << VIP_DEC(replacement) << "' @ "
	// 	 << "(" << VIP_DEC(x) << "," << VIP_DEC(y) << "):\n";
	// printMatrix(mat2, x, y, replacement);

	// floodfillNA(mat2, x, y, replacement);

	// cout << "\nAFTER:" << endl;
	// printMatrix(mat2, x, y, replacement);

	// testing
	mysrand(time(NULL));
	int failCount = 0;
	int total = 0;

	for (int run = 0; run < 100; run++)
	{
		VIP_ENCCHAR mat[M][N];

		// randomly populate
		for (int row = 0; row < M; row++)
		{
			for (int col = 0; col < N; col++)
			{
				VIP_ENCCHAR randChar = (myrand() > RAND_MAX / 2) ? 'O' : 'X';
				mat[row][col] = randChar;
			}
		}

		// run for every possible target
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				total++;

				VIP_ENCINT x = i, y = j;

				VIP_ENCCHAR copy1[M][N];
				VIP_ENCCHAR copy2[M][N];
				copyMatrix(mat, copy1);
				copyMatrix(mat, copy2);

				cout << "\nTEST:" << total << endl;
				cout << "\nNA - Before:" << endl;
				printMatrix(copy2, x, y, replacement);

				cout << "\nDO - Before:" << endl;
				printMatrix(copy1, x, y, replacement);

				bool inputSame = compareMatrix(copy1, copy2);
				auto inputSameText = inputSame ? "\033[1;32mPASS\033[0m" : "\033[1;31mFAIL\033[0m";
				cout << "\nSame Input: " << inputSameText << endl;

				// for NA flood fill
				floodfillNA(copy2, x, y, replacement);
				cout << "\nNA - After:" << endl;
				printMatrix(copy2, x, y, replacement);

				// for DO flood fill
				floodfill(copy1, x, y, replacement);
				cout << "\nDO - After:" << endl;
				printMatrix(copy1, x, y, replacement);

				bool equal = compareMatrix(copy1, copy2);
				auto equalText = equal ? "\033[1;32mPASS\033[0m" : "\033[1;31mFAIL\033[0m";
				cout << "\nCorrectness: " << equalText << endl;

				if (!equal)
				{
					failCount++;
					cout << "Failed: [" << i << ", " << j << "]" << endl;
					return 0;
					// cout << "\nContinue? ";
					// cin.get();
				}

				clearScreen(1);
			}
		}
	}
	if (failCount == 0)
	{
		cout << "\n\033[1;32mPassed all tests!\033[0m\n\n";
	}
	else
	{
		cout << "\n\033[1;31mFailed " << failCount << " of " << total << " tests!\033[0m\n\n";
	}
}
