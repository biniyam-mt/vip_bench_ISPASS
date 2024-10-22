/* C Program for Bad Character Heuristic of Boyer
Moore String Matching Algorithm */
// SOURCE: https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/

#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "../../config.h"

using namespace std;

#define NO_OF_CHARS 256
#define SIZE 512

// The preprocessing function for Boyer Moore's
// bad character heuristic
void badCharHeuristic(vector<VIP_ENCCHAR> str, int size, VIP_ENCINT badchar[NO_OF_CHARS])
{
  // Initialize all occurrences as -1
  for (int i = 0; i < NO_OF_CHARS; i++)
  {
    badchar[i] = -1;
  }
  // Fill the actual value of last occurrence of a character
  for (int i = 0; i < size; i++)
  {
    badchar[(int)VIP_DEC(str[i])] = i;
  }
}

/* A pattern searching function that uses Bad Character Heuristic of Boyer Moore Algorithm */
void search(vector<VIP_ENCCHAR> &txt, int n, vector<VIP_ENCCHAR> &pat, int m, VIP_ENCBOOL *ret)
{
  VIP_ENCINT badchar[NO_OF_CHARS];

  /* Fill the bad character array by calling
  the preprocessing function badCharHeuristic()
  for given pattern */
  badCharHeuristic(pat, m, badchar);

  VIP_ENCINT s = 0; // s is shift of the pattern with respect to text

  for (int l = 0; l <= (n - m); l++)
  {
    // Early exit if not data-oblivious...
    if (VIP_DEC(s) > (n - m))
      break;

    VIP_ENCINT idx = m - 1;

    /* Keep reducing index idx of pattern while
    characters of pattern and text are
    matching at this shift s */
    while (idx >= 0 && pat[VIP_DEC(idx)] == txt[VIP_DEC(s + idx)])
    {
      idx--;
    }
    /* If the pattern is present at current
    shift, then index idx will become -1 after
    the above loop */
    VIP_ENCBOOL cond = (idx < 0);

    if (VIP_DEC(cond))
    {
      ret[VIP_DEC(s)] = true;
      s += (s + m < n) ? m - badchar[(int)VIP_DEC(txt[VIP_DEC(s + m)])] : 1;
    }
    else
    {
      VIP_ENCINT s_shift = idx - badchar[(int)VIP_DEC(txt[VIP_DEC(s + idx)])];
      s += 1 > s_shift ? 1 : s_shift;
    }
  }
}

int main(void)
{
  VIP_INIT;

  char inp_txt[SIZE];
  // initialize the pseudo-RNG
  mysrand(14);

  // initialize the array to sort
  for (unsigned i = 0; i < SIZE; i++)
  {
    int rand_char = (myrand() % 58) + 65;
    if (rand_char > 90 && rand_char < 97)
    {
      i--;
    }
    else
    {
      inp_txt[i] = rand_char;
    }
  }
  // Insert pattern
  char inp_pat[] = "cypzABAx";
  for (int i = 0; i < 3; i++)
  {
    int shift = myrand() % (SIZE - strlen(inp_pat));
    printf("Shift: %d\n", shift);
    for (unsigned j = 0; j < strlen(inp_pat); j++)
    {
      inp_txt[shift + j] = inp_pat[j];
    }
  }

  printf("Text: ");
  for (int i = 0; i < SIZE; i++)
  {
    printf("%c", inp_txt[i]);
  }
  printf("\n");

  int n = strlen(inp_txt); // String lengths are public
  int m = strlen(inp_pat); // String lengths are public

  vector<VIP_ENCCHAR> txt(n);
  for (int k = 0; k < n; k++)
    txt[k] = inp_txt[k];

  vector<VIP_ENCCHAR> pat(m);
  for (int k = 0; k < m; k++)
    pat[k] = inp_pat[k];

  // Return vector
  VIP_ENCBOOL ret[n];
  for (int i = 0; i < n; i++)
    ret[i] = false;

  // Run search
  {
    Stopwatch s("VIP_Bench Runtime");
    search(txt, n, pat, m, ret);
  }

  // print results
  for (int i = 0; i < n; i++)
  {
    if (VIP_DEC(ret[i]))
    {
      printf("pattern occurs at shift = %d\n", i);
    }
  }

  return 0;
}
