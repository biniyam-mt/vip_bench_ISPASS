/*
 ELEMENT DISTINCTNESS ALGORITHM
 The approach used in this algorithm is adding the elements in an array implementation of a binary tree
 If the elements already exists in the tree then the elements are not distinct else it is. The function
 performing the algorithm is the isDistinct function. The argument 'dup' stores the first duplicate found in
 the array.
*/
#include <iostream>
#include <limits>

#include "../config.h"
#include <bits/stdc++.h>

using namespace std;

#define SIZE  20
// NOTE: 0 can not be an element of the array evaluated for distinctness since MAX is set to 0
#define MAX 0


VIP_ENCINT elements1[SIZE] = {25,97,1,0,36,22,74,3,9,12,30,81,63,148,99,13,64,49,80,15};
VIP_ENCINT elements2[SIZE] = {25,97,1,0,36,22,74,3,99,12,30,81,63,148,99,13,64,49,99,15};
VIP_ENCINT elements3[SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,4,15,16,17,18,19,1};

VIP_ENCBOOL
isDistinct(VIP_ENCINT elements[], VIP_ENCINT &dup)
{

  VIP_ENCINT tree[SIZE][3];
  dup = MAX;

	for(int i = 0; i < SIZE;i++){
		tree[i][0] = MAX;
		tree[i][1] = MAX;
		tree[i][2] = MAX;
	}	
	
	tree[0][0] = elements[0];
	VIP_ENCINT location = 0;

	for(int i = 1; i < SIZE; i++){
		VIP_ENCINT temp = 0;
		VIP_ENCINT value = tree[0][0];
		VIP_ENCINT left = tree[0][1];
		VIP_ENCINT right = tree[0][2];

		while(value != MAX){
			if(elements[i] > value){
				if(right != MAX){
					value = tree[right][0];
					left = tree[right][1];
					temp = right;
					right = tree[right][2];
				}else{
					tree[location+1][0] = elements[i];
					tree[temp][2] = location + 1;
					location++;
					break;
				}
			}else if(elements[i] < value){
				if(left != MAX){
					value = tree[left][0];
					right = tree[left][2];
					temp = left;
					left = tree[left][1];
				}else{
					tree[temp][1] = location+1;
					tree[location+1][0] = elements[i];
					location++;
					break;
				}
			}else{
        		dup = elements[i];
				return false;
			}
		}
	}
	return true;
}

int
main(void)
{
  VIP_ENCINT dup1, dup2, dup3;

  bool res1, res2, res3;

  {
    Stopwatch s("VIP Distinctness check:");

    res1 = VIP_DEC(isDistinct(elements1, dup1));
    res2 = VIP_DEC(isDistinct(elements2, dup2));
	res3 = VIP_DEC(isDistinct(elements3, dup3));
  }

  if (res1)
		cout<<"The elements of `elements1' are distinct"<<endl;
	else
		cout<<"The elements of `elements1' are not distinct (e.g., " << VIP_DEC(dup1) << " is duplicated)"<<endl;
	
  if (res2)
		cout<<"The elements of `elements2' are distinct"<<endl;
	else
		cout<<"The elements of `elements2' are not distinct (e.g., " << VIP_DEC(dup2) << " is duplicated)"<<endl;
  if (res3)
		cout<<"The elements of `elements3' are distinct"<<endl;
	else
		cout<<"The elements of `elements3' are not distinct (e.g., " << VIP_DEC(dup3) << " is duplicated)"<<endl;

	return 0;
}

