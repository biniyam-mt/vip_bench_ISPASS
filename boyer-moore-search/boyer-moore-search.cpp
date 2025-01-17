/* C Program for Bad Character Heuristic of Boyer
Moore String Matching Algorithm */
// SOURCE: https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/

#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "../config.h"

#ifdef VIP_DO_MODE
#define VIP_DO_IF
#define VIP_DO_LOOP
#define VIP_DO_MEM
#endif /* VIP_DO_MODE */

using namespace std;

#define NO_OF_CHARS 256

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
#ifndef VIP_DO_MEM
    badchar[(int)str[i]] = i;
#else
    /**** IISWC DO Transformation: <ACCESS> <B.M.T> ****/
    // True data-obliviousness requires us to write to all indexes
    VIP_ENCINT badchar_index = (VIP_ENCINT)str[i];
    for (int j = 0; j < NO_OF_CHARS; j++)
    {
      badchar[j] = VIP_CMOV(j == badchar_index, j, badchar[j]);
    }
#endif
  }
}

/* A pattern searching function that uses Bad
Character Heuristic of Boyer Moore Algorithm */
void search(vector<VIP_ENCCHAR> txt, int n, vector<VIP_ENCCHAR> pat, int m, VIP_ENCBOOL *ret)
{
  VIP_ENCINT badchar[NO_OF_CHARS];

  /* Fill the bad character array by calling
  the preprocessing function badCharHeuristic()
  for given pattern */
  badCharHeuristic(pat, m, badchar);

  VIP_ENCINT s = 0; // s is shift of the pattern with
                    // respect to text

  for (int l = 0; l <= (n - m); l++)
  {
#ifndef VIP_DO_IF
    /**** IISWC DO Transformation: <LOOP> <B.M.T> ****/
    // Early exit if not data-oblivious...
    if (VIP_DEC(s) > (n - m))
      break;
#endif

    VIP_ENCINT idx = m - 1;

    /* Keep reducing index idx of pattern while
    characters of pattern and text are
    matching at this shift s */
#ifndef VIP_DO_MODE
    while (idx >= 0 && pat[VIP_DEC(idx)] == txt[VIP_DEC(s + idx)])
    {
      idx--;
    }
#else
    /**** IISWC DO Transformation: <LOOP> <B.M.T> ****/
    for (int i = 0; i < m; i++)
    {
      /**** IISWC DO Transformation: <ACCESS> <B.M.T> ****/
      // Access: pat[VIP_DEC(idx)]
      VIP_ENCCHAR pat_idx = pat[0];
      for (int j = 0; j < m; j++)
        pat_idx = VIP_CMOV(j == idx, pat[j], pat_idx);

      /**** IISWC DO Transformation: <ACCESS> <B.M.T> ****/
      // Access: txt[VIP_DEC(s+idx)]
      VIP_ENCCHAR txt_idx = txt[0];
      for (int j = 0; j < n; j++)
        txt_idx = VIP_CMOV(j == s + idx, txt[j], txt_idx);

      /* Comment from Reviewer: [MZD]
      * 
      * For the for-loops above, to improve performance I would do the following: 
      * Identify if n or m is greater: let's call it x. Description [x: (n > m) ? n : m]
      *  
      * VIP_ENCCHAR pat_idx = pat[0];
      * VIP_ENCCHAR txt_idx = txt[0];
      * 
      * for(int j = 0; j < x; j++){
      *     pat_idx = VIP_CMOV(j == idx , pat[j%m], pat_idx);
      *     txt_idx = VIP_CMOV(j == s + idx, txt[j%n], txt_idx);
      *  }
      * 
      */

      /**** IISWC DO Transformation: <IF> <B.M.T> ****/
      idx = idx - VIP_CMOV(idx >= 0 && pat_idx == txt_idx, (VIP_ENCINT)1, (VIP_ENCINT)0);

      /* 
      * Comment from Reviewer: [MZD] 
      * I wonder for the code above, if this version would be optimal in terms 
      * of performance: idx = idx - (idx >= 0 && pat_idx == txt_idx);
      * 
      */
    }
#endif

    /* If the pattern is present at current
    shift, then index idx will become -1 after
    the above loop */
    VIP_ENCBOOL cond = (idx < 0);
#ifndef VIP_DO_MODE
    if (cond)
    {
      ret[s] = true;
      s += (s + m < n) ? m - badchar[(int)txt[s + m]] : 1;
    }
    else
    {
      VIP_ENCINT s_shift = idx - badchar[(int)txt[VIP_DEC(s + idx)]];
      s += 1 > s_shift ? 1 : s_shift;
    }
#else
    /**** IISWC DO Transformation: <ACCESS/IF> <B.M.T> ****/
    // True data-obliviousness requires us to write to all indexes
    for (int i = 0; i < n; i++)
    {
      ret[i] = VIP_CMOV(cond && i == s, true, ret[i]);
    }
    /**** IISWC DO Transformation: <ACCESS> <B.M.T> ****/
    // Access: badchar[VIP_DEC(txt[VIP_DEC(s+m)])]
    VIP_ENCINT txt_sm = (VIP_ENCINT)txt[0];
    for (int j = 0; j < n; j++)
      txt_sm = VIP_CMOV(j == s + m, txt[j], txt_sm);

    /**** IISWC DO Transformation: <ACCESS> <B.M.T> ****/
    VIP_ENCINT badchar_txt_sm = badchar[0];
    for (int j = 0; j < NO_OF_CHARS; j++)
      badchar_txt_sm = VIP_CMOV(j == txt_sm, badchar[j], badchar_txt_sm);

    /**** IISWC DO Transformation: <ACCESS> <B.M.T> ****/
    // Access: badchar[VIP_DEC(txt[VIP_DEC(s+idx)])]
    VIP_ENCINT txt_sidx = (VIP_ENCINT)txt[0];
    for (int j = 0; j < n; j++)
      txt_sidx = VIP_CMOV(j == s + idx, txt[j], txt_sidx);

    /**** IISWC DO Transformation: <ACCESS> <B.M.T> ****/
    VIP_ENCINT badchar_txt_sidx = badchar[0];
    for (int j = 0; j < NO_OF_CHARS; j++)
      badchar_txt_sidx = VIP_CMOV(j == txt_sidx, badchar[j], badchar_txt_sidx);

    
    /* Comment from Reviewer: [MZD]
      * 
      * For the for-loops above, to improve performance I would do the following: 
      *  
      * VIP_ENCINT txt_sm = (VIP_ENCINT)txt[0];
      * VIP_ENCINT badchar_txt_sm = badchar[0];
      * VIP_ENCINT txt_sidx = (VIP_ENCINT)txt[0];
      * VIP_ENCINT badchar_txt_sidx = badchar[0];
      * 
      * for(int j = 0; j < n; j++){
      *     ret[j] = VIP_CMOV(cond && j == s, true, ret[j]);
      *     txt_sm = VIP_CMOV(j == s + m, txt[j], txt_sm);
      *     txt_sidx = VIP_CMOV(j == s + idx, txt[j], txt_sidx);
      *  }
      * 
      * for(int j = 0; j< NO_OF_CHARS; j++){
      *     badchar_txt_sm = VIP_CMOV(j == txt_sm , badchar[j], badchar_txt_sm);
      *     badchar_txt_sidx = VIP_CMOV(j == txt_sidx, badchar[j], badchar_txt_sidx);
      * }
      * 
      */


    /**** IISWC DO Transformation: <IF> <B.M.T> ****/
    VIP_ENCINT s_if = VIP_CMOV(s + m < n, m - badchar_txt_sm, 1);
    VIP_ENCINT s_shift = idx - badchar_txt_sidx;

    /**** IISWC DO Transformation: <IF> <B.M.T> ****/
    VIP_ENCINT s_else = VIP_CMOV(1 > s_shift, 1, s_shift);

    /**** IISWC DO Transformation: <IF> <B.M.T> ****/
    s = s + VIP_CMOV(cond, s_if, s_else);
#endif
  }
}

int main(void)
{
  VIP_INIT;

  // Inputs
  // char inp_txt[] = "ABAAABCDDABC";
  char inp_txt[] =
      "zJfMus2WzLnMr82T4bmuzKTNjcylzYfNiGjMssyBZc2PzZPMvMyXzJnMvMyjzZQgzYfMnMyxzKDN"
      "k82NzZVOzZXNoGXMl8yxesyYzJ3MnMy6zZlwzKTMusy5zY3Mr82aZcygzLvMoM2ccsyozKTNjcy6"
      "zJbNlMyWzJZkzKDMn8ytzKzMnc2facymzZbMqc2TzZTMpGHMoMyXzKzNicyZbs2azZwgzLvMnsyw"
      "zZrNhWjMtc2JacyzzJ52zKLNh+G4mc2OzZ8t0onMrcypzLzNlG3MpMytzKtpzZXNh8ydzKZuzJfN"
      "meG4jcyfIMyvzLLNlc2ex6vMn8yvzLDMss2ZzLvMnWYgzKrMsMywzJfMlsytzJjNmGPMps2NzLLM"
      "ns2NzKnMmeG4pc2aYcyuzY7Mn8yZzZzGocypzLnNjnPMpC7MncydINKJWsyhzJbMnM2WzLDMo82J"
      "zJxhzqwerty42ZbMsM2ZzKzNoWzMssyrzLPNjcypZ8yhzJ/MvMyxzZrMnsyszYVvzJfNnC7Mnw=="
      "zKZIzKzMpMyXzKTNnWXNnCDMnMylzJ3Mu82NzJ/MgXfMlWjMlsyvzZNvzJ3NmcyWzY7MscyuINKJ"
      "zLrMmcyezJ/NiFfMt8y8zK1hzLrMqs2NxK/NiM2VzK3NmcyvzJx0zLbMvMyuc8yYzZnNlsyVIMyg"
      "zKvMoELMu82NzZnNicyzzYVlzLVozLXMrM2HzKvNmWnMuc2TzLPMs8yuzY7Mq8yVbs2fZMy0zKrM"
      "nMyWIMywzYnMqc2HzZnMss2ezYVUzZbMvM2TzKrNomjNj82TzK7Mu2XMrMydzJ/NhSDMpMy5zJ1X";

  // char inp_pat[] = "ABC";
  char inp_pat[] = "NzZ";

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
