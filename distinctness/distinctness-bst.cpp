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

#ifdef VIP_DO_MODE /* VIP_DO_MODE */
    
    VIP_ENCBOOL _result = true;

    for(int i = 1; i < SIZE; i++){
        VIP_ENCINT temp = 0;

        VIP_ENCINT value = tree[0][0];
        VIP_ENCINT left = tree[0][1];
        VIP_ENCINT right = tree[0][2];
        VIP_ENCBOOL isMax_r = false;
        VIP_ENCBOOL isMax_l = false;
        VIP_ENCBOOL isNotDone = !((VIP_DEC(isMax_l) || VIP_DEC(isMax_r)) && !(VIP_DEC(isMax_l) && VIP_DEC(isMax_r)));

            
        for( int k = 0; k < SIZE - 1; k++){
            VIP_ENCBOOL condition1 = elements[i] > value;
            VIP_ENCBOOL condition2 = right != MAX;

            VIP_ENCBOOL _isRightNotMax = condition1 && condition2;
            VIP_ENCBOOL _isRightMax = condition1 && !condition2;

            VIP_ENCBOOL condition3 = elements[i] < value;
            VIP_ENCBOOL condition4 = left != MAX;

            VIP_ENCBOOL _isLeftNotMax = condition3 && condition4;
            VIP_ENCBOOL _isLeftMax = condition3 && !condition4;

            VIP_ENCBOOL notBoth = !condition1 && !condition3;

            VIP_ENCINT temp0 = tree[0][0];
            VIP_ENCINT temp1 = tree[0][0];
            VIP_ENCINT temp2 = tree[0][0];
            VIP_ENCINT temp3 = tree[0][0];
            VIP_ENCINT temp4 = tree[0][0];
            VIP_ENCINT temp5 = tree[0][0];

            for(int x = 0; x < SIZE; x++){
                /**** IISWC DO Transformation: <ACCESS> [MZD] ****/
                /**** Description: Changing row accesses of the 2D matrix using a secret index to accessing all 
                      row indices and using a CMOV to return the correct value 
                ****/
                temp0 = VIP_CMOV(x == right, tree[x][0], temp0);
                temp1 = VIP_CMOV(x == right, tree[x][1], temp1);
                temp2 = VIP_CMOV(x == right, tree[x][2], temp2);
                temp3 = VIP_CMOV(x == left, tree[x][0], temp3);
                temp4 = VIP_CMOV(x == left, tree[x][2], temp4);
                temp5 = VIP_CMOV(x == left, tree[x][1], temp5);
                /**** IISWC DO Transformation: <ACCESS/IF> [MZD] ****/
                /**** Description
                     * <ACCESS>: Changing row accesses of the 2D matrix using a secret index to accessing all 
                        row indices and using a CMOV to return the correct value  
                    * <IF>: Using CMOV in place of if-statement
                ****/
                tree[x][0] = VIP_CMOV(x == location + 1 && isNotDone && _isRightMax, elements[i], tree[x][0]);
                tree[x][2] = VIP_CMOV(x == temp && isNotDone && _isRightMax, location + 1, tree[x][2]);
                tree[x][1] = VIP_CMOV(x == temp && isNotDone && _isLeftMax, location+1 , tree[x][1]);
                tree[x][0] = VIP_CMOV(x == location+1 && isNotDone && _isLeftMax, elements[i], tree[x][0]);
            }
            /**** IISWC DO Transformation: <IF> [MZD] ****/
            /**** Description: Using CMOV in place of if-statement ****/
            value = VIP_CMOV(isNotDone && _isRightNotMax, temp0, value);
            left = VIP_CMOV(isNotDone && _isRightNotMax, temp1, left);
            temp = VIP_CMOV(isNotDone && _isRightNotMax, right, temp);
            right = VIP_CMOV(isNotDone && _isRightNotMax, temp2, right);

            /**** IISWC DO Transformation: <IF> [MZD] ****/
            /**** Description: Using CMOV in place of if-statement ****/
            location = VIP_CMOV(isNotDone && _isRightMax, location + 1, location);
            isMax_r = VIP_CMOV(isNotDone && _isRightMax, VIP_ENCBOOL(true), isMax_r);

            /**** IISWC DO Transformation: <IF> [MZD] ****/
            /**** Description: Using CMOV in place of if-statement ****/
            value = VIP_CMOV(isNotDone && _isLeftNotMax,  temp3, value);
            right = VIP_CMOV(isNotDone && _isLeftNotMax,  temp4, right);
            temp = VIP_CMOV(isNotDone && _isLeftNotMax, left, temp);
            left = VIP_CMOV(isNotDone && _isLeftNotMax,  temp5, left);
            
            /**** IISWC DO Transformation: <IF> [MZD] ****/
            /**** Description: Using CMOV in place of if-statement ****/
            location = VIP_CMOV(isNotDone && _isLeftMax, location + 1, location);
            isMax_l = VIP_CMOV(isNotDone && _isLeftMax, VIP_ENCBOOL(true), isMax_l);
            dup = VIP_CMOV(isNotDone && notBoth && dup == MAX, elements[i], dup);
            _result = VIP_CMOV(isNotDone && notBoth, VIP_ENCBOOL(false), _result);
            isMax_r = VIP_CMOV(isNotDone && !isMax_r && notBoth && !(_result), VIP_ENCBOOL(true), isMax_r);

            isNotDone = !((VIP_DEC(isMax_l) || VIP_DEC(isMax_r)) && !(VIP_DEC(isMax_l) && VIP_DEC(isMax_r)));

        }
        
    }
    return _result;
#else
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
                    /**** IISWC DO Transformation: <LOOP> [MZD] ****/
                    /**** Description: Early-exit from while loop ****/
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
                    /**** IISWC DO Transformation: <LOOP> [MZD] ****/
                    /**** Description: Early-exit from while loop ****/
					break;
				}
			}else{
        		dup = elements[i];
				return false;
			}
		}
	}
	return true;

#endif

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

