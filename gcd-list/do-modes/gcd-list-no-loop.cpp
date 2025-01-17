/**
 * @file
 * @brief This program aims at calculating the GCD of n numbers by division
 * method
 *
 * @see gcd_iterative_euclidean.cpp, gcd_recursive_euclidean.cpp
 */
#include <iostream>

#include "../../config.h"

/** Compute GCD using division algorithm
 *
 * @param[in] a array of integers to compute GCD for
 * @param[in] n number of integers in array `a`
 */
VIP_ENCUINT
gcd(VIP_ENCUINT *a, unsigned n)
{
  unsigned j = 1; // to access all elements of the array starting from 1
  VIP_ENCUINT gcd = a[0];
  while (j < n)
  {
#define MAXITER 32 // any division >= 2 will reduce precision by at least 1 bit
    for (unsigned iter = 0; iter < MAXITER; iter++)
    {
      if (!(a[j] % gcd == 0)) // value of gcd is as needed so far
        gcd = a[j] % gcd;     // calculating GCD by division method
    }
    j++;
  }
  return gcd;
}

/** Main function */
int main(void)
{
  // initialize RNG
  mysrand(42);

  unsigned n = 10000;
  VIP_ENCUINT *a = new VIP_ENCUINT[n];
  for (unsigned i = 0; i < n; i++)
    a[i] = (myrand() % 10000000) * 37;

  fprintf(stdout, "INFO: a[%d] = { ", n);
  for (unsigned i = 0; i < n; i++)
    fprintf(stdout, "%d, ", VIP_DEC(a[i]));
  fprintf(stdout, " }\n");

  VIP_ENCUINT gcd_of_n;
  {
    Stopwatch s("VIP-Bench gcd-list:");

    gcd_of_n = gcd(a, n);
  }
  std::cout << "GCD of list:" << VIP_DEC(gcd_of_n) << std::endl;

  delete[] a;
  return 0;
}
