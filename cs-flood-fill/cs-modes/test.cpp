#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>

using namespace std;

#include "../config.h"
#include "utils.h"

// `M × N` matrix
#define M 10
#define N 10

// Used to find adjacent values of an element in a matrix
int row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int col[] = {-1, 0, 1, -1, 1, -1, 0, 1};
// same size as the given matrix
// An element with location(x,y) here represents the element(x,y) in the input matrix
// Holds the groups of the elements in the input matrix
int group[M][N];
bool visited[M][N];

// Can use this function to see the groups and subgroup
void printStructMatrix(node struct_mat[M][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(6) << "(" << VIP_DEC(struct_mat[i][j].sub_group) << "," << VIP_DEC(struct_mat[i][j].group) << ")";
		}
		cout << endl;
	}
}

void floodfill(VIP_ENCCHAR mat[M][N], VIP_ENCINT x, VIP_ENCINT y, VIP_ENCCHAR replacement)
{

#define SAFELOC(X, Y) ((X) >= 0 && (X) < M && (Y) >= 0 && (Y) < N)

	// Used for the condition value in VIP_CMOV
	VIP_ENCBOOL condition = false;
	VIP_ENCBOOL found = false;
	VIP_ENCULONG temp = 0;

	VIP_ENCINT group_count = 0;

	// Get what the color is at mat[x][y], i.e. the target color
	VIP_ENCCHAR target_color = 0;
	for (int ix = 0; ix < M; ix++)
	{
		for (int iy = 0; iy < N; iy++)
		{
			target_color = VIP_CMOV(x == ix && y == iy, mat[ix][iy], target_color);
		}
	}

	// Find groups of the target color
	for (int ix = 0; ix < M; ix++)
	{
		for (int iy = 0; iy < N; iy++)
		{
			// First time we are visiting this node!
			assert(visited[ix][iy] == false);
			visited[ix][iy] = true;
			VIP_ENCBOOL is_target_color = (mat[ix][iy] == target_color);

			// If its target color, want to assign to adj group or start a new group!
			// Check if any groups are adjacent
			VIP_ENCINT groupnum = 0;
			for (int k = 0; k < 8; k++)
			{
				if (SAFELOC(ix + row[k], iy + col[k]))
				{ // CAUTION: Iter order may impact correctness...
					VIP_ENCBOOL has_visited = visited[ix + row[k]][iy + col[k]];
					VIP_ENCINT this_groupnum = group[ix + row[k]][iy + col[k]];
					if (has_visited && this_groupnum > 0)
					{ // TODO:: FIXME
						assert(groupnum == 0 || groupnum == this_groupnum);
						groupnum = this_groupnum;
					}
				}
			}
			VIP_ENCBOOL assign_to_new_group = is_target_color && groupnum == 0;
				group_count = VIP_CMOV(is_target_color && groupnum==0, group_count)
				group[ix][iy]=VIP_CMOV(is_target_color && groupnum==0, sgroupnum;
		}
	}

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (SAFELOC(i + row[k], j + col[k]))
				{

					// Set to true if at least one element adjacent to the
					// element in question has been assigned and has the same color
					condition = (struct_mat[i + row[k]][j + col[k]].assigned && mat[i][j] == mat[i + row[k]][j + col[k]]);

					// The moment condition is set to true this value become true until it is reset to false later on
					found = VIP_CMOV(condition, condition, found);

					// Assigns the group of the current element to the adjacent group if condition is true and
					// It is assigned any group yet
					struct_mat[i][j].sub_group = VIP_CMOV((condition && !struct_mat[i][j].assigned), struct_mat[i + row[k]][j + col[k]].sub_group, struct_mat[i][j].sub_group);
					struct_mat[i][j].group = VIP_CMOV((condition && !struct_mat[i][j].assigned), struct_mat[i + row[k]][j + col[k]].group, struct_mat[i][j].group);

					// If the condition is true but the current element is already assigned an element then
					// the all element in the adjacent's group is changed to the current elements group
					temp = struct_mat[i][j].group * struct_mat[i + row[k]][j + col[k]].group;
					struct_mat[i + row[k]][j + col[k]].group = VIP_CMOV(condition && struct_mat[i][j].assigned && !isFactor(struct_mat[i][j].group, struct_mat[i + row[k]][j + col[k]].group) && struct_mat[i][j].sub_group != struct_mat[i + row[k]][j + col[k]].sub_group, temp, struct_mat[i + row[k]][j + col[k]].group);
					struct_mat[i][j].group = VIP_CMOV(condition && struct_mat[i][j].assigned && !isFactor(struct_mat[i][j].group, struct_mat[i + row[k]][j + col[k]].group) && struct_mat[i][j].sub_group != struct_mat[i + row[k]][j + col[k]].sub_group, temp, struct_mat[i][j].group);

					temp = VIP_CMOV(struct_mat[i][j].group > struct_mat[i + row[k]][j + col[k]].group, struct_mat[i][j].group, struct_mat[i + row[k]][j + col[k]].group);
					struct_mat[i][j].group = VIP_CMOV(condition && struct_mat[i][j].assigned && struct_mat[i][j].sub_group == struct_mat[i + row[k]][j + col[k]].sub_group, temp, struct_mat[i][j].group);
					struct_mat[i + row[k]][j + col[k]].group = VIP_CMOV(condition && struct_mat[i][j].assigned && struct_mat[i][j].sub_group == struct_mat[i + row[k]][j + col[k]].sub_group, temp, struct_mat[i + row[k]][j + col[k]].group);

					// If conditon was set to true the the current element will be assigned(true)
					struct_mat[i][j].assigned = VIP_CMOV(condition, (VIP_ENCBOOL) true, struct_mat[i][j].assigned);
				}
			}
			// If no adjacent value that fullfils the condition is found then it will be assigned a new group
			struct_mat[i][j].sub_group = VIP_CMOV(!found, (VIP_ENCULONG)primeNum[groupIndex], struct_mat[i][j].sub_group);
			struct_mat[i][j].group = VIP_CMOV(!found, struct_mat[i][j].sub_group, struct_mat[i][j].group);

			// all value are assigned after the finish this phase
			struct_mat[i][j].assigned = true;
			// found variable is reset for the next iteration
			found = false;
			groupIndex++;
		}
	}

	// Holds the value of the group to be changed
	VIP_ENCULONG targetGr = 1;
	for (int ix = 0; ix < M; ix++)
	{
		for (int iy = 0; iy < N; iy++)
		{
			VIP_ENCBOOL _istarget = (x == ix && y == iy);
			targetGr = VIP_CMOV(_istarget, struct_mat[ix][iy].group, targetGr);
			targetGr = VIP_CMOV(condition && isFactor(struct_mat[ix][iy].group, targetGr), struct_mat[ix][iy].group, targetGr);
			condition = VIP_CMOV(_istarget, (VIP_ENCBOOL) true, condition);
		}
	}

	// This loop finds each element that is in the target group and assigns it with the replacemnt color
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			condition = (isFactor(targetGr, struct_mat[i][j].sub_group));
			mat[i][j] = VIP_CMOV(condition, replacement, mat[i][j]);
		}
	}
}

void printMatrix(VIP_ENCCHAR mat[M][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(3) << VIP_DEC(mat[i][j]);
		}
		cout << endl;
	}
}

int main()
{

	VIP_ENCINT x = 3, y = 9;
	VIP_ENCCHAR replacement = 'C';
#ifndef VIP_NA_MODE
	generatePrime();
#endif

	VIP_ENCCHAR mat[M][N] =
		{
			{'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
			{'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X'},
			{'G', 'X', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X'},
			{'W', 'X', 'X', 'W', 'W', 'G', 'G', 'G', 'G', 'X'},
			{'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X'},
			{'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X'},
			{'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X'},
			{'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X'},
			{'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X'},
			{'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};

	cout << "\nBEFORE flooding `" << VIP_DEC(replacement) << "' @ "
		 << "(" << VIP_DEC(x) << "," << VIP_DEC(y) << "):\n";
	printMatrix(mat);
	{
		Stopwatch start("VIP-bench runtime: ");
		floodfill(mat, x, y, replacement);
	}
	cout << "\nAFTER:" << endl;
	printMatrix(mat);
}
