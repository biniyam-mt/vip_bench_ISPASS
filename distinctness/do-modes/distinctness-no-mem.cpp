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

#define SIZE 128
// NOTE: 0 can not be an element of the array evaluated for distinctness since MAX is set to 0
#define MAX 0

VIP_ENCINT elements1[SIZE];
VIP_ENCINT elements2[SIZE];
VIP_ENCINT elements3[SIZE];

VIP_ENCBOOL isDistinct(VIP_ENCINT elements[], VIP_ENCINT &dup)
{

  VIP_ENCINT tree[SIZE][3];
  dup = MAX;

  for (int i = 0; i < SIZE; i++)
  {
    tree[i][0] = MAX;
    tree[i][1] = MAX;
    tree[i][2] = MAX;
  }

  tree[0][0] = elements[0];
  VIP_ENCINT location = 0;
  VIP_ENCBOOL _result = true;

  for (int i = 1; i < SIZE; i++)
  {
    VIP_ENCINT temp = 0;

    VIP_ENCINT value = tree[0][0];
    VIP_ENCINT left = tree[0][1];
    VIP_ENCINT right = tree[0][2];

    VIP_ENCBOOL check = false;
    VIP_ENCBOOL _break = false;

    for (int k = 0; k < i; k++)
    {

      VIP_ENCBOOL condition1 = elements[i] > value;
      VIP_ENCBOOL condition2 = right != MAX;

      VIP_ENCBOOL _isRightNotMax = condition1 & condition2;
      VIP_ENCBOOL _isRightMax = condition1 & !condition2;

      VIP_ENCBOOL condition3 = elements[i] < value;
      VIP_ENCBOOL condition4 = left != MAX;

      VIP_ENCBOOL _isLeftNotMax = condition3 & condition4;
      VIP_ENCBOOL _isLeftMax = condition3 & !condition4;

      VIP_ENCBOOL notBoth = !condition1 & !condition3; // duplicate is found

      check = !_break;
      _break = VIP_CMOV(_isLeftMax | _isRightMax, true, _break);

      temp = VIP_CMOV(_isLeftNotMax & !_break, left, temp);
      temp = VIP_CMOV(_isRightNotMax & !_break, right, temp);

      location = VIP_CMOV((_isLeftMax | _isRightMax) & check, location + 1, location);

      for (int x = 0; x <= i; x++)
      {
        VIP_ENCBOOL cond = (x == temp);

        value = VIP_CMOV(cond & (_isRightNotMax | _isLeftNotMax) & !_break, tree[x][0], value);

        left = VIP_CMOV(cond & (_isRightNotMax | _isLeftNotMax) & !_break, tree[x][1], left);
        right = VIP_CMOV(cond & (_isRightNotMax | _isLeftNotMax) & !_break, tree[x][2], right);

        tree[x][2] = VIP_CMOV(cond & _isRightMax & check, location, tree[x][2]);
        tree[x][1] = VIP_CMOV(cond & _isLeftMax & check, location, tree[x][1]);
        tree[x][0] = VIP_CMOV((x == location) & (_isLeftMax | _isRightMax) & check, elements[i], tree[x][0]);
      }

      dup = VIP_CMOV(notBoth & _result, elements[i], dup);
      _result = VIP_CMOV(notBoth, false, _result); // duplicate has been found
    }
  }
  return _result;
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
    printf("%d, ", elements1[i]);
  printf("%d]\n", elements1[SIZE - 1]);

  if (res1)
    cout << "The elements of `elements1' are distinct" << endl;
  else
    cout << "The elements of `elements1' are not distinct (e.g., " << VIP_DEC(dup1) << " is duplicated)" << endl;

  printf("[ ");
  for (int i = 0; i < SIZE - 1; i++)
    printf("%d, ", elements2[i]);
  printf("%d]\n", elements2[SIZE - 1]);
  if (res2)
    cout << "The elements of `elements2' are distinct" << endl;
  else
    cout << "The elements of `elements2' are not distinct (e.g., " << VIP_DEC(dup2) << " is duplicated)" << endl;

  printf("[ ");
  for (int i = 0; i < SIZE - 1; i++)
    printf("%d, ", elements3[i]);
  printf("%d]\n", elements3[SIZE - 1]);
  if (res3)
    cout << "The elements of `elements3' are distinct" << endl;
  else
    cout << "The elements of `elements3' are not distinct (e.g., " << VIP_DEC(dup3) << " is duplicated)" << endl;

  return 0;
}