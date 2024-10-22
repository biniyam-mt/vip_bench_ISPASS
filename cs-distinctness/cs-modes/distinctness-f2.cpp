/*
 ELEMENT DISTINCTNESS ALGORITHM
 There are multiple ways of detecting whether the elements are distinct or not.
 One of the ways is to sort the elements in the array and check if the elements next to each other
 are equal or not. The function checking for duplicate elements is the isDistinct function. The argument
 'dup' stores the first duplicate found in the sorted array.
*/
#include <iostream>
#include <limits>

#include "../../config.h"
#include <bits/stdc++.h>
#include "../../common/utils.h"

using namespace std;

#define SIZE 128
// NOTE: 0 can not be an element of the array evaluated for distinctness since MAX is set to 0
#define MAX 0

VIP_ENCINT elements1[SIZE];
VIP_ENCINT elements2[SIZE];
VIP_ENCINT elements3[SIZE];

// given an array arr of length n, this code sorts it in place
// all indices run from 0 to n-1
void bitonicsort(VIP_ENCINT *data, unsigned size)
{
  for (unsigned k = 2; k <= size; k <<= 1) // k is doubled every iteration
  {
    for (unsigned j = k / 2; j > 0; j >>= 1) // j is halved at every iteration, with truncation of fractional parts
    {
      for (unsigned i = 0; i < size; i++)
      {
        unsigned l = (i ^ j);

        VIP_ENCBOOL _pred = ((l > i) & ((((i & k) == 0) & (data[i] > data[l])) | (((i & k) != 0) & (data[i] < data[l]))));
        VIP_ENCINT tmp = data[i];
        data[i] = VIP_CMOV(_pred, data[l], data[i]);
        data[l] = VIP_CMOV(_pred, tmp, data[l]);
      }
    }
  }
}

VIP_ENCBOOL
isDistinct(VIP_ENCINT elements[], VIP_ENCINT &dup)
{
  // sort the data
  bitonicsort(elements, SIZE);

  // detect dups
  VIP_ENCBOOL distinct = true;
  dup = MAX;
  for (int i = SIZE - 2; i >= 0; i--)
  {
    VIP_ENCBOOL _pred = (elements[i] == elements[i + 1]);
    dup = VIP_CMOV(_pred, elements[i], dup);
    distinct = VIP_CMOV(_pred, (VIP_ENCBOOL) false, distinct);
  }
  return distinct;
}

int main(void)
{
  VIP_ENCINT dup1, dup2, dup3;

  bool res1, res2, res3;
  VIP_ENCINT print1[SIZE], print2[SIZE], print3[SIZE];
  // initialize the pseudo-RNG
  mysrand(42);

  // initialize the array to sort
  for (unsigned i = 0; i < SIZE; i++)
  {
    elements1[i] = myrand() % 201;
    elements2[i] = myrand() % 501;
    elements3[i] = myrand();
    print1[i] = elements1[i];
    print2[i] = elements2[i];
    print3[i] = elements3[i];
  }

  {
    Stopwatch s("VIP Distinctness check:");

    res1 = VIP_DEC(isDistinct(elements1, dup1));
    res2 = VIP_DEC(isDistinct(elements2, dup2));
    res3 = VIP_DEC(isDistinct(elements3, dup3));
  }

  printf("[ ");
  for (int i = 0; i < SIZE - 1; i++)
    printf("%d, ", VIP_DEC(print1[i]));
  printf("%d]\n", VIP_DEC(print1[SIZE - 1]));
  if (res1)
    cout << "The elements of `elements1' are distinct" << endl;
  else
    cout << "The elements of `elements1' are not distinct (e.g., " << VIP_DEC(dup1) << " is duplicated)" << endl;

  printf("[ ");
  for (int i = 0; i < SIZE - 1; i++)
    printf("%d, ", VIP_DEC(print2[i]));
  printf("%d]\n", VIP_DEC(print2[SIZE - 1]));
  if (res2)
    cout << "The elements of `elements2' are distinct" << endl;
  else
    cout << "The elements of `elements2' are not distinct (e.g., " << VIP_DEC(dup2) << " is duplicated)" << endl;

  printf("[ ");
  for (int i = 0; i < SIZE - 1; i++)
    printf("%d, ", VIP_DEC(print3[i]));
  printf("%d]\n", VIP_DEC(print3[SIZE - 1]));
  if (res3)
    cout << "The elements of `elements3' are distinct" << endl;
  else
    cout << "The elements of `elements3' are not distinct (e.g., " << VIP_DEC(dup3) << " is duplicated)" << endl;

  return 0;
}