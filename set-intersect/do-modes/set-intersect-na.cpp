#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

#include "utils.h"

// include build configuration defines
#include "../config.h"

#define MAX_SETVAL    5000
#define SETA_SIZE     5000
#define SETB_SIZE     4000

void
set_init(vector<VIP_ENCINT>& set)
{
  vector<int> _set(set.size());

  for (unsigned i=0; i < _set.size(); i++)
  {
    // REDO:: checks if val has been added to the set previously
  redo:
    int val = myrand() % MAX_SETVAL;
    for (unsigned j=0; i != 0 && j < i; j++)
    {
      if (_set[j] == val)
        goto redo;
    }
    set[i] = _set[i] = val;
  }
}

void
set_print(const char *name, vector<VIP_ENCINT>& set)
{
  fprintf(stdout, "%s:\n", name);
  for (unsigned i=0; i < set.size(); i++)
    fprintf(stdout, "  %s[%u] = %d\n", name, i, VIP_DEC(set[i]));
}

void
set_intersect(vector<VIP_ENCINT>& setA, vector<VIP_ENCINT>& setB, vector<VIP_ENCBOOL>& setA_match)
{
  for (unsigned i=0; i < setA.size(); i++)
  {
    VIP_ENCBOOL match = false;
    for (unsigned j=0; j < setB.size(); j++)
    {
      if (setA[i] == setB[j])
        match = true;
    }
    setA_match[i] = match;
  }
}

int
main(void)
{
  vector<VIP_ENCINT> setA(SETA_SIZE);
  vector<VIP_ENCINT> setB(SETB_SIZE);
  vector<VIP_ENCBOOL> setA_match(SETA_SIZE);

  // initialize the privacy enhanced execution target
  VIP_INIT;

  // initialize the pseudo-RNG
  mysrand(42);

  // initialize the set vectors
  set_init(setA); 
  set_print("setA", setA);
  set_init(setB); 
  set_print("setB", setB);

  {
    Stopwatch s("VIP_Bench Runtime");
    set_intersect(setA, setB, setA_match);
  }

  // print the intersection
  fprintf(stdout, "setA & setB:\n");
  
  unsigned j=0;
  for (unsigned i=0; i < setA_match.size(); i++)
  {
    if (VIP_DEC(setA_match[i]))
      fprintf(stdout, "  setA_and_setB[%u] = %d\n", j++, VIP_DEC(setA[i]));
  }
  fprintf(stdout, "INFO: cardinality(setA & setB) == %u\n", j);
  return 0;
}

