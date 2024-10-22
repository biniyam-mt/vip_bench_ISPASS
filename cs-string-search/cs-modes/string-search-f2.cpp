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

// D is the number of characters in the input alphabet
#define D 256

/* simple string search algorithm */
void search(vector<VIP_ENCCHAR> &txt, int n, vector<VIP_ENCCHAR> &pat, int m, VIP_ENCBOOL *ret)
{
  int q = INT_MAX;

  // value of h would be "pow(d, M-1)%q"
  int h = 1;
  for (int i = 0; i < m - 1; i++)
    h = (h * D) % q;

  VIP_ENCINT p = 0; // hash value for pattern
  VIP_ENCINT t = 0; // hash value for txt

  // calculate the hash value of pattern and first window of text
  for (int i = 0; i < m; i++)
  {
    p = (D * p + pat[i]) % q;
    t = (D * t + txt[i]) % q;
  }

  // slide the pattern over text one by one
  for (int i = 0; i <= (n - m); i++)
  {

    // check the hash values of current window of text
    // and pattern. If the hash values match then only
    // check for characters one by one
    ret[i] = (p == t);

    // calculate hash value for next window of text: Remove leading digit, add trailing digit
    VIP_ENCBOOL _pred = (i < (int)txt.size() - (int)pat.size());
    t = VIP_CMOV(_pred, ((D * (t - ((VIP_ENCINT)txt[i]) * h) + txt[i + pat.size()]) % q), t);

    VIP_ENCBOOL _pred1 = (t < 0);
    t = VIP_CMOV(_pred & _pred1, t + q, t);
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
