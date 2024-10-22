/* miller_rabin_int.c -- long long implementation of the Miller-Rabin test
 *
 * Copyright 2014 by Colin Benner <colin-software@yzhs.de>
 *
 * This file is part of frobenius-test.
 *
 * frobenius-test is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * frobenius-test is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with frobenius-test.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "../../config.h"

// precision of the primality test, there p_failure = 1/4^K
#define K 16

// primality results
#define PT_COMPOSITE 0
#define PT_PRIME 1
#define PT_PRIME_LIKELY 2

/*
 * Raise b to the e'th power modulo m.  This uses 64-bit registers to hold the
 * results of the multipliations.  Therefore, the results will be wrong if m is
 * greater than 2^32-1
 */
static VIP_ENCULONG powm(VIP_ENCULONG b, VIP_ENCULONG e, VIP_ENCUINT m)
{
  VIP_ENCULONG result = 1;

  VIP_ENCBOOL _done = false;
  for (int i = 0; i < 64; i++)
  {
    _done = _done || (e == 0);
    if (!_done)
    {
      if ((e & 1) == 1){
        result = (result * b) % m;
      }
      b = (b * b) % m;
      e /= 2;
    }
  }

  return result;
}

/*
 * This function generates a random integer between in the interval
 * [low, high].  As we divide by (high - low + 1) in the process, we need
 * low < high.
 */
VIP_ENCULONG get_random_int(VIP_ENCULONG low, VIP_ENCULONG high)
{
  VIP_ENCULONG x = (high - low + 1);
  if(x==0) x=1;
  return (uint64_t)myrand() % x + low;
}

/*
 * Calculate s, d such that n-1=2^s*d where d is odd.
 */
void split_int(VIP_ENCULONG *s, VIP_ENCULONG *d, VIP_ENCULONG n)
{
  *s = 0;
  *d = n - 1;

  VIP_ENCBOOL _done = false;
  for (int i = 0; i < 64; i++)
  {
    _done = _done || ((*d & 1) != 0);
    if (!_done)
    {
      (*s)++;
      *d /= 2;
    }
  }
}
/*
 * This function checks whether a given number n is a prime or not, using the
 * Miller-Rabin primality test.  This is a probabilistic test which randomly
 * chooses an integer a as a base and checks whether n satisfies a certain
 * property (which depends on b).  If it does, n is a prime for at least three
 * out of four of the possible values of a, if it does not, it is certainly not
 * prime.
 *
 * The implementation is taken from the pseudo code found on
 * http://en.wikipedia.org/wiki/Miller-Rabin_primality_test.
 *
 * The function returns `probably_prime` if it found no evidence, that n might
 * be composite and `composite` if it did find a counter example.
 */
VIP_ENCINT
miller_rabin_int(VIP_ENCUINT n, uint32_t k)
{
  VIP_ENCULONG s;
  VIP_ENCULONG a = 0, d, x, nm1;
  VIP_ENCBOOL _done = false;
  VIP_ENCINT _retval = -1;

  /* We need an odd integer greater than 3 */
  if ((n & 1) == 0){
    if(n == 2)
      _retval = PT_PRIME;
    else
      _retval = PT_COMPOSITE;
    _done = true;
  }
  else if (!_done && n == 3){
    _retval = PT_PRIME;
    _done = true;
  }
  else if (!_done && n < 3){
    _retval = PT_COMPOSITE;
    _done = true;
  }

  nm1 = n - 1;

  /* compute s and d s.t. n-1=2^s*d */
  split_int(&s, &d, n);

  /* Repeat the test itself k times to increase the accuracy */
  for (unsigned i = 0; i < k; i++)
  {
      VIP_ENCBOOL _continued = false;

      a = get_random_int(2, n - 2);

      /* compute a^d mod n */
      x = powm(a, d, n);

      _continued = (x == 1 || x == nm1); //LB: Skip loop if continue condition is met;
      if (!_continued && !_done)
      {
        VIP_ENCBOOL _breakout = false;
        VIP_ENCULONG r = 1;
        for (int ii = 0; ii < 64; ii++)
        {
          _breakout = _breakout || !(r <= s);
          if (!_breakout)
          {
            x = (x * x) % n;
            if (x == 1)
            {
              _retval = PT_COMPOSITE;
              _done = true;
            }

            if (x == nm1)
              _breakout = true;
          }
          r++;
        }

        if (x != nm1) {
          _retval = PT_COMPOSITE;
          _done = true;
        }
      }
  }

  if (!_done)
    _retval = PT_PRIME_LIKELY;
  return _retval;
}

// blind queue for results
#define Q_SIZE 64
struct
{
  VIP_ENCUINT val;
  VIP_ENCINT prim;
} q[Q_SIZE];
int q_head = 0;

int main(void)
{
  // initialize the RNG
  mysrand(42);

  // locate primes in a stream of random numbers
  {
    Stopwatch s("VIP_Bench Runtime");

    VIP_ENCUINT val = 3;
    for (int i = 0; i < 200; i++)
    {
      VIP_ENCINT prim = miller_rabin_int(val, K);
      VIP_ENCBOOL _pred = (prim != PT_COMPOSITE);
      if (VIP_DEC(_pred))
      {
        q[q_head].val = val;
        q[q_head].prim = prim;
        if (q_head + 1 < Q_SIZE)
          q_head++;
      }
      mysrand(VIP_DEC(val));
      val = myrand();
    }
  }

  // print out the primes that were found
  fprintf(stdout, "Primality tests found %d primes...\n", q_head);
  for (int i = 0; i < q_head; i++)
  {
    if (VIP_DEC(q[i].prim) == PT_PRIME)
      fprintf(stdout, "Value %u is `prime' with failure probability (0)\n", VIP_DEC(q[i].val));
    else if (VIP_DEC(q[i].prim) == PT_PRIME_LIKELY)
      fprintf(stdout, "Value %u is `likely prime' with failure probability (1 in %le)\n", VIP_DEC(q[i].val), pow(4.0, K));
  }
  return 0;
}
