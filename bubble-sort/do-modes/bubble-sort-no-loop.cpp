#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// include build configuration defines
#include "../../config.h"

#define DATASET_SIZE 4096
VIP_ENCINT data[DATASET_SIZE];

// total swaps executed so far
unsigned long swaps = 0;


void
print_data(VIP_ENCINT *data, unsigned size)
{
  fprintf(stdout, "DATA DUMP:\n");
  for (unsigned i=0; i < size; i++)
    fprintf(stdout, "  data[%u] = %d\n", i, VIP_DEC(data[i]));
}

void
bubblesort(VIP_ENCINT *data, unsigned size)
{
  for (unsigned i=size; i > 1; i--)
  {
    for (unsigned j=0; j < i-1; j++)
    {
/**** IISWC DO Transformation: IF Conversion - LB ****/
      if (data[j] > data[j+1])
      {
        VIP_ENCINT tmp = data[j];
        data[j] = data[j+1];
        data[j+1] = tmp;
        swaps++;
      }
    }
  }
}

int
main(void)
{
  // initialize the privacy enhanced execution target
  VIP_INIT;

  // initialize the pseudo-RNG
  mysrand(42);
  // mysrand(time(NULL));

  // initialize the array to sort
  for (unsigned i=0; i < DATASET_SIZE; i++)
    data[i] = myrand();
  print_data(data, DATASET_SIZE);

  {
    Stopwatch s("VIP_Bench Runtime");
    bubblesort(data, DATASET_SIZE);
  }
  print_data(data, DATASET_SIZE);

  // check the array
  for (unsigned i=0; i < DATASET_SIZE-1; i++)
  {
    if (VIP_DEC(data[i]) > VIP_DEC(data[i+1]))
    {
      fprintf(stdout, "ERROR: data is not properly sorted.\n");
      return -1;
    }
  }
  fprintf(stderr, "INFO: %lu swaps executed.\n", swaps);
  fprintf(stdout, "INFO: data is properly sorted.\n");
  return 0;
}
