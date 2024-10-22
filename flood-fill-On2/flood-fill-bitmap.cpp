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
int BITMAPS = 1;

#ifndef VIP_NA_MODE

typedef vector<VIP_ENCUINT64> VIP_Enc_Group_t;
typedef VIP_ENCUINT64 VIP_Enc_Id_t;

VIP_Enc_Group_t initId(BITMAPS, 0);	   //{BITMAPS x 0}
VIP_Enc_Group_t initGroup(BITMAPS, 0); //{BITMAPS x 0}
struct node
{
	VIP_Enc_Group_t id = initId;
	VIP_Enc_Group_t group = initGroup;
};

string dev_intToBinary(uint64_t n)
{
	if (!n)
		return "0";
	string binary = "";
	while (n)
	{
		if (n & 1)
			binary = "1" + binary;
		else
			binary = "0" + binary;

		n >>= 1;
	}
	return binary;
}

int dev_binaryToInt(string binary)
{
	return std::stoi(binary, nullptr, 2);
}

// Can use this function to see groups and ids
void dev_printStructMatrix(node struct_mat[M][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// needs to be updated
			cout << setw(6) << "(" << dev_intToBinary(VIP_DEC(struct_mat[i][j].id[0])) << " - " << dev_intToBinary(VIP_DEC(struct_mat[i][j].id[0])) << " : " << dev_intToBinary(VIP_DEC(struct_mat[i][j].id[0])) << " - " << dev_intToBinary(VIP_DEC(struct_mat[i][j].group[1])) << "),";
		}
		cout << endl;
	}
}
VIP_ENCBOOL haveIntersection(VIP_Enc_Group_t bin1, VIP_Enc_Group_t bin2)
{
	VIP_ENCBOOL intersect = false;
	for (int i = 0; i < BITMAPS; i++)
	{
		intersect = VIP_CMOV(bin1[i] & bin2[i], VIP_ENCBOOL(true), intersect);
	}

	return intersect;
}
VIP_Enc_Group_t combine(VIP_Enc_Group_t bin1, VIP_Enc_Group_t bin2)
{
	VIP_Enc_Group_t combined = initGroup;

	for (int i = 0; i < BITMAPS; i++)
	{
		combined[i] = bin1[i] | bin2[i];
	}
	return combined;
}
VIP_Enc_Id_t nextId(VIP_Enc_Id_t currentId)
{
	VIP_Enc_Id_t nextId = currentId << 1;

	VIP_Enc_Id_t ret = VIP_CMOV(nextId <= currentId, VIP_Enc_Id_t(0), nextId);

	return ret;
}
#endif

int floodfill(VIP_ENCCHAR mat[M][N], VIP_ENCINT x, VIP_ENCINT y, VIP_ENCCHAR replacement)
{
	int row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int col[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	node struct_mat[M][N];
	VIP_Enc_Id_t currId = 1;
	int bitMapIdx = 0;

#ifndef VIP_NA_MODE
#define SAFELOC(X, Y) ((X) >= 0 && (X) < M && (Y) >= 0 && (Y) < N)

	// Used for the condition value in VIP_CMOV
	VIP_ENCBOOL condition = false;
	VIP_ENCINT retVal = 0;
	// Set to true if at least one element adjacent to the
	// element in question has the same color
	VIP_ENCBOOL matchFound = false;

	// Forward pass
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{

			node *cell = &(struct_mat[i][j]);
			VIP_Enc_Group_t commonGroup = cell->group;

			// Forward read pass
			for (int k = 0; k < 4; k++)
			{

				if (SAFELOC(i + row[k], j + col[k]))
				{
					node *adjCell = &(struct_mat[i + row[k]][j + col[k]]);

					VIP_ENCBOOL match = (mat[i][j] == mat[i + row[k]][j + col[k]]);

					matchFound = VIP_CMOV(match, VIP_ENCBOOL(true), matchFound);
					// cout << "check1" << endl;

					commonGroup = VIP_CMOV(match, combine(commonGroup, adjCell->group), commonGroup);

					VIP_ENCBOOL hasId = false;
					for (int i = 0; i < BITMAPS; i++)
					{
						hasId = VIP_CMOV(cell->id[i], true, hasId);
					}

					cell->id = VIP_CMOV(match & !hasId, adjCell->id, cell->id);
				}
			}

			cell->group = commonGroup;

			// Forward write pass
			for (int k = 0; k < 4; k++)
			{
				if (SAFELOC(i + row[k], j + col[k]))
				{
					node *adjCell = &(struct_mat[i + row[k]][j + col[k]]);

					// Set to true if at least one element adjacent to the
					// element in question has been assigned and has the same color
					VIP_ENCBOOL match = (mat[i][j] == mat[i + row[k]][j + col[k]]);

					// The moment condition is set to true this value become true until it is reset to false later on
					adjCell->group = VIP_CMOV(match, commonGroup, adjCell->group);
				}
			}

			if (!matchFound)
			{
				// If no adjacent value that fullfils the condition is found then it will be assigned a new group

				if (currId == 0)
				{
					if (bitMapIdx + 1 < BITMAPS)
					{
						bitMapIdx++;
						currId = 1;
						// cout << "bitmap inc!" << endl;
					}
					else
					{
						cout << "overflowed!" << endl;
						return -1;
					}
				}

				cell->id[bitMapIdx] = currId;

				cell->group[bitMapIdx] = currId;

				currId = nextId(currId);
			}

			// retVal = VIP_CMOV(!matchFound & currId == 0, VIP_ENCINT(-1), retVal);

			// cell->id = VIP_CMOV(!matchFound, currId, cell->id);
			// cell->group = VIP_CMOV(!matchFound, currId, cell->group);
			// currId = VIP_CMOV(!matchFound, nextId(currId), currId);

			// found variable is reset for the next iteration
			matchFound = false;
		}
	}
	// dev_printStructMatrix(struct_mat);
	cout << endl;

	// Reverse pass
	for (int i = M - 1; i >= 0; i--)
	{
		for (int j = N - 1; j >= 0; j--)
		{
			node *cell = &(struct_mat[i][j]);
			VIP_Enc_Group_t commonGroup = cell->group;
			// Reverse read pass
			for (int k = 0; k < 8; k++)
			{
				if (SAFELOC(i + row[k], j + col[k]))
				{
					node *adjCell = &(struct_mat[i + row[k]][j + col[k]]);

					// Set to true if at least one element adjacent to the
					// element in question has been assigned and has the same color
					VIP_ENCBOOL match = (mat[i][j] == mat[i + row[k]][j + col[k]]);

					// The moment condition is set to true this value become true until it is reset to false later on
					// if (match)
					// {

					// 	commonGroup = combine(commonGroup, adjCell->group);
					// }
					commonGroup = VIP_CMOV(match, combine(commonGroup, adjCell->group), commonGroup);
				}
			}
			// Reverse write pass
			cell->group = commonGroup;
			for (int k = 0; k < 8; k++)
			{
				if (SAFELOC(i + row[k], j + col[k]))
				{
					node *adjCell = &(struct_mat[i + row[k]][j + col[k]]);

					// Set to true if at least one element adjacent to the
					// element in question has been assigned and has the same color
					VIP_ENCBOOL match = (mat[i][j] == mat[i + row[k]][j + col[k]]);

					// The moment condition is set to true this value become true until it is reset to false later on
					// if (match)
					// {
					// 	adjCell->group = commonGroup;
					// }
					adjCell->group = VIP_CMOV(match, commonGroup, adjCell->group);
				}
			}
		}
	}

	// dev_printStructMatrix(struct_mat);

	// Target group pass
	VIP_Enc_Group_t targetGr = initGroup;
	for (int ix = 0; ix < M; ix++)
	{
		for (int iy = 0; iy < N; iy++)
		{
			VIP_ENCBOOL _istarget = (x == ix & y == iy);
			targetGr = VIP_CMOV(_istarget, struct_mat[ix][iy].group, targetGr);
		}
	}
	// cout << "\ntargetGr : " << dev_intToBinary(targetGr[0]) << " - " << dev_intToBinary(targetGr[1]) << endl;

	// Target Group Update pass
	for (int ix = 0; ix < M; ix++)
	{
		for (int iy = 0; iy < N; iy++)
		{

			node *cell = &struct_mat[ix][iy];

			VIP_ENCBOOL cond = haveIntersection(cell->group, targetGr);
			// if group contains target group
			// if (cond)
			// {
			// 	targetGr = combine(cell->group, targetGr);
			// }
			targetGr = VIP_CMOV(cond, combine(cell->group, targetGr), targetGr);
		}
	}
	// cout << "\ntargetGr : " << targetGr << endl;
	// cout << "\ntargetGr : " << dev_intToBinary(targetGr[0]) << " - " << dev_intToBinary(targetGr[1]) << endl;

	// Coloring pass
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{

			VIP_ENCBOOL flood = haveIntersection(targetGr, struct_mat[i][j].group);
			mat[i][j] = VIP_CMOV(flood, replacement, mat[i][j]);
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
	return retVal;
}

void floodfillNA(VIP_ENCCHAR mat[M][N], VIP_ENCINT x, VIP_ENCINT y, VIP_ENCCHAR replacement)
{
	int row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int col[] = {-1, 0, 1, -1, 1, -1, 0, 1};
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
void dev_printMatrix(VIP_ENCCHAR mat[M][N], VIP_ENCINT x, VIP_ENCINT y, VIP_ENCCHAR replacement)
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
void dev_printRawMatrix(VIP_ENCCHAR mat[M][N])
{
	cout << "{ ";
	for (int i = 0; i < M; i++)
	{
		cout << "{ ";
		for (int j = 0; j < N; j++)
		{
			cout << "'" << mat[i][j] << "', ";
		}
		cout << "},";
		cout << endl;
	}
	cout << "};";
}

void dev_clearScreen(int delay)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	cout << "\033[H\033[2J\033[3J";
}
string dev_readableNumber(long n)
{
	string num = to_string(n);
	string res = "";

	int size = num.size();
	int count = size;

	for (int i = num.size() - 1; i >= 0; i--)
	{
		res = num[i] + res;
		if ((size - i) % 3 == 0 && i != 0)
			res = "," + res;
	}
	return res;
}
void dev_copyMatrix(VIP_ENCCHAR mat[M][N], VIP_ENCCHAR copy[M][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			copy[i][j] = mat[i][j];
		}
	}
}
bool dev_compareMatrix(VIP_ENCCHAR mat1[M][N], VIP_ENCCHAR mat2[M][N])
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

void singleTest()
{
	VIP_ENCCHAR replacement = 'C';
	VIP_ENCINT x = 0, y = 1;
	VIP_ENCCHAR mat[M][N] =
		{
			{'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
			{'X', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
			{'X', 'X', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'O'},
			{'O', 'O', 'O', 'X', 'O', 'X', 'O', 'X', 'X', 'O'},
			{'X', 'X', 'O', 'O', 'X', 'O', 'O', 'O', 'X', 'O'},
			{'X', 'O', 'X', 'O', 'O', 'X', 'O', 'O', 'X', 'O'},
			{'O', 'X', 'O', 'O', 'X', 'O', 'O', 'X', 'X', 'O'},
			{'O', 'O', 'X', 'X', 'O', 'O', 'O', 'O', 'O', 'O'},
			{'O', 'O', 'X', 'X', 'X', 'X', 'O', 'O', 'O', 'O'},
		};
	VIP_ENCCHAR copy1[M][N];
	VIP_ENCCHAR copy2[M][N];
	dev_copyMatrix(mat, copy1);
	dev_copyMatrix(mat, copy2);

	cout << "\nNA - Before:" << endl;
	dev_printMatrix(copy2, x, y, replacement);

	cout << "\nDO - Before:" << endl;
	dev_printMatrix(copy1, x, y, replacement);

	bool inputSame = dev_compareMatrix(copy1, copy2);
	auto inputSameText = inputSame ? "\033[1;32mPASS\033[0m" : "\033[1;31mFAIL\033[0m";
	cout << "\nSame Input: " << inputSameText << endl;

	// for NA flood fill
	floodfillNA(copy2, x, y, replacement);
	cout << "\nNA - After:" << endl;
	dev_printMatrix(copy2, x, y, replacement);

	// for DO flood fill
	floodfill(copy1, x, y, replacement);
	cout << "\nDO - After:" << endl;
	dev_printMatrix(copy1, x, y, replacement);

	bool equal = dev_compareMatrix(copy1, copy2);
	auto equalText = equal ? "\033[1;32mPASS\033[0m" : "\033[1;31mFAIL\033[0m";
	cout << "\nCorrectness: " << equalText << endl;
}
void allTest()
{

	VIP_ENCCHAR replacement = 'C';
#ifndef VIP_NA_MODE

#endif

	// testing
	int failCount = 0;
	int overflow = 0;
	int total = 0;
	auto seed = time(NULL);
	mysrand(seed);

	long testMatriceCount = 10000;

	for (int run = 0; run < testMatriceCount; run++)
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

		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				total++;

				VIP_ENCINT x = i, y = j;

				VIP_ENCCHAR copy1[M][N];
				VIP_ENCCHAR copy2[M][N];
				dev_copyMatrix(mat, copy1);
				dev_copyMatrix(mat, copy2);

				// for NA flood fill
				floodfillNA(copy2, x, y, replacement);

				// for DO flood fill
				int ret = floodfill(copy1, x, y, replacement);

				if (ret == 0)
				{

					bool equal = dev_compareMatrix(copy1, copy2);

					if (!equal)
					{
						failCount++;
						cout << x << " " << y << endl;
						dev_printRawMatrix(mat);
						return;
					}
				}
				else
				{
					overflow += 1;
				}

				dev_clearScreen(0);
				long totalTestCount = 1 * testMatriceCount;
				cout << "\n\033[1;36mRunning " << dev_readableNumber(totalTestCount) << " tests on " << M << "x" << N << " matrices using " << BITMAPS << " long integers!\033[0m\n";
				int completed = total * 100 / double(totalTestCount);
				cout << "\n\033[1;33mCompleted: " << completed << "% \033[0m\n";
				cout << "\n\033[1;33mMatrices tested: " << dev_readableNumber(run + 1) << " \033[0m\n";
				cout << "\n\033[1;33mTotal: " << dev_readableNumber(total) << " \033[0m\n";
				cout << "\n\033[1;32mPassed: " << dev_readableNumber(total - overflow - failCount) << " \033[0m\n";
				cout << "\n\033[1;31mFailed " << dev_readableNumber(failCount) << "\033[0m\n";
				cout << "\n\033[1;35mOverflowed: " << dev_readableNumber(overflow) << "\033[0m\n";
			}
		}
	}
}

int main()
{
	// singleTest();
	allTest();

	// node myNode;
	// cout << "readable: " << dev_readableNumber(23465745683686384) << endl;
	// auto c = myNode.group;
	// for (int i = 0; i < c.size(); i++)
	// {
	// 	cout << "bitmap " << c[i] << endl;
	// }

	// VIP_Enc_Id_t currId = 1;
	// int bitMapIdx = 0;

	// while (1)
	// {

	// 	if (currId == 0)
	// 	{
	// 		if (bitMapIdx + 1 < BITMAPS)
	// 		{
	// 			bitMapIdx++;
	// 			currId = 1;
	// 		}
	// 		else
	// 		{
	// 			cout << "over!" << endl;
	// 			return -1;
	// 		}
	// 	}

	// 	cout << bitMapIdx << " : " << currId << endl;
	// 	currId = nextId(currId);
	// }

	return 0;
}
