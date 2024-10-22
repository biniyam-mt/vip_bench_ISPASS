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

/* A pattern searching function that uses Bad Character Heuristic of Boyer Moore Algorithm */
void search(vector<VIP_ENCCHAR> &txt, int n, vector<VIP_ENCCHAR> &pat, int m, VIP_ENCBOOL *ret)
{

  for (int s = 0; s <= (n - m); s++) // loop over input txt
  {

    VIP_ENCBOOL match = true;
    for (int i = 0; i < m; i++) // loop over pattern pat
    {
      match = match & (pat[i] == txt[s + i]);
    }
    ret[s] = match;
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
