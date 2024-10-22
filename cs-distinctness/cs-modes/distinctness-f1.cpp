/*
 ELEMENT DISTINCTNESS ALGORITHM
 There are multiple ways of detecting whether the elements are distinct or not.
 An n^2 loop can be used to select an element from the array and check if the
 the element exists. The function checking for duplicates is the isDistinct
 function. The argument 'dup' stores the first duplicate found in the array.
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

VIP_ENCBOOL
isDistinct(VIP_ENCINT elements[], VIP_ENCINT &dup)
{
  dup = MAX;

  for (int i = SIZE - 1; i >= 0; i--)
  {
    for (int j = 0; j < SIZE; j++)
      dup = VIP_CMOV((elements[i] == elements[j]) & (i != j) & (dup == MAX), elements[j], dup);
  }

  return (dup == MAX);
}

int main(void)
{
  VIP_ENCINT dup1, dup2, dup3;

  bool res1, res2, res3;

  // initialize the pseudo-RNG
  mysrand(42);

  // initialize the array to sort
  for (unsigned i = 0; i < SIZE; i++)
  {
    elements1[i] = myrand() % 201;
    elements2[i] = myrand() % 501;
    elements3[i] = myrand();
  }

  {
    Stopwatch s("VIP Distinctness check:");

    res1 = VIP_DEC(isDistinct(elements1, dup1));
    res2 = VIP_DEC(isDistinct(elements2, dup2));
    res3 = VIP_DEC(isDistinct(elements3, dup3));
  }

  printf("[ ");
  for (int i = 0; i < SIZE - 1; i++)
    printf("%d, ", VIP_DEC(elements1[i]));
  printf("%d]\n", VIP_DEC(elements1[SIZE - 1]));
  if (res1)
    cout << "The elements of `elements1' are distinct" << endl;
  else
    cout << "The elements of `elements1' are not distinct (e.g., " << VIP_DEC(dup1) << " is duplicated)" << endl;

  printf("[ ");
  for (int i = 0; i < SIZE - 1; i++)
    printf("%d, ", VIP_DEC(elements2[i]));
  printf("%d]\n", VIP_DEC(elements2[SIZE - 1]));
  if (res2)
    cout << "The elements of `elements2' are distinct" << endl;
  else
    cout << "The elements of `elements2' are not distinct (e.g., " << VIP_DEC(dup2) << " is duplicated)" << endl;

  printf("[ ");
  for (int i = 0; i < SIZE - 1; i++)
    printf("%d, ", VIP_DEC(elements3[i]));
  printf("%d]\n", VIP_DEC(elements3[SIZE - 1]));
  if (res3)
    cout << "The elements of `elements3' are distinct" << endl;
  else
    cout << "The elements of `elements3' are not distinct (e.g., " << VIP_DEC(dup3) << " is duplicated)" << endl;

  return 0;
}
