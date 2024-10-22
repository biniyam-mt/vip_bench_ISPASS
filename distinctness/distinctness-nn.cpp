/*
 ELEMENT DISTINCTNESS ALGORITHM
 There are multiple ways of detecting whether the elements are distinct or not. 
 An n^2 loop can be used to select an element from the array and check if the
 the element exists. The function checking for duplicates is the isDistinct 
 function. The argument 'dup' stores the first duplicate found in the array.
*/
#include <iostream>
#include <limits>

#include "../config.h"

using namespace std;

#define SIZE  20
#define MAX numeric_limits<int>::max()


VIP_ENCINT elements1[SIZE] = {25,97,1,0,36,22,74,3,9,12,30,81,63,148,99,13,64,49,80,15};
VIP_ENCINT elements2[SIZE] = {25,97,1,0,36,22,74,3,99,12,30,81,63,148,99,13,64,49,99,15};
VIP_ENCINT elements3[SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,4,15,16,17,18,19,1};

VIP_ENCBOOL
isDistinct(VIP_ENCINT elements[], VIP_ENCINT &dup)
{

  dup = MAX;
  for (int i=SIZE-1; i >= 0; i--){
    for (int j=0; j < SIZE; j++){
#ifdef VIP_DO_MODE /* VIP_DO_MODE */
        /**** IISWC DO Transformation: <IF> [MZD] ****/
        /**** Description: Using CMOV in place of if-statement ****/
        dup = VIP_CMOV(elements[i] == elements[j] && i!=j && dup == MAX, elements[j], dup);
#else
        if(elements[i] == elements[j] && i!=j){
			      dup = elements[j];
            /**** IISWC DO Transformation: <LOOP> [MZD] ****/
            /**** Description: Early exit from for loop ****/
            return false;
	    }
#endif	
        	 
	}
  }

  return (dup == MAX);

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

